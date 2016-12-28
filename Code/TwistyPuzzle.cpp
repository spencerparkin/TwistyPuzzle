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
		case CLASSIC_2x2x2:
		{
			MakeBox( 10.0, 10.0, 10.0 );

			CutShape* cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
			cutShape->rotationDivisor = 4.0;
			cutShape->unitRotationAxis.Set( 1.0, 0.0, 0.0 );
			cutShapeList.push_back( cutShape );

			cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
			cutShape->rotationDivisor = 4.0;
			cutShape->unitRotationAxis.Set( 0.0, 1.0, 0.0 );
			cutShapeList.push_back( cutShape );

			cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
			cutShape->rotationDivisor = 4.0;
			cutShape->unitRotationAxis.Set( 0.0, 1.0, 0.0 );
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
	Face* face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color.Set( 1.0, 1.0, 1.0 );
	faceList.push_back( face );

	face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color.Set( 1.0, 1.0, 0.0 );
	faceList.push_back( face );

	face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->color.Set( 1.0, 0.0, 0.0 );
	faceList.push_back( face );

	face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->color.Set( 1.0, 0.5, 0.0 );
	faceList.push_back( face );

	face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, height / 2.0, -depth / 2.0 ) );
	face->color.Set( 0.0, 0.0, 1.0 );
	faceList.push_back( face );

	face = new Face();
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( -width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, -depth / 2.0 ) );
	face->polygon.vertexArray->push_back( _3DMath::Vector( width / 2.0, -height / 2.0, depth / 2.0 ) );
	face->color.Set( 0.0, 1.0, 0.0 );
	faceList.push_back( face );
}

void TwistyPuzzle::Render( _3DMath::Renderer& renderer )
{
	// TODO: Turn on back-face culling.

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;

		if( face->tessellationNeeded )
		{
			face->polygon.Tessellate();
			face->tessellationNeeded = false;
		}

		renderer.drawStyle = _3DMath::Renderer::DRAW_STYLE_SOLID;
		renderer.Color( face->color );
		renderer.DrawPolygon( face->polygon, &face->transform );
	}

	// TODO: Draw selectecd cut-shape?
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::Face
//---------------------------------------------------------------------------------

TwistyPuzzle::Face::Face( void )
{
	tessellationNeeded = true;

	transform.Identity();
}

TwistyPuzzle::Face::~Face( void )
{
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::CutShape
//---------------------------------------------------------------------------------

TwistyPuzzle::CutShape::CutShape( void )
{
	rotationDivisor = 1.0;
	rotationAngle = 0.0;

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