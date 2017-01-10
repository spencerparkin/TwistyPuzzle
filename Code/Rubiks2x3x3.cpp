// Rubiks2x3x3.cpp

#include "Rubiks2x3x3.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Rubiks2x3x3, TwistyPuzzle );

Rubiks2x3x3::Rubiks2x3x3( void )
{
}

/*virtual*/ Rubiks2x3x3::~Rubiks2x3x3( void )
{
}

/*virtual*/ void Rubiks2x3x3::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0 * ( 2.0 / 3.0 ), 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShapeList.push_back( cutShape );
}

// Rubiks2x3x3.cpp