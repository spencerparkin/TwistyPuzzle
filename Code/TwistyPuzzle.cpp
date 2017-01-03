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

void TwistyPuzzle::Clear( void )
{
	_3DMath::FreeList< Face >( faceList );
	_3DMath::FreeList< CutShape >( cutShapeList );
	_3DMath::FreeList< Rotation >( rotationQueue );
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

		CutShape* cutShape = ( CutShape* )_3DMath::HandleObject::Dereference( rotation->cutShapeHandle );
		if( cutShape )
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
				face->rotationAngleForAnimation = -rotationAngle;
			}
		}

		delete rotation;
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

/*virtual*/ void TwistyPuzzle::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle )
{
	if( renderMode == GL_RENDER )
	{
		for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
		{
			Face* face = *iter;
			if( !face->polygon )
				continue;

			if( face->tessellationNeeded )
			{
				face->polygon->Tessellate();
				face->tessellationNeeded = false;
			}

			_3DMath::AffineTransform renderTransform;

			// TODO: If we're rendering wire frame, we might shrink the polygon about its center
			//       just a tad so that it's easy to see the lines that would otherwise be co-
			//       incident with other lines.

			if( face->rotationAngleForAnimation == 0.0 )
				renderTransform = transform;
			else
			{
				_3DMath::AffineTransform animationTransform;
				animationTransform.SetRotation( face->axisOfRotation, face->rotationAngleForAnimation );
				renderTransform.Concatinate( animationTransform, transform );
			}

			renderer.Color( face->color );
			renderer.DrawPolygon( *face->polygon, &renderTransform );
		}
	}

	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

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

		renderer.DrawVector( vector, cutShape->axisOfRotation.center, color, 0.5, 0.5 );
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
		if( face->polygon->SplitAgainstSurface( surface, polygonList, 0.1 ) )
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

	iter = faceList.begin();
	while( iter != faceList.end() )
	{
		Face* face = *iter;
		int insideCount = 0;
		int outsideCount = 0;

		for( int i = 0; i < ( signed )face->polygon->vertexArray->size(); i++ )
		{
			const _3DMath::Vector& point = ( *face->polygon->vertexArray )[i];
			_3DMath::Surface::Side side = surface->GetSide( point, 0.05 );	// No, we should not need an epsilon this big!
			if( side == _3DMath::Surface::INSIDE )
				insideCount++;
			else if( side == _3DMath::Surface::OUTSIDE )
				outsideCount++;
		}

		wxASSERT( insideCount == 0 || outsideCount == 0 );

		if( ( insideCount > 0 && captureSide == _3DMath::Surface::INSIDE ) ||
			( outsideCount > 0 && captureSide == _3DMath::Surface::OUTSIDE ) )
		{
			capturedFaceList.push_back( face );
		}

		iter++;
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
}

TwistyPuzzle::Rotation::~Rotation( void )
{
}

// TwistyPuzzle.cpp