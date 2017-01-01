// Rubiks2x2x2.cpp

#include "Rubiks2x2x2.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Rubiks2x2x2, TwistyPuzzle );

Rubiks2x2x2::Rubiks2x2x2( void )
{
}

/*virtual*/ Rubiks2x2x2::~Rubiks2x2x2( void )
{
}

/*virtual*/ void Rubiks2x2x2::Reset( void )
{
	Clear();

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
}

// Rubiks2x2x2.cpp