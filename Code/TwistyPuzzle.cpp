// TwistyPuzzle.cpp

#include "TwistyPuzzle.h"
#include <Surface.h>
#include <Plane.h>
#include <ListFunctions.h>

//---------------------------------------------------------------------------------
//                                  TwistyPuzzle
//---------------------------------------------------------------------------------

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
}

void TwistyPuzzle::SetType( Type type )
{
	Clear();

	this->type = type;

	switch( type )
	{
		case DEBUG:
		{
			Face* face = new Face( new _3DMath::Polygon() );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 0.5, -2.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 3.0, -2.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 3.0, -1.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 2.0, -1.8, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 3.5, 2.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 1.0, 1.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( 0.5, 3.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.0, 3.1, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.0, 1.8, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -0.4, 2.2, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -0.5, 1.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.6, 0.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.6, 2.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.5, 2.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.5, 2.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -3.5, 2.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -3.5, -1.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.5, -1.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.5, -0.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -0.5, -1.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -1.0, -2.5, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -1.5, -2.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -2.0, -3.0, 0.0 ) );
			face->polygon->vertexArray->push_back( _3DMath::Vector( -1.0, -3.5, 0.0 ) );
			face->color.Set( 1.0, 1.0, 1.0 );
			faceList.push_back( face );

			break;
		}
		case CLASSIC_2x2x2:
		{
			MakeBox( 10.0, 10.0, 10.0 );

			CutShape* cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
			cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
			cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
			cutShapeList.push_back( cutShape );

			cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
			cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
			cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
			cutShapeList.push_back( cutShape );

			cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
			cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
			cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
			cutShapeList.push_back( cutShape );

			break;
		}
		case CLASSIC_3x3x3:
		case CLASSIC_4x4x4:
		case BUBBLOID_3x3x4:
		case BUBBLOID_3x4x4:
		case CURVEY_COPTER:
		{
			// TODO: I believe we may be able to simulate the jumble move on this puzzle!
			break;
		}
		case REX_CUBE:
		{
			break;
		}
	}
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

void TwistyPuzzle::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform )
{
	// TODO: Turn on back-face culling.

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
		renderTransform.Concatinate( face->transform, transform );

		renderer.drawStyle = _3DMath::Renderer::DRAW_STYLE_WIRE_FRAME;
		renderer.Color( face->color );
		renderer.DrawPolygon( *face->polygon, &renderTransform );
	}

	// TODO: Draw these with alpha-blending turned on.
	// TODO: Use OpenGL selection mechanism on these so that we can select the cut-shape?

	_3DMath::LinearTransform normalTransform;
	transform.linearTransform.GetNormalTransform( normalTransform );

	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		CutShape* cutShape = *iter;

		_3DMath::Vector vector, position, color;

		transform.Transform( cutShape->axisOfRotation.center, position );
		normalTransform.Transform( cutShape->axisOfRotation.normal, vector );

		vector.Scale( 10.0 );

		color.Set( 0.5, 0.5, 0.5 );
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
	transform.Identity();
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
	rotationAngleForSingleTurn = 0.0;
	surface = nullptr;
}

TwistyPuzzle::CutShape::~CutShape( void )
{
	delete surface;
}

void TwistyPuzzle::CutShape::CutAndCapture( FaceList& faceList )
{
}

// TwistyPuzzle.cpp