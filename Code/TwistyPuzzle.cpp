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

/*virtual*/ void TwistyPuzzle::IncrementallySolve( RotationList& rotationList ) const
{
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
	// TODO: We might select faces, but until then bail if we're not in render mode.
	if( renderMode != GL_RENDER )
		return;
	
	glLineWidth( 2.5f );

	_3DMath::AffineTransform renderTransform;

	_3DMath::AffineTransform animationTransform;
	animationTransform.SetRotation( axisOfRotation, rotationAngleForAnimation );
	renderTransform.Concatinate( animationTransform, transform );

	renderer.Color( color );
	renderer.DrawPolygon( *polygon, &renderTransform );

	if( renderer.drawStyle == _3DMath::Renderer::DRAW_STYLE_SOLID )
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

	iter = faceList.begin();
	while( iter != faceList.end() )
	{
		Face* face = *iter;
		face->UpdateTessellationIfNeeded();

		int insideCount = 0;
		int outsideCount = 0;

		_3DMath::IndexTriangleList::const_iterator triangleIter = face->polygon->indexTriangleList->cbegin();
		while( triangleIter != face->polygon->indexTriangleList->cend() )
		{
			const _3DMath::IndexTriangle& indexTriangle = *triangleIter;

			_3DMath::Triangle triangle;
			indexTriangle.GetTriangle( triangle, face->polygon->vertexArray );

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

		if( dominantSide == captureSide )
			capturedFaceList.push_back( face );

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