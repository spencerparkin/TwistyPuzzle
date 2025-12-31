// PentacleCube.cpp

#include "PentacleCube.h"
#include "Application.h"
#include <Surface.h>
#include <Plane.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( PentacleCube, TwistyPuzzle );

PentacleCube::PentacleCube( void )
{
}

/*virtual*/ PentacleCube::~PentacleCube( void )
{
}

/*virtual*/ void PentacleCube::Reset( void )
{
	Clear();

	// +Z

	Face* face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	// -Z

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	// +Y

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	// -Y

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	// +X

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	// -X

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	CutShape* rightCutShape = new CutShape();
	rightCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	rightCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	rightCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	rightCutShape->label = 'R';
	rightCutShape->vectorLength = 6.0;
	cutShapeList.push_back( rightCutShape );

	CutShape* leftCutShape = new CutShape();
	leftCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	leftCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	leftCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	leftCutShape->label = 'L';
	leftCutShape->vectorLength = 6.0;
	cutShapeList.push_back( leftCutShape );

	CutShape* upCutShape = new CutShape();
	upCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	upCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	upCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	upCutShape->label = 'U';
	upCutShape->vectorLength = 6.0;
	cutShapeList.push_back( upCutShape );

	CutShape* downCutShape = new CutShape();
	downCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	downCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	downCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	downCutShape->label = 'D';
	downCutShape->vectorLength = 6.0;
	cutShapeList.push_back( downCutShape );

	CutShape* frontCutShape = new CutShape();
	frontCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	frontCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	frontCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	frontCutShape->label = 'F';
	frontCutShape->vectorLength = 6.0;
	cutShapeList.push_back( frontCutShape );

	CutShape* backCutShape = new CutShape();
	backCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	backCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	backCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	backCutShape->label = 'B';
	backCutShape->vectorLength = 6.0;
	cutShapeList.push_back( backCutShape );

	CutShape* cutShape = nullptr;
		
	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 0.0, 5.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'f';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 0.0, -5.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'b';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'u';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'd';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'r';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->vectorLength = 7.0;
	cutShape->label = 'l';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'u', _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'd', _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'f', _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'b', _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'l', _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	vectorMap.insert( std::pair< char, _3DMath::Vector >( 'r', _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
}

/*virtual*/ void PentacleCube::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, int renderFlags )
{
	TwistyPuzzle::Render( renderer, transform, renderMode, selectedObjectHandle, renderFlags );

	for( VectorMap::iterator iter = vectorMap.begin(); iter != vectorMap.end(); iter++ )
	{
		_3DMath::Vector vector = iter->second;
		vector.Scale( 4.0 );

		_3DMath::Vector position;
		if( iter->first == 'u' )
			position.Set( 0.0, 5.5, 0.0 );
		else if( iter->first == 'd' )
			position.Set( 0.0, -5.5, 0.0 );
		else if( iter->first == 'l' )
			position.Set( -5.5, 0.0, 0.0 );
		else if( iter->first == 'r' )
			position.Set( 5.5, 0.0, 0.0 );
		else if( iter->first == 'f' )
			position.Set( 0.0, 0.0, 5.5 );
		else if( iter->first == 'b' )
			position.Set( 0.0, 0.0, -5.5 );

		_3DMath::Vector color( 0.5, 0.5, 0.5 );

		_3DMath::LinearTransform normalTransform;
		transform.linearTransform.GetNormalTransform( normalTransform );

		transform.Transform( position );
		normalTransform.Transform( vector );

		renderer.DrawVector( vector, position, color, 1.0, 0.5 );
	}
}

void PentacleCube::GetAdjacentSides( char side, std::list< char >& sideList )
{
	if( side == 'U' || side == 'D' )
	{
		sideList.push_back('l');
		sideList.push_back('r');
		sideList.push_back('f');
		sideList.push_back('b');
	}
	else if( side == 'L' || side == 'R' )
	{
		sideList.push_back('u');
		sideList.push_back('d');
		sideList.push_back('f');
		sideList.push_back('b');
	}
	else if( side == 'F' || side == 'B' )
	{
		sideList.push_back('l');
		sideList.push_back('r');
		sideList.push_back('u');
		sideList.push_back('d');
	}
}

/*virtual*/ bool PentacleCube::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	std::string upperLabels = "UDLRFB";

	if( upperLabels.find( cutShape->label ) != -1 )
	{
		std::list< char > labelList;
		GetAdjacentSides( cutShape->label.c_str()[0], labelList );

		for( std::list< char >::iterator iter = labelList.begin(); iter != labelList.end(); iter++ )
		{
			const _3DMath::Vector& vector = vectorMap.find( *iter )->second;
			double angle = vector.AngleBetween( cutShape->axisOfRotation.normal );
			if( angle > 1e-5 )
				return false; // The face is locked; it cannot turn.
		}
	}
	
	_3DMath::Vector& vector = vectorMap.find( ::tolower( cutShape->label.c_str()[0] ) )->second;
	double angle = ( ( rotation->direction == Rotation::DIR_CCW ) ? M_PI / 2.0 : -M_PI / 2.0 ) * float( rotation->turnCount );
	_3DMath::LinearTransform transform;
	transform.SetRotation( cutShape->axisOfRotation.normal, angle );
	transform.Transform( vector );

	return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );
}

/*virtual*/ bool PentacleCube::LoadFromXml( const wxXmlDocument& xmlDocument )
{
	if( !TwistyPuzzle::LoadFromXml( xmlDocument ) )
		return false;

	const wxXmlNode* xmlRootNode = xmlDocument.GetRoot();

	wxXmlNode* xmlVectorMapNode = xmlRootNode->GetChildren();
	while( xmlVectorMapNode )
	{
		if( xmlVectorMapNode->GetName() == "vectorMap" )
			break;

		xmlVectorMapNode = xmlVectorMapNode->GetNext();
	}

	if( !xmlVectorMapNode )
		return false;

	for( VectorMap::iterator iter = vectorMap.begin(); iter != vectorMap.end(); iter++ )
		if( !LoadVector( iter->first, xmlVectorMapNode, iter->second ) )
			return false;

	return true;
}

/*virtual*/ bool PentacleCube::SaveToXml( wxXmlDocument& xmlDocument ) const
{
	if( !TwistyPuzzle::SaveToXml( xmlDocument ) )
		return false;

	wxXmlNode* xmlRootNode = xmlDocument.GetRoot();

	wxXmlNode* xmlVectorMapNode = new wxXmlNode( wxXmlNodeType::wxXML_ELEMENT_NODE, "vectorMap" );
	for( VectorMap::const_iterator iter = vectorMap.cbegin(); iter != vectorMap.cend(); iter++ )
		if( !SaveVector( iter->first, xmlVectorMapNode, iter->second ) )
			return false;

	xmlRootNode->AddChild( xmlVectorMapNode );

	return true;
}

/*virtual*/ void PentacleCube::EnqueueRandomRotations( _3DMath::Random& random, int rotationCount )
{
	// Here, instead of just enqueueing rotations, we're actually just going to do the scramble directly.
	// This is because we have to flush each iteration of this loop.

	while( rotationCount > 0 )
	{
		const char sideArray[6] = { 'U', 'D', 'L', 'R', 'F', 'B' };
		CutShape* cutShape = FindCutShapeWithLabel( sideArray[ random.Integer( 0, 5 ) ] );

		std::list< char > labelList;
		GetAdjacentSides( cutShape->label.c_str()[0], labelList );

		for( std::list< char >::iterator iter = labelList.begin(); iter != labelList.end(); iter++ )
		{
			const _3DMath::Vector& vector = vectorMap.find( *iter )->second;
			CutShape* sphereCutShape = FindCutShapeWithLabel( *iter );

			while( true )
			{
				double angle = vector.AngleBetween( cutShape->axisOfRotation.normal );
				if( angle <= 1e-5 )
					break;

				EnqueueRotation( new Rotation( sphereCutShape->GetHandle(), Rotation::DIR_CCW ) );
				FlushRotationQueue();
			}
		}

		Rotation::Direction direction = random.Integer( 0, 1 ) ? Rotation::DIR_CCW : Rotation::DIR_CW;
		EnqueueRotation( new Rotation( cutShape->GetHandle(), direction ) );
		FlushRotationQueue();

		rotationCount--;
	}
}

// PentacleCube.cpp