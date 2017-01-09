// FaceTurningOctahedron.cpp

#include "FaceTurningOctahedron.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( FaceTurningOctahedron, TwistyPuzzle );

FaceTurningOctahedron::FaceTurningOctahedron( void )
{
}

/*virtual*/ FaceTurningOctahedron::~FaceTurningOctahedron( void )
{
}

/*virtual*/ void FaceTurningOctahedron::Reset( void )
{
	Clear();

	double radius = 4.0;

	MakePolyhedron( OCTAHEDRON, radius );

	_3DMath::Vector normal[8];

	for( int i = 0; i < 8; i++ )
	{
		normal[i].Set( 1.0, 1.0, 1.0 );
		if( i & 1 )
			normal[i].x *= -1.0;
		if( i & 2 )
			normal[i].y *= -1.0;
		if( i & 4 )
			normal[i].z *= -1.0;
		normal[i].Normalize();
	}

	for( int i = 0; i < 8; i++ )
	{
		_3DMath::Triangle triangle;
		triangle.vertex[0].Set( radius, 0.0, 0.0 );
		triangle.vertex[1].Set( 0.0, radius, 0.0 );
		triangle.vertex[2].Set( 0.0, 0.0, radius );

		if( normal[i].x < 0.0 )
			triangle.vertex[0].x *= -1.0;
		if( normal[i].y < 0.0 )
			triangle.vertex[1].y *= -1.0;
		if( normal[i].z < 0.0 )
			triangle.vertex[2].z *= -1.0;

		_3DMath::Vector center;
		triangle.GetCenter( center );
		center.Scale( 1.0 / 6.0 );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal[i] ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal[i];
		cutShapeList.push_back( cutShape );
	}
}

// FaceTurningOctahedron.cpp