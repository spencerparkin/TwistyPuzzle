// TwistyPuzzle.cpp

#include "TwistyPuzzle.h"
#include "Application.h"
#include "Frame.h"
#include "ShaderProgram.h"
#include <Surface.h>
#include <ListFunctions.h>
#include <wx/wfstream.h>
#include <wx/msgdlg.h>

#if defined LINUX
#	define sprintf_s snprintf
#endif

//---------------------------------------------------------------------------------
//                                  TwistyPuzzle
//---------------------------------------------------------------------------------

wxIMPLEMENT_ABSTRACT_CLASS( TwistyPuzzle, wxObject )

TwistyPuzzle::TwistyPuzzle( void )
{
	rotationSpeedCoeficient = 10.0;
	needsSaving = false;
	rotationHistoryIter = rotationHistory.end();
	shaderProgram = nullptr;
}

/*virtual*/ TwistyPuzzle::~TwistyPuzzle( void )
{
	Clear();

	delete shaderProgram;
}

/*virtual*/ void TwistyPuzzle::Clear( void )
{
	_3DMath::FreeList< Face >( faceList );
	_3DMath::FreeList< CutShape >( cutShapeList );
	_3DMath::FreeList< Rotation >( rotationQueue );
	_3DMath::FreeList< Rotation >( rotationHistory );
}

/*virtual*/ bool TwistyPuzzle::SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown )
{
	return false;
}

void TwistyPuzzle::AddHistory( Rotation* newRotation )
{
	RotationList::iterator iter = rotationHistoryIter;
	while( iter != rotationHistory.end() )
	{
		RotationList::iterator nextIter = iter;
		nextIter++;
		Rotation* rotation = *iter;
		delete rotation;
		rotationHistory.erase( iter );
		iter = nextIter;
	}

	rotationHistory.push_back( newRotation );
	rotationHistoryIter = rotationHistory.end();
}

void TwistyPuzzle::GoForward( void )
{
	while( CanGoForward() )
	{
		Rotation* rotation = *rotationHistoryIter;
		Rotation* newRotation = new Rotation(0);
		*newRotation = *rotation;
		newRotation->flags |= Rotation::FLAG_HISTORY;
		EnqueueRotation( newRotation );
		rotationHistoryIter++;
		if( !( rotation->flags & Rotation::FLAG_FORWARD_AGAIN ) )
			break;
	}
}

void TwistyPuzzle::GoBackward( void )
{
	while( CanGoBackward() )
	{
		rotationHistoryIter--;
		Rotation* rotation = *rotationHistoryIter;
		Rotation* newRotation = new Rotation(0);
		*newRotation = *rotation;
		newRotation->turnCount = -newRotation->turnCount;
		newRotation->flags |= Rotation::FLAG_HISTORY;
		EnqueueRotation( newRotation );
		if( !( rotation->flags & Rotation::FLAG_BACK_AGAIN ) )
			break;
	}
}

bool TwistyPuzzle::CanGoForward( void )
{
	if( rotationHistoryIter == rotationHistory.end() )
		return false;
	return true;
}

bool TwistyPuzzle::CanGoBackward( void )
{
	if( rotationHistoryIter == rotationHistory.begin() )
		return false;
	return true;
}

TwistyPuzzle::CutShape* TwistyPuzzle::FindCutShapeWithLabel( const wxString& label )
{
	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		CutShape* cutShape = *iter;
		if( cutShape->label == label )
			return cutShape;
	}

	return nullptr;
}

/*static*/ TwistyPuzzle* TwistyPuzzle::AllocateUsingFile( const wxString& file )
{
	TwistyPuzzle* puzzle = nullptr;

	wxXmlDocument xmlDocument;
	wxFileInputStream fileInputStream( file );
	if( xmlDocument.Load( fileInputStream ) )
	{
		wxXmlNode* xmlRootNode = xmlDocument.GetRoot();
		if( xmlRootNode->GetName() == "TwistyPuzzle" )
		{
			wxString className = xmlRootNode->GetAttribute( "class_name" );
			const wxClassInfo* classInfo = wxClassInfo::FindClass( className );
			const wxClassInfo* baseClassInfo = wxClassInfo::FindClass( "TwistyPuzzle" );
			if( classInfo && classInfo->IsKindOf( baseClassInfo ) )
			{
				puzzle = ( TwistyPuzzle* )classInfo->CreateObject();
			}
		}
	}

	return puzzle;
}

void TwistyPuzzle::EnqueueRotation( Rotation* rotation )
{
	rotationQueue.push_back( rotation );
}

bool TwistyPuzzle::DequeueAndProcessNextRotation( void )
{
	if( rotationQueue.size() == 0 )
		return false;

	RotationList::iterator iter = rotationQueue.begin();
	Rotation* rotation = *iter;
	rotationQueue.erase( iter );

	wxStatusBar* statusBar = wxGetApp().GetFrame()->GetStatusBar();
	wxString text = wxString::Format( "%d rotations queued.", int( rotationQueue.size() ) );
	statusBar->SetStatusText( text );

	if( rotation->newRotationSpeedCoeficient != 0.0 )
		rotationSpeedCoeficient = rotation->newRotationSpeedCoeficient;

	bool deleteRotation = true;

	_3DMath::HandleObject* object = _3DMath::HandleObject::Dereference( rotation->cutShapeHandle );
	CutShape* cutShape = dynamic_cast< CutShape* >( object );
	if( cutShape )
	{
		if( ApplyCutShapeWithRotation( cutShape, rotation ) )
		{
			if( !( rotation->flags & Rotation::FLAG_HISTORY ) )
			{
				AddHistory( rotation );
				deleteRotation = false;
			}
		}
	}

	if( deleteRotation )
		delete rotation;

	return true;
}

bool TwistyPuzzle::ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper )
{
	bool motion = false;

	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		CutShape* cutShape = *iter;
		if( cutShape->rotationAngleForAnimation != 0.0 )
		{
			double rotationRateRadiansPerSecond = -cutShape->rotationAngleForAnimation * rotationSpeedCoeficient;
			double thresholdAngle = 0.01;

			if( fabs( cutShape->rotationAngleForAnimation ) < thresholdAngle )
				cutShape->rotationAngleForAnimation = 0.0;
			else
			{
				double deltaTimeSeconds = timeKeeper.GetDeltaTimeSeconds();
				cutShape->rotationAngleForAnimation += rotationRateRadiansPerSecond * deltaTimeSeconds;
			}

			motion = true;
		}
	}

	if( !motion )
		return DequeueAndProcessNextRotation();

	return true;
}

void TwistyPuzzle::BindCutShapeToCapturedFaces( CutShape* cutShape, FaceList& capturedFaceList )
{
	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;
		face->boundCutShapeHandle = 0;
	}

	for( FaceList::iterator iter = capturedFaceList.begin(); iter != capturedFaceList.end(); iter++ )
	{
		Face* face = *iter;
		face->boundCutShapeHandle = cutShape->GetHandle();
	}
}

/*virtual*/ bool TwistyPuzzle::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	double eps = GetCutAndCaptureEpsilon();

	FaceList capturedFaceList;
	cutShape->CutAndCapture( faceList, capturedFaceList, eps );

	BindCutShapeToCapturedFaces( cutShape, capturedFaceList );

	if( rotation )
	{
		double rotationAngle = rotation->turnCount * cutShape->rotationAngleForSingleTurn;
		if( rotation->direction == Rotation::DIR_CW )
			rotationAngle = -rotationAngle;
		rotationAngle = fmod( rotationAngle, 2.0 * M_PI );

		_3DMath::AffineTransform transform;
		transform.SetRotation( cutShape->axisOfRotation, rotationAngle );

		for( FaceList::iterator iter = capturedFaceList.begin(); iter != capturedFaceList.end(); iter++ )
		{
			Face* face = *iter;
			face->polygon->Transform( transform );
		}

		cutShape->rotationAngleForAnimation -= rotationAngle;

		// One major draw-back to how we're manipulating the puzzle is that it is subject
		// to accumulated round-off error.  This, however, can be overcome for puzzles that
		// don't shape-shift.  The idea is simply to cache the original vertices of the puzzle,
		// and then after each rotation, snap all transformed vertices to their closest cached point.
		// Hmmm...but this will only work if we also update the cache when new cuts are formed.
		// This could all be a mechanism handled at this base-class level, unbeknownst to the puzzle
		// derivative, even if it shape-shifts.  I'm not sure if it will solve the problem currently
		// had by the Gem6, but it may be worth a try.  The problem with the Gem6, I believe, may
		// have more to do with inaccuracy in the original vertex calculations.

		needsSaving = true;
	}

	return true;
}

void TwistyPuzzle::SetupStandardDynamicFaceTurningBoxLabels( double radius /*= 10.0*/ )
{
	labelMap.clear();

	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "R", _3DMath::Vector( 1.0, 0.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "L", _3DMath::Vector( -1.0, 0.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "U", _3DMath::Vector( 0.0, 1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "D", _3DMath::Vector( 0.0, -1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "F", _3DMath::Vector( 0.0, 0.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "B", _3DMath::Vector( 0.0, 0.0, -1.0 ) * radius ) );
}

void TwistyPuzzle::SetupStandardDynamicCornerTurningBoxLabels( double radius /*= 10.0*/ )
{
	labelMap.clear();

	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "X", _3DMath::Vector( -1.0, 1.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "Y", _3DMath::Vector( 1.0, 1.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "Z", _3DMath::Vector( 1.0, 1.0, -1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "W", _3DMath::Vector( -1.0, 1.0, -1.0 ) * radius ) );

	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "B", _3DMath::Vector( 1.0, -1.0, -1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "A", _3DMath::Vector( -1.0, -1.0, -1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "C", _3DMath::Vector( 1.0, -1.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "D", _3DMath::Vector( -1.0, -1.0, 1.0 ) * radius ) );
}

void TwistyPuzzle::SetupStandardDynamicEdgeTurningBoxLabels( double radius /*= 10.0*/ )
{
	labelMap.clear();
	
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "X", _3DMath::Vector( -1.0, 1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "Y", _3DMath::Vector( 0.0, 1.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "Z", _3DMath::Vector( 1.0, 1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "W", _3DMath::Vector( 0.0, 1.0, -1.0 ) * radius ) );

	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "A", _3DMath::Vector( -1.0, 0.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "B", _3DMath::Vector( 1.0, 0.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "C", _3DMath::Vector( 1.0, 0.0, -1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "D", _3DMath::Vector( -1.0, 0.0, -1.0 ) * radius ) );

	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "S", _3DMath::Vector( -1.0, -1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "T", _3DMath::Vector( 0.0, -1.0, 1.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "U", _3DMath::Vector( 1.0, -1.0, 0.0 ) * radius ) );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( "V", _3DMath::Vector( 0.0, -1.0, -1.0 ) * radius ) );
}

void TwistyPuzzle::SetupDynamicLabelUsingCutShape( const CutShape* cutShape )
{
	_3DMath::Vector point;
	point.AddScale( cutShape->axisOfRotation.center, cutShape->axisOfRotation.normal, cutShape->vectorLength );
	labelMap.insert( std::pair< std::string, _3DMath::Vector >( ( const char* )cutShape->label.c_str(), point ) );
}

void TwistyPuzzle::SetupDynamicLabelUsingCutShapeList( void )
{
	labelMap.clear();

	for( CutShapeList::const_iterator iter = cutShapeList.cbegin(); iter != cutShapeList.cend(); iter++ )
		SetupDynamicLabelUsingCutShape( *iter );
}

/*virtual*/ void TwistyPuzzle::UpdateCutShapeLabels( const _3DMath::AffineTransform& transform )
{
	if( labelMap.size() == 0 )
		return;

	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		TwistyPuzzle::CutShape* cutShape = *iter;
		cutShape->label = FindLabelForCutShape( cutShape, transform, normalTransform );
	}
}

wxString TwistyPuzzle::FindLabelForCutShape( const CutShape* cutShape, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform )
{
	_3DMath::Vector center, vector, point;
	transform.Transform( cutShape->axisOfRotation.center, center );
	normalTransform.Transform( cutShape->axisOfRotation.normal, vector );
	point.AddScale( center, vector, cutShape->vectorLength );

	wxString label;
	double smallestDistance = -1.0;

	for( LabelMap::iterator iter = labelMap.begin(); iter != labelMap.end(); iter++ )
	{
		double distance = iter->second.Distance( point );
		if( smallestDistance < 0.0 || distance < smallestDistance )
		{
			smallestDistance = distance;
			label = iter->first;
		}
	}

	return label;
}

TwistyPuzzle::CutShape* TwistyPuzzle::FindCutShapeNearestDirection( const _3DMath::Vector& direction, const _3DMath::AffineTransform& transform, TwistyPuzzle::CutShapeList::iterator* foundIter /*= nullptr*/ )
{
	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

	double smallestAngle = 2.0 * M_PI;
	CutShape* nearestCutShape = nullptr;

	if( foundIter )
		*foundIter = cutShapeList.end();

	for( TwistyPuzzle::CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		TwistyPuzzle::CutShape* cutShape = *iter;

		_3DMath::Vector normal;
		normalTransform.Transform( cutShape->axisOfRotation.normal, normal );

		double angle = normal.AngleBetween( direction );
		if( angle < smallestAngle )
		{
			smallestAngle = angle;
			nearestCutShape = cutShape;
			if( foundIter )
				*foundIter = iter;
		}
	}

	return nearestCutShape;
}

void TwistyPuzzle::MakeBox( double width, double height, double depth )
{
	Face* face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color = orange;
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color = red;
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color = green;
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->color = blue;
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color = white;
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->color = yellow;
	faceList.push_back( face );
}

void TwistyPuzzle::MakePolyhedron( Polyhedron polyhedron, double radius, _3DMath::TriangleMesh* triangleMesh /*= nullptr*/ )
{
	_3DMath::TriangleMesh triangleMeshStorage;
	if( !triangleMesh )
		triangleMesh = &triangleMeshStorage;

	switch( polyhedron )
	{
		case DODECAHEDRON:
		{
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 1.0, 1.0, 1.0 ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0 / PHI, PHI ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 1.0 / PHI, PHI, 0.0 ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( PHI, 0.0, 1.0 / PHI ) );
			break;
		}
		case ICOSAHEDRON:
		{
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0, PHI ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 1.0, PHI, 0.0 ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( PHI, 0.0, 1.0 ) );
			break;
		}
		case HEXADRON:
		{
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 1.0, 1.0, 1.0 ) );
			break;
		}
		case OCTAHEDRON:
		{
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 1.0, 0.0, 0.0 ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0, 0.0 ) );
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 0.0, 0.0, 1.0 ) );
			break;
		}
		case TETRAHEDRON:
		{
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 1.0, 0.0, -1.0 / sqrt( 2.0 ) ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -1.0, 0.0, -1.0 / sqrt( 2.0 ) ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 0.0, 1.0, 1.0 / sqrt( 2.0 ) ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 0.0, -1.0, 1.0 / sqrt( 2.0 ) ) ) );
			break;
		}
		case TRUNCATED_TETRAHEDRON:
		{
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 3.0, 1.0, 1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -3.0, -1.0, 1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -3.0, 1.0, -1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 3.0, -1.0, -1.0 ) ) );

			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 1.0, 3.0, 1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -1.0, -3.0, 1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -1.0, 3.0, -1.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 1.0, -3.0, -1.0 ) ) );

			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 1.0, 1.0, 3.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -1.0, -1.0, 3.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( -1.0, 1.0, -3.0 ) ) );
			triangleMesh->vertexArray->push_back( _3DMath::Vertex( _3DMath::Vector( 1.0, -1.0, -3.0 ) ) );
			break;
		}
		case TRUNCATED_OCTAHEDRON:
		{
			triangleMesh->AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0, 2.0 ) );
			break;
		}
	}

	_3DMath::AffineTransform transform;
	transform.linearTransform.SetScale( radius );
	triangleMesh->Transform( transform );

	triangleMesh->FindConvexHull();

	_3DMath::PolygonList polygonFaceList;
	triangleMesh->GeneratePolygonFaceList( polygonFaceList );

	int i = 0;

	for( _3DMath::PolygonList::iterator iter = polygonFaceList.begin(); iter != polygonFaceList.end(); iter++ )
	{
		_3DMath::Polygon* polygon = *iter;
		Face* face = new Face( polygon );
		face->color = ColorTable( i++ );
		faceList.push_back( face );
	}
}

_3DMath::Vector TwistyPuzzle::red( 1.0, 0.0, 0.0 );
_3DMath::Vector TwistyPuzzle::green( 0.0, 0.8, 0.0 );
_3DMath::Vector TwistyPuzzle::blue( 0.0, 0.0, 1.0 );
_3DMath::Vector TwistyPuzzle::magenta( 1.0, 0.0, 1.0 );
_3DMath::Vector TwistyPuzzle::cyan( 0.0, 1.0, 1.0 );
_3DMath::Vector TwistyPuzzle::yellow( 1.0, 1.0, 0.0 );
_3DMath::Vector TwistyPuzzle::orange( 1.0, 0.5, 0.0 );
_3DMath::Vector TwistyPuzzle::maroon( 153.0 / 255.0, 0.0, 56.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::white( 1.0, 1.0, 1.0 );
_3DMath::Vector TwistyPuzzle::pink( 255.0 / 255.0, 105.0 / 255.0, 180.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::lime( 174.0 / 255.0, 249.0 / 255.0, 44.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::indigo( 94.0 / 255.0, 120.0 / 255.0, 249.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::lightseagrean( 32.0 / 255.0, 178.0 / 255.0, 170.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::turquoiseblue( 0.0 / 255.0, 199.0 / 255.0, 140.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::eggshell( 252.0 / 255.0, 230.0 / 255.0, 201.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::firebrick( 178.0 / 255.0, 34.0 / 255.0, 34.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::olivedrab( 142.0 / 255.0, 142.0 / 255.0, 56.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::salmon( 198.0 / 255.0, 113.0 / 255.0, 113.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::brown( 165.0 / 255.0, 42.0 / 255.0, 42.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::aquamarine( 127.0 / 255.0, 255.0 / 255.0, 212.0 / 255.0 );

/*static*/ _3DMath::Vector TwistyPuzzle::ColorTable( int index )
{
	_3DMath::Vector* table[] =
	{
		&red,
		&green,
		&blue,
		&magenta,
		&cyan,
		&yellow,
		&orange,
		&maroon,
		&white,
		&lime,
		&indigo,
		&lightseagrean,
		&turquoiseblue,
		&eggshell,
		&firebrick,
		&olivedrab,
		&salmon,
		&brown,
		&aquamarine,
		&pink,
	};

	int tableSize = sizeof( table ) / sizeof( _3DMath::Vector* );

	_3DMath::Vector color = *table[ index % tableSize ];
	return color;
}

bool TwistyPuzzle::Load( const wxString& file )
{
	wxXmlDocument xmlDocument;
	wxFileInputStream fileInputStream( file );
	if( !xmlDocument.Load( fileInputStream ) )
		return false;

	if( !LoadFromXml( xmlDocument ) )
		return false;

	return true;
}

bool TwistyPuzzle::Save( const wxString& file ) const
{
	wxXmlDocument xmlDocument;
	if( !SaveToXml( xmlDocument ) )
		return false;

	wxFileOutputStream fileOutputStream( file );
	if( !xmlDocument.Save( fileOutputStream ) )
		return false;

	needsSaving = false;
	return true;
}

/*virtual*/ bool TwistyPuzzle::LoadFromXml( const wxXmlDocument& xmlDocument )
{
	const wxXmlNode* xmlRootNode = xmlDocument.GetRoot();

	if( xmlRootNode->GetName() != "TwistyPuzzle" )
		return false;

	Reset();

	_3DMath::FreeList< Face >( faceList );

	for( wxXmlNode* xmlNode = xmlRootNode->GetChildren(); xmlNode; xmlNode = xmlNode->GetNext() )
	{
		if( xmlNode->GetName() == "FacePool" )
		{
			for( wxXmlNode* xmlFaceNode = xmlNode->GetChildren(); xmlFaceNode; xmlFaceNode = xmlFaceNode->GetNext() )
			{
				Face* face = new Face( new _3DMath::Polygon() );
				faceList.push_back( face );

				if( !face->Load( xmlFaceNode ) )
					return false;
			}
		}
	}

	if( faceList.size() == 0 )
		return false;

	return true;
}

/*virtual*/ bool TwistyPuzzle::SaveToXml( wxXmlDocument& xmlDocument ) const
{
	wxXmlNode* xmlRootNode = new wxXmlNode( wxXML_ELEMENT_NODE, "TwistyPuzzle" );
	xmlDocument.SetRoot( xmlRootNode );

	wxClassInfo* classInfo = GetClassInfo();
	wxString className = classInfo->GetClassName();
	xmlRootNode->AddAttribute( "class_name", className );

	wxXmlNode* xmlFacePoolNode = new wxXmlNode( xmlRootNode, wxXML_ELEMENT_NODE, "FacePool" );
	for( FaceList::const_iterator iter = faceList.cbegin(); iter != faceList.cend(); iter++ )
	{
		const Face* face = *iter;
		wxXmlNode* xmlFaceNode = new wxXmlNode( xmlFacePoolNode, wxXML_ELEMENT_NODE, "Face" );
		if( !face->Save( xmlFaceNode ) )
			return false;
	}

	// TODO: Save/restore history?

	return true;
}

/*virtual*/ void TwistyPuzzle::IncrementallySolve( RotationList& rotationList ) const
{
}

/*virtual*/ TwistyPuzzle::Rotation* TwistyPuzzle::CalculateNearestRotation( CutShape* cutShape )
{
	double turnCount = 0.0;
	double rotationAngle = 0.0;
	while( fabs( rotationAngle - cutShape->rotationAngleForAnimation ) > cutShape->rotationAngleForSingleTurn / 2.0 )
	{
		if( rotationAngle < cutShape->rotationAngleForAnimation )
		{
			turnCount += 1.0;
			rotationAngle += cutShape->rotationAngleForSingleTurn;
		}
		else
		{
			turnCount -= 1.0;
			rotationAngle -= cutShape->rotationAngleForSingleTurn;
		}
	}

	if( fabs( turnCount ) < EPSILON )
		return nullptr;

	Rotation* rotation = new Rotation( cutShape->GetHandle(), Rotation::DIR_CCW, turnCount );
	return rotation;
}

/*virtual*/ void TwistyPuzzle::EnqueueRandomRotations( _3DMath::Random& random, int rotationCount )
{
	for( int i = 0; i < rotationCount; i++ )
	{
		int j = random.Integer( 0, cutShapeList.size() - 1 );
		CutShapeList::iterator iter = cutShapeList.begin();
		while( j > 0 )
		{
			iter++;
			j--;
		}

		const CutShape* cutShape = *iter;

		Rotation::Direction rotDir = Rotation::DIR_CCW;
		if( random.Integer( 0, 1 ) )
			rotDir = Rotation::DIR_CW;

		EnqueueRotation( new Rotation( cutShape->GetHandle(), rotDir, 1.0 ) );
	}
}

/*virtual*/ void TwistyPuzzle::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, bool renderAxisLabels, bool renderBorders )
{
	if( !shaderProgram && renderBorders )
	{
		shaderProgram = new ShaderProgram();
		if( !shaderProgram->Load( "face" ) )
		{
			wxMessageBox( "Failed to load face shader program.", "Error", wxICON_ERROR | wxCENTRE, wxGetApp().GetFrame() );
			wxAbort();
		}
	}

	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

	if( renderBorders )
	{
		if( !shaderProgram->Bind() )
		{
			wxMessageBox( "Failed to find face shader program.", "Error", wxICON_ERROR | wxCENTRE, wxGetApp().GetFrame() );
			renderBorders = false;
		}
		else
		{
			shaderProgram->SetUniformFloat( "borderThickness", 0.05 );
			shaderProgram->SetUniformVector( "borderColor", _3DMath::Vector( 0.0, 0.0, 0.0 ) );
		}
	}

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;
		face->UpdateTessellationIfNeeded();
		face->Render( renderer, renderMode, transform, normalTransform, ( renderBorders ? shaderProgram : nullptr ) );
	}

	if( renderBorders )
		shaderProgram->Unbind();

	if( renderMode == GL_RENDER )
	{
		for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
		{
			CutShape* cutShape = *iter;
			if( cutShape->GetHandle() == selectedObjectHandle )
			{
				_3DMath::Vector color( 0.5, 0.5, 0.5 );
				glDepthMask( GL_FALSE );
				renderer.DrawSurface( *cutShape->surface, color, 0.2, &transform );
				glDepthMask( GL_TRUE );
			}
		}
	}

	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		CutShape* cutShape = *iter;

		_3DMath::Vector vector, position, color;

		transform.Transform( cutShape->axisOfRotation.center, position );
		normalTransform.Transform( cutShape->axisOfRotation.normal, vector );

		vector.Scale( cutShape->vectorLength );

		if( cutShape->GetHandle() == selectedObjectHandle )
			color.Set( 0.8, 0.8, 0.8 );
		else
			color.Set( 0.5, 0.5, 0.5 );

		if( renderMode == GL_SELECT )
			glLoadName( cutShape->GetHandle() );

		renderer.DrawVector( vector, position, color, 0.5, 0.5 );

		if( renderAxisLabels && renderMode == GL_RENDER && !cutShape->label.empty() )
		{
			FontSys::System* fontSystem = wxGetApp().GetFontSystem();
			glColor4d( 0.9, 0.9, 0.9, 0.5 );
			fontSystem->SetFont( "ChanticleerRomanNF.ttf" );
			fontSystem->SetJustification( FontSys::System::JUSTIFY_CENTER );
			fontSystem->SetWordWrap( false );
			fontSystem->SetLineHeight( 1.0 );

			glPushAttrib( GL_LIGHTING_BIT | GL_ENABLE_BIT );
			glDisable( GL_LIGHTING );
			glDisable( GL_DEPTH_TEST );

			_3DMath::Vector arrowPosition = position + vector;

			glMatrixMode( GL_MODELVIEW_MATRIX );
			glPushMatrix();
			glTranslatef( arrowPosition.x, arrowPosition.y, arrowPosition.z );

			fontSystem->DrawTextCPtr( cutShape->label.c_str(), true );

			glPopMatrix();
			glPopAttrib();
		}
	}
}

/*virtual*/ void TwistyPuzzle::RenderStats( const _3DMath::TimeKeeper& timeKeeper )
{
	double deltaTimeSeconds = timeKeeper.GetDeltaTimeSeconds();
	double framesPerSecond = 1.0 / deltaTimeSeconds;

	int triangleCount = 0;
	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;
		face->UpdateTessellationIfNeeded();
		triangleCount += face->polygon->indexTriangleList->size();
	}

	FontSys::System* fontSystem = wxGetApp().GetFontSystem();
	glColor3d( 1.0, 1.0, 1.0 );
	fontSystem->SetFont( "Anonymous_Pro.ttf" );
	fontSystem->SetJustification( FontSys::System::JUSTIFY_LEFT );
	fontSystem->SetWordWrap( false );
	fontSystem->SetLineHeight( 0.25 );

	glPushAttrib( GL_LIGHTING_BIT | GL_ENABLE_BIT );
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	char buffer[ 256 ];

	sprintf_s( buffer, sizeof( buffer ), "FPS: %02.2f", framesPerSecond );
	fontSystem->DrawTextCPtr( buffer );

	glTranslatef( 0.f, fontSystem->GetLineHeight() * 1.5, 0.f );

	sprintf_s( buffer, sizeof( buffer ), "Faces: %d", int( faceList.size() ) );
	fontSystem->DrawTextCPtr( buffer );

	glTranslatef( 0.f, fontSystem->GetLineHeight() * 1.5, 0.f );

	sprintf_s( buffer, sizeof( buffer ), "Triangles: %d", triangleCount );
	fontSystem->DrawTextCPtr( buffer );

	glPopAttrib();
}

/*static*/ bool TwistyPuzzle::SaveVector( const wxString& name, wxXmlNode* xmlNode, const _3DMath::Vector& vector )
{
	wxString xStr, yStr, zStr;

	xStr = wxString::Format( "%1.16f", vector.x );
	yStr = wxString::Format( "%1.16f", vector.y );
	zStr = wxString::Format( "%1.16f", vector.z );

	xmlNode->AddAttribute( name + "_x", xStr );
	xmlNode->AddAttribute( name + "_y", yStr );
	xmlNode->AddAttribute( name + "_z", zStr );

	return true;
}

/*static*/ bool TwistyPuzzle::LoadVector( const wxString& name, const wxXmlNode* xmlNode, _3DMath::Vector& vector )
{
	wxString xStr = xmlNode->GetAttribute( name + "_x" );
	wxString yStr = xmlNode->GetAttribute( name + "_y" );
	wxString zStr = xmlNode->GetAttribute( name + "_z" );

	if( !xStr.ToCDouble( &vector.x ) )
		return false;

	if( !yStr.ToCDouble( &vector.y ) )
		return false;

	if( !zStr.ToCDouble( &vector.z ) )
		return false;

	return true;
}

/*static*/ bool TwistyPuzzle::SaveNumber( const wxString& name, wxXmlNode* xmlNode, double number )
{
	wxString numberStr = wxString::Format( "%1.16f", number );
	xmlNode->AddAttribute( name, numberStr );
	return true;
}

/*static*/ bool TwistyPuzzle::LoadNumber( const wxString& name, const wxXmlNode* xmlNode, double& number )
{
	wxString numberStr = xmlNode->GetAttribute( name );
	return numberStr.ToCDouble( &number );
}

void TwistyPuzzle::CollectAdjacentEdges( const Face* face, _3DMath::LineSegmentList& lineSegmentList ) const
{
	lineSegmentList.clear();

	_3DMath::Plane plane;
	face->polygon->GetPlane( plane );

	// Note that we're not compressing the list, so there may be duplicates.
	for( FaceList::const_iterator iter = faceList.cbegin(); iter != faceList.cend(); iter++ )
	{
		const Face* otherFace = *iter;
		if( otherFace == face )
			continue;

		for( int i = 0; i < ( signed )otherFace->polygon->vertexArray->size(); i++ )
		{
			int j = ( i + 1 ) % otherFace->polygon->vertexArray->size();

			_3DMath::LineSegment lineSegment;
			lineSegment.vertex[0] = ( *otherFace->polygon->vertexArray )[i];
			lineSegment.vertex[1] = ( *otherFace->polygon->vertexArray )[j];

			_3DMath::Plane::Side side[2];
			side[0] = plane.GetSide( lineSegment.vertex[0] );
			side[1] = plane.GetSide( lineSegment.vertex[1] );

			if( ( side[0] == _3DMath::Plane::SIDE_NEITHER && side[1] != _3DMath::Plane::SIDE_NEITHER ) ||
				( side[1] == _3DMath::Plane::SIDE_NEITHER && side[0] != _3DMath::Plane::SIDE_NEITHER ) )
			{
				lineSegmentList.push_back( lineSegment );
			}
		}
	}
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::Face
//---------------------------------------------------------------------------------

TwistyPuzzle::Face::Face( _3DMath::Polygon* polygon )
{
	this->polygon = polygon;
	tessellationNeeded = true;
	boundCutShapeHandle = 0;
}

TwistyPuzzle::Face::~Face( void )
{
	delete polygon;
}

bool TwistyPuzzle::Face::Save( wxXmlNode* xmlFaceNode ) const
{
	SaveVector( "color", xmlFaceNode, color );
	
	wxXmlNode* xmlVertexPoolNode = new wxXmlNode( xmlFaceNode, wxXML_ELEMENT_NODE, "VertexPool" );

	for( int i = 0; i < ( signed )polygon->vertexArray->size(); i++ )
	{
		wxXmlNode* xmlVertexNode = new wxXmlNode( xmlVertexPoolNode, wxXML_ELEMENT_NODE, "Vertex" );
		SaveVector( "", xmlVertexNode, ( *polygon->vertexArray )[i] );
	}

	return true;
}

bool TwistyPuzzle::Face::Load( const wxXmlNode* xmlFaceNode )
{
	if( !LoadVector( "color", xmlFaceNode, color ) )
		return false;

	polygon->vertexArray->clear();

	for( wxXmlNode* xmlNode = xmlFaceNode->GetChildren(); xmlNode; xmlNode = xmlNode->GetNext() )
	{
		if( xmlNode->GetName() == "VertexPool" )
		{
			_3DMath::VectorList vertexList;

			for( wxXmlNode* xmlVertexNode = xmlNode->GetChildren(); xmlVertexNode; xmlVertexNode = xmlVertexNode->GetNext() )
			{
				_3DMath::Vector vertex;
				if( !LoadVector( "", xmlVertexNode, vertex ) )
					return false;

				vertexList.push_back( vertex );
			}
			
			_3DMath::VectorList::reverse_iterator iter = vertexList.rbegin();
			while( iter != vertexList.rend() )
			{
				polygon->vertexArray->push_back( *iter );
				iter++;
			}
		}
	}

	if( polygon->vertexArray->size() == 0 )
		return false;

	return true;
}

void TwistyPuzzle::Face::UpdateTessellationIfNeeded( void )
{
	if( tessellationNeeded )
	{
		polygon->Tessellate();
		tessellationNeeded = false;
	}
}

// TODO: Add lighting as optionally enabled from the render menu.
void TwistyPuzzle::Face::Render( _3DMath::Renderer& renderer, GLenum renderMode, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform, ShaderProgram* shaderProgram ) const
{
	_3DMath::AffineTransform renderTransform;

	CutShape* cutShape = ( CutShape* )_3DMath::HandleObject::Dereference( boundCutShapeHandle );
	if( !cutShape )
		renderTransform = transform;
	else
	{
		_3DMath::AffineTransform animationTransform;
		animationTransform.SetRotation( cutShape->axisOfRotation, cutShape->rotationAngleForAnimation );
		renderTransform.Concatinate( animationTransform, transform );
	}

	if( renderMode == GL_SELECT )
		glLoadName( GetHandle() );

	glColor3d( color.x, color.y, color.z );

	for( _3DMath::IndexTriangleList::const_iterator iter = polygon->indexTriangleList->cbegin(); iter != polygon->indexTriangleList->cend(); iter++ )
	{
		const _3DMath::IndexTriangle& indexTriangle = *iter;

		_3DMath::Triangle triangle;
		indexTriangle.GetTriangle( triangle, polygon->vertexArray );
		
		if( shaderProgram )
		{
			int lineSegCount = 0;
			const int maxLineSegCount = 4;
			_3DMath::Vector lineSegEndPointA[ maxLineSegCount ];
			_3DMath::Vector lineSegEndPointB[ maxLineSegCount ];

			for( int i = 0; i < ( signed )polygon->vertexArray->size(); i++ )
			{
				int j = ( i + 1 ) % polygon->vertexArray->size();
				
				int k;
				for( k = 0; k < 3; k++ )
					if( indexTriangle.vertex[k] == i || indexTriangle.vertex[k] == j )
						break;

				if( k < 3 )
				{
					renderTransform.Transform( ( *polygon->vertexArray )[i], lineSegEndPointA[ lineSegCount ] );
					renderTransform.Transform( ( *polygon->vertexArray )[j], lineSegEndPointB[ lineSegCount ] );
					lineSegCount++;
					if( lineSegCount == maxLineSegCount )
						break;
				}
			}

			while( lineSegCount < maxLineSegCount )
			{
				lineSegEndPointA[ lineSegCount ].Set( 100.0, 100.0, 100.0 );
				lineSegEndPointB[ lineSegCount ].Set( 200.0, 200.0, 200.0 );
				lineSegCount++;
			}

			shaderProgram->SetUniformVectorArray( "lineSegEndPointA", lineSegEndPointA, lineSegCount );
			shaderProgram->SetUniformVectorArray( "lineSegEndPointB", lineSegEndPointB, lineSegCount );
		}

		glBegin( GL_TRIANGLES );
		
		for( int i = 0; i < 3; i++ )
		{
			_3DMath::Vector& vertex = triangle.vertex[i];
			renderTransform.Transform( vertex );
			glVertex3d( vertex.x, vertex.y, vertex.z );
		}

		glEnd();
	}
}

bool TwistyPuzzle::Face::IsCapturedByCutShape( CutShape* cutShape ) const
{
	const_cast< Face* >( this )->UpdateTessellationIfNeeded();

	return IsCapturedBySurface( cutShape->surface, cutShape->captureSide );
}

// TODO: There is a bug here; this logic does not always give us what we want.
bool TwistyPuzzle::Face::IsCapturedBySurface( _3DMath::Surface* surface, _3DMath::Surface::Side captureSide ) const
{
	int insideCount = 0;
	int outsideCount = 0;

	_3DMath::IndexTriangleList::const_iterator triangleIter = polygon->indexTriangleList->cbegin();
	while( triangleIter != polygon->indexTriangleList->cend() )
	{
		const _3DMath::IndexTriangle& indexTriangle = *triangleIter;

		_3DMath::Triangle triangle;
		indexTriangle.GetTriangle( triangle, polygon->vertexArray );

		_3DMath::Vector triangleCenter;
		triangle.GetCenter( triangleCenter );

		_3DMath::Surface::Side side = surface->GetSide( triangleCenter );
		if( side == _3DMath::Surface::INSIDE )
			insideCount++;
		else if( side == _3DMath::Surface::OUTSIDE )
			outsideCount++;

		triangleIter++;
	}

	_3DMath::Surface::Side dominantSide = _3DMath::Surface::OUTSIDE;
	if( insideCount > outsideCount )
		dominantSide = _3DMath::Surface::INSIDE;

	return( dominantSide == captureSide ) ? true : false;
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::CutShape
//---------------------------------------------------------------------------------

TwistyPuzzle::CutShape::CutShape( void )
{
	axisOfRotation.center.Set( 0.0, 0.0, 0.0 );
	axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	captureSide = _3DMath::Surface::OUTSIDE;
	rotationAngleForSingleTurn = 0.0;
	rotationAngleForAnimation = 0.0;
	vectorLength = 10.0;
	surface = nullptr;
}

/*virtual*/ TwistyPuzzle::CutShape::~CutShape( void )
{
	delete surface;
}

/*virtual*/ void TwistyPuzzle::CutShape::CutAndCapture( FaceList& faceList, FaceList& capturedFaceList, double eps /*= EPSILON*/ )
{
	capturedFaceList.clear();

	FaceList::iterator iter = faceList.begin();
	while( iter != faceList.end() )
	{
		FaceList::iterator nextIter = iter;
		nextIter++;

		Face* face = *iter;

		_3DMath::Polygon polygonArray[2];
		if( face->polygon->SplitAgainstSurface( surface, polygonArray, 20.0, 1.0, eps ) )
		{
			for( int i = 0; i < 2; i++ )
			{
				_3DMath::Polygon* polygon = new _3DMath::Polygon();
				polygonArray[i].GetCopy( *polygon );
				Face* newFace = new Face( polygon );
				newFace->color = face->color;
				faceList.push_front( newFace );
			}

			delete face;
			faceList.erase( iter );
		}

		iter = nextIter;
	}

	for( FaceList::const_iterator iter = faceList.cbegin(); iter != faceList.cend(); iter++ )
	{
		Face* face = *iter;
		if( face->IsCapturedByCutShape( this ) )
			capturedFaceList.push_back( face );
	}
}

//---------------------------------------------------------------------------------
//                              TwistyPuzzle::Rotation
//---------------------------------------------------------------------------------

TwistyPuzzle::Rotation::Rotation( int cutShapeHandle, Direction direction /*= DIR_CCW*/, double turnCount /*= 1.0*/, int flags /*= 0*/ )
{
	this->cutShapeHandle = cutShapeHandle;
	this->direction = direction;
	this->turnCount = turnCount;
	this->flags = flags;
	newRotationSpeedCoeficient = 0.0;
}

TwistyPuzzle::Rotation::~Rotation( void )
{
}

// TwistyPuzzle.cpp