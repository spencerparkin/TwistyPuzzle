// Rubiks2x3x3.cpp

#include "Rubiks2x3x3.h"
#include "Application.h"
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

	SetupStandardDynamicFaceTurningBoxLabels();

	MakeBox( 10.0, 10.0 * ( 2.0 / 3.0 ), 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 2, 36 );
	cutShape->ccwPermutation.DefineCycle( 3, 35 );
	cutShape->ccwPermutation.DefineCycle( 4, 34 );
	cutShape->ccwPermutation.DefineCycle( 10, 26 );
	cutShape->ccwPermutation.DefineCycle( 14, 22 );
	cutShape->ccwPermutation.DefineCycle( 11, 25 );
	cutShape->ccwPermutation.DefineCycle( 12, 24 );
	cutShape->ccwPermutation.DefineCycle( 13, 23 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 6, 32 );
	cutShape->ccwPermutation.DefineCycle( 7, 39 );
	cutShape->ccwPermutation.DefineCycle( 0, 38 );
	cutShape->ccwPermutation.DefineCycle( 8, 28 );
	cutShape->ccwPermutation.DefineCycle( 16, 20 );
	cutShape->ccwPermutation.DefineCycle( 17, 31 );
	cutShape->ccwPermutation.DefineCycle( 18, 30 );
	cutShape->ccwPermutation.DefineCycle( 19, 29 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 34 );
	cutShape->ccwPermutation.DefineCycle( 1, 33 );
	cutShape->ccwPermutation.DefineCycle( 2, 32 );
	cutShape->ccwPermutation.DefineCycle( 11, 31 );
	cutShape->ccwPermutation.DefineCycle( 19, 23 );
	cutShape->ccwPermutation.DefineCycle( 8, 22 );
	cutShape->ccwPermutation.DefineCycle( 9, 21 );
	cutShape->ccwPermutation.DefineCycle( 10, 20 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->ccwPermutation.DefineCycle( 4, 38 );
	cutShape->ccwPermutation.DefineCycle( 5, 37 );
	cutShape->ccwPermutation.DefineCycle( 6, 36 );
	cutShape->ccwPermutation.DefineCycle( 13, 29 );
	cutShape->ccwPermutation.DefineCycle( 17, 25 );
	cutShape->ccwPermutation.DefineCycle( 14, 28 );
	cutShape->ccwPermutation.DefineCycle( 15, 27 );
	cutShape->ccwPermutation.DefineCycle( 16, 26 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 2, 4, 6 );
	cutShape->ccwPermutation.DefineCycle( 1, 3, 5, 7 );
	cutShape->ccwPermutation.DefineCycle( 8, 11, 14, 17 );
	cutShape->ccwPermutation.DefineCycle( 9, 12, 15, 18 );
	cutShape->ccwPermutation.DefineCycle( 10, 13, 16, 19 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 32, 38, 36, 34 );
	cutShape->ccwPermutation.DefineCycle( 33, 39, 37, 35 );
	cutShape->ccwPermutation.DefineCycle( 20, 29, 26, 23 );
	cutShape->ccwPermutation.DefineCycle( 21, 30, 27, 24 );
	cutShape->ccwPermutation.DefineCycle( 22, 31, 28, 25 );
	cutShapeList.push_back( cutShape );
}


/*virtual*/ wxString Rubiks2x3x3::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Rubiks2x3x3.txt" );
}

// Rubiks2x3x3.cpp