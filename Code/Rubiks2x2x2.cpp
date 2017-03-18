// Rubiks2x2x2.cpp

#include "Rubiks2x2x2.h"
#include "Application.h"
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

	SetupStandardDynamicFaceTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 4, 5, 6, 7 );
	cutShape->ccwPermutation.DefineCycle( 2, 18, 8, 22 );
	cutShape->ccwPermutation.DefineCycle( 1, 17, 11, 21 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 12, 13, 14, 15 );
	cutShape->ccwPermutation.DefineCycle( 0, 20, 10, 16 );
	cutShape->ccwPermutation.DefineCycle( 3, 23, 9, 19 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 20, 21, 22, 23 );
	cutShape->ccwPermutation.DefineCycle( 2, 6, 10, 14 );
	cutShape->ccwPermutation.DefineCycle( 3, 7, 11, 15 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->ccwPermutation.DefineCycle( 16, 17, 18, 19 );
	cutShape->ccwPermutation.DefineCycle( 0, 12, 8, 4 );
	cutShape->ccwPermutation.DefineCycle( 1, 13, 9, 5 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->ccwPermutation.DefineCycle( 0, 1, 2, 3 );
	cutShape->ccwPermutation.DefineCycle( 13, 18, 7, 20 );
	cutShape->ccwPermutation.DefineCycle( 14, 19, 4, 21 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->ccwPermutation.DefineCycle( 8, 9, 10, 11 );
	cutShape->ccwPermutation.DefineCycle( 5, 16, 15, 22 );
	cutShape->ccwPermutation.DefineCycle( 6, 17, 12, 23 );
	cutShapeList.push_back( cutShape );
}

/*virtual*/ wxString Rubiks2x2x2::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Rubiks2x2x2.txt" );
}

// Rubiks2x2x2.cpp