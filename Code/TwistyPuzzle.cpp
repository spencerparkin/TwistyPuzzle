// TwistyPuzzle.cpp

#include "TwistyPuzzle.h"
#include <Surface.h>
#include <ListFunctions.h>

//---------------------------------------------------------------------------------
//                                  TwistyPuzzle
//---------------------------------------------------------------------------------

wxIMPLEMENT_ABSTRACT_CLASS( TwistyPuzzle, wxObject )

TwistyPuzzle::TwistyPuzzle( void )
{
}

/*virtual*/ TwistyPuzzle::~TwistyPuzzle( void )
{
	Clear();
}

/*virtual*/ void TwistyPuzzle::Clear( void )
{
	_3DMath::FreeList< Face >( faceList );
	_3DMath::FreeList< CutShape >( cutShapeList );
	_3DMath::FreeList< Rotation >( rotationQueue );
}

/*virtual*/ bool TwistyPuzzle::SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown )
{
	return false;
}

void TwistyPuzzle::EnqueueRotation( Rotation* rotation )
{
	rotationQueue.push_back( rotation );
}

bool TwistyPuzzle::ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper )
{
	bool motion = false;

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;
		if( face->rotationAngleForAnimation != 0.0 )
		{
			double rotationRateRadiansPerSecond = -face->rotationAngleForAnimation * 10.0;
			double thresholdAngle = 0.01;

			if( fabs( face->rotationAngleForAnimation ) < thresholdAngle )
				face->rotationAngleForAnimation = 0.0;
			else
				face->rotationAngleForAnimation += rotationRateRadiansPerSecond * timeKeeper.GetDeltaTimeSeconds();

			motion = true;
		}
	}

	if( !motion )
	{
		if( rotationQueue.size() == 0 )
			return false;

		RotationList::iterator iter = rotationQueue.begin();
		Rotation* rotation = *iter;
		rotationQueue.erase( iter );

		_3DMath::HandleObject* object = _3DMath::HandleObject::Dereference( rotation->cutShapeHandle );
		CutShape* cutShape = dynamic_cast< CutShape* >( object );
		if( cutShape )
		{
			if( ApplyCutShapeWithRotation( cutShape, rotation ) )
			{
				if( !rotation->isHistory )
				{
					// TODO: Add to history buffer.
				}
			}
		}

		delete rotation;
	}

	return true;
}

/*virtual*/ bool TwistyPuzzle::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	FaceList capturedFaceList;
	cutShape->CutAndCapture( faceList, capturedFaceList );

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
		face->axisOfRotation = cutShape->axisOfRotation;
		face->rotationAngleForAnimation -= rotationAngle;
	}

	return true;
}

void TwistyPuzzle::MakeBox( double width, double height, double depth )
{
	Face* face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color.Set( 1.0, 1.0, 1.0 );
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color.Set( 1.0, 1.0, 0.0 );
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color.Set( 1.0, 0.0, 0.0 );
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->color.Set( 1.0, 0.5, 0.0 );
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color.Set( 0.0, 0.0, 1.0 );
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->color.Set( 0.0, 1.0, 0.0 );
	faceList.push_back( face );
}

void TwistyPuzzle::MakePolyhedron( Polyhedron polyhedron, double radius )
{
	_3DMath::TriangleMesh triangleMesh;

	switch( polyhedron )
	{
		case DODECAHEDRON:
		{
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( 1.0, 1.0, 1.0 ) );
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0 / PHI, PHI ) );
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( 1.0 / PHI, PHI, 0.0 ) );
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( PHI, 0.0, 1.0 / PHI ) );
			break;
		}
		case ICOSAHEDRON:
		{
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( 0.0, 1.0, PHI ) );
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( 1.0, PHI, 0.0 ) );
			triangleMesh.AddSymmetricVertices( _3DMath::Vector( PHI, 0.0, 1.0 ) );
			break;
		}
		case HEXADRON:
		{
			break;
		}
		case OCTAHEDRON:
		{
			break;
		}
		case TETRAHEDRON:
		{
			break;
		}
	}

	_3DMath::AffineTransform transform;
	transform.linearTransform.SetScale( radius );
	triangleMesh.Transform( transform );

	triangleMesh.FindConvexHull();

	_3DMath::PolygonList polygonFaceList;
	triangleMesh.GeneratePolygonFaceList( polygonFaceList );

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
_3DMath::Vector TwistyPuzzle::green( 0.0, 1.0, 0.0 );
_3DMath::Vector TwistyPuzzle::blue( 0.0, 0.0, 1.0 );
_3DMath::Vector TwistyPuzzle::magenta( 1.0, 0.0, 1.0 );
_3DMath::Vector TwistyPuzzle::cyan( 0.0, 1.0, 1.0 );
_3DMath::Vector TwistyPuzzle::yellow( 1.0, 1.0, 0.0 );
_3DMath::Vector TwistyPuzzle::orange( 1.0, 0.5, 0.0 );
_3DMath::Vector TwistyPuzzle::maroon( 153.0 / 255.0, 0.0, 56.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::white( 1.0, 1.0, 1.0 );
_3DMath::Vector TwistyPuzzle::pink( 249.0 / 255.0, 0.0, 162.0 );
_3DMath::Vector TwistyPuzzle::lime( 174.0 / 255.0, 249.0 / 255.0, 44.0 / 255.0 );
_3DMath::Vector TwistyPuzzle::indigo( 94.0 / 255.0, 120.0 / 255.0, 249.0 / 255.0 );

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
		&pink,
		&lime,
		&indigo,
	};

	int tableSize = sizeof( table ) / sizeof( _3DMath::Vector* );

	return *table[ index % tableSize ];
}

bool TwistyPuzzle::Load( const wxString& file )
{
	return false;
}

bool TwistyPuzzle::Save( const wxString& file ) const
{
	return false;
}

/*virtual*/ void TwistyPuzzle::IncrementallySolve( RotationList& rotationList ) const
{
}

/*virtual*/ TwistyPuzzle::Rotation* TwistyPuzzle::CalculateNearestRotation( CutShape* cutShape, double currentRotationAngle )
{
	double turnCount = fmod( currentRotationAngle, cutShape->rotationAngleForSingleTurn );
	turnCount = floor( turnCount );
	if( fabs( turnCount ) < EPSILON )
		return nullptr;

	Rotation* rotation = new Rotation( cutShape->GetHandle(), Rotation::DIR_CCW, turnCount );
	return rotation;
}

/*virtual*/ void TwistyPuzzle::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle )
{
	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;
		face->UpdateTessellationIfNeeded();
		face->Render( renderer, renderMode, transform, normalTransform );
	}

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

		vector.Scale( 10.0 );

		if( cutShape->GetHandle() == selectedObjectHandle )
			color.Set( 0.8, 0.8, 0.8 );
		else
			color.Set( 0.5, 0.5, 0.5 );

		if( renderMode == GL_SELECT )
			glLoadName( cutShape->GetHandle() );

		renderer.DrawVector( vector, position, color, 0.5, 0.5 );
	}
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::Face
//---------------------------------------------------------------------------------

TwistyPuzzle::Face::Face( _3DMath::Polygon* polygon )
{
	this->polygon = polygon;
	tessellationNeeded = true;
	rotationAngleForAnimation = 0.0;
}

TwistyPuzzle::Face::~Face( void )
{
	delete polygon;
}

void TwistyPuzzle::Face::UpdateTessellationIfNeeded( void )
{
	if( tessellationNeeded )
	{
		polygon->Tessellate();
		tessellationNeeded = false;
	}
}

void TwistyPuzzle::Face::Render( _3DMath::Renderer& renderer, GLenum renderMode, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform ) const
{
	glLineWidth( 2.5f );

	_3DMath::AffineTransform renderTransform;

	_3DMath::AffineTransform animationTransform;
	animationTransform.SetRotation( axisOfRotation, rotationAngleForAnimation );
	renderTransform.Concatinate( animationTransform, transform );

	if( renderMode == GL_SELECT )
		glLoadName( GetHandle() );

	renderer.Color( color );
	renderer.DrawPolygon( *polygon, &renderTransform );

	if( renderer.drawStyle == _3DMath::Renderer::DRAW_STYLE_SOLID && renderMode == GL_RENDER )
	{
		renderer.drawStyle = _3DMath::Renderer::DRAW_STYLE_WIRE_FRAME;

		_3DMath::AffineTransform scaleTransform;
		scaleTransform.linearTransform.SetScale( 1.01 );

		_3DMath::AffineTransform silhouetteTransform;
		silhouetteTransform.Concatinate( scaleTransform, renderTransform );

		renderer.Color( _3DMath::Vector( 0.0, 0.0, 0.0 ), 1.0 );
		renderer.DrawPolygon( *polygon, &silhouetteTransform );

		renderer.drawStyle = _3DMath::Renderer::DRAW_STYLE_SOLID;
	}
}

// TODO: There is a bug here; this logic does not always give us what we want.
bool TwistyPuzzle::Face::IsCapturedByCutShape( CutShape* cutShape ) const
{
	const_cast< Face* >( this )->UpdateTessellationIfNeeded();

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

		_3DMath::Surface::Side side = cutShape->surface->GetSide( triangleCenter );
		if( side == _3DMath::Surface::INSIDE )
			insideCount++;
		else if( side == _3DMath::Surface::OUTSIDE )
			outsideCount++;

		triangleIter++;
	}

	_3DMath::Surface::Side dominantSide = _3DMath::Surface::OUTSIDE;
	if( insideCount > outsideCount )
		dominantSide = _3DMath::Surface::INSIDE;

	return( dominantSide == cutShape->captureSide ) ? true : false;
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
	surface = nullptr;
}

TwistyPuzzle::CutShape::~CutShape( void )
{
	delete surface;
}

void TwistyPuzzle::CutShape::CutAndCapture( FaceList& faceList, FaceList& capturedFaceList )
{
	capturedFaceList.clear();

	FaceList::iterator iter = faceList.begin();
	while( iter != faceList.end() )
	{
		FaceList::iterator nextIter = iter;
		nextIter++;

		Face* face = *iter;

		_3DMath::PolygonList polygonList;
		if( face->polygon->SplitAgainstSurface( surface, polygonList, 1.0 ) )
		{
			while( polygonList.size() > 0 )
			{
				_3DMath::PolygonList::iterator polyIter = polygonList.begin();
				_3DMath::Polygon* polygon = *polyIter;
				polygonList.erase( polyIter );
				Face* newFace = new Face( polygon );
				newFace->color = face->color;
				faceList.push_front( newFace );
			}

			delete face;
			faceList.erase( iter );
		}

		iter = nextIter;
	}

	Capture( faceList, capturedFaceList );
}

void TwistyPuzzle::CutShape::Capture( const FaceList& faceList, FaceList& capturedFaceList )
{
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

TwistyPuzzle::Rotation::Rotation( int cutShapeHandle, Direction direction, double turnCount )
{
	this->cutShapeHandle = cutShapeHandle;
	this->direction = direction;
	this->turnCount = turnCount;
	isHistory = false;
}

TwistyPuzzle::Rotation::~Rotation( void )
{
}

// TwistyPuzzle.cpp