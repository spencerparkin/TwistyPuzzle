// Skewb2.cpp

#include "Skewb2.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Skewb2, TwistyPuzzle );

Skewb2::Skewb2( void )
{
}

/*virtual*/ Skewb2::~Skewb2( void )
{
}

/*virtual*/ void Skewb2::Reset( void )
{
	Clear();

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

	char label = 'A';

	for( int i = 0; i < 8; i++ )
	{
		_3DMath::Vector center;
		normal[i].GetScaled( center, 0.5 );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal[i] ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal[i];
		cutShape->label = label++;
		cutShapeList.push_back( cutShape );

		DoubleSurfaceCutShape* doubleCutShape = new DoubleSurfaceCutShape();
		doubleCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal[i] ) );
		doubleCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( center * -1.0, normal[i] * -1.0 ) );
		doubleCutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		doubleCutShape->axisOfRotation.normal = normal[i];
		doubleCutShape->label = label++;
		doubleCutShape->vectorLength = 12.0;
		doubleCutShape->captureSide = _3DMath::Surface::INSIDE;
		cutShapeList.push_back( doubleCutShape );
	}
}

// Skewb2.cpp