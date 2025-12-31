// Skewb.cpp

#include "Skewb.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Skewb, TwistyPuzzle );

Skewb::Skewb( void )
{
}

/*virtual*/ Skewb::~Skewb( void )
{
}

/*virtual*/ void Skewb::Reset( void )
{
	Clear();

	SetupStandardDynamicCornerTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

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
		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal[i] ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal[i];
		cutShapeList.push_back( cutShape );
	}
}

// Skewb.cpp