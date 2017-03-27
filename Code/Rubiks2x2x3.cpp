// Rubiks2x2x3.cpp

#include "Application.h"
#include "Rubiks2x2x3.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Rubiks2x2x3, TwistyPuzzle );

Rubiks2x2x3::Rubiks2x2x3( void )
{
}

/*virtual*/ Rubiks2x2x3::~Rubiks2x2x3( void )
{
}

/*virtual*/ void Rubiks2x2x3::Reset( void )
{
	Clear();

	SetupStandardDynamicFaceTurningBoxLabels();

	MakeBox( 10.0 * ( 2.0 / 3.0 ), 10.0, 10.0 * ( 2.0 / 3.0 ) );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 1, 31 );
	cutShape->ccwPermutation.DefineCycle( 2, 28 );
	cutShape->ccwPermutation.DefineCycle( 4, 7 );
	cutShape->ccwPermutation.DefineCycle( 6, 9 );
	cutShape->ccwPermutation.DefineCycle( 5, 8 );
	cutShape->ccwPermutation.DefineCycle( 11, 23 );
	cutShape->ccwPermutation.DefineCycle( 12, 24 );
	cutShape->ccwPermutation.DefineCycle( 13, 15 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 30 );
	cutShape->ccwPermutation.DefineCycle( 3, 29 );
	cutShape->ccwPermutation.DefineCycle( 10, 22 );
	cutShape->ccwPermutation.DefineCycle( 15, 27 );
	cutShape->ccwPermutation.DefineCycle( 14, 26 );
	cutShape->ccwPermutation.DefineCycle( 21, 18 );
	cutShape->ccwPermutation.DefineCycle( 20, 27 );
	cutShape->ccwPermutation.DefineCycle( 19, 16 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 28 );
	cutShape->ccwPermutation.DefineCycle( 1, 29 );
	cutShape->ccwPermutation.DefineCycle( 26, 23 );
	cutShape->ccwPermutation.DefineCycle( 27, 24 );
	cutShape->ccwPermutation.DefineCycle( 22, 25 );
	cutShape->ccwPermutation.DefineCycle( 6, 18 );
	cutShape->ccwPermutation.DefineCycle( 5, 17 );
	cutShape->ccwPermutation.DefineCycle( 4, 16 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->ccwPermutation.DefineCycle( 2, 30 );
	cutShape->ccwPermutation.DefineCycle( 3, 31 );
	cutShape->ccwPermutation.DefineCycle( 9, 21 );
	cutShape->ccwPermutation.DefineCycle( 8, 20 );
	cutShape->ccwPermutation.DefineCycle( 7, 19 );
	cutShape->ccwPermutation.DefineCycle( 11, 14 );
	cutShape->ccwPermutation.DefineCycle( 15, 12 );
	cutShape->ccwPermutation.DefineCycle( 10, 13 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 1, 2, 3 );
	cutShape->ccwPermutation.DefineCycle( 4, 11, 19, 26 );
	cutShape->ccwPermutation.DefineCycle( 9, 10, 18, 25 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 28, 29, 30, 31 );
	cutShape->ccwPermutation.DefineCycle( 6, 22, 21, 13 );
	cutShape->ccwPermutation.DefineCycle( 7, 23, 16, 14 );
	cutShapeList.push_back( cutShape );
}

/*virtual*/ wxString Rubiks2x2x3::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Rubiks2x2x3.txt" );
}

// Rubiks2x2x3.cpp