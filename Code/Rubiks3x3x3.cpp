// Rubiks3x3x3.cpp

#include "Rubiks3x3x3.h"
#include "Application.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Rubiks3x3x3, TwistyPuzzle );

Rubiks3x3x3::Rubiks3x3x3( void )
{
}

/*virtual*/ Rubiks3x3x3::~Rubiks3x3x3( void )
{
}

/*virtual*/ void Rubiks3x3x3::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->label = 'R';
	cutShape->ccwPermutation.DefineCycle( 24, 29, 31, 26 );
	cutShape->ccwPermutation.DefineCycle( 25, 27, 30, 28 );
	cutShape->ccwPermutation.DefineCycle( 2, 18, 42, 37 );
	cutShape->ccwPermutation.DefineCycle( 4, 20, 44, 35 );
	cutShape->ccwPermutation.DefineCycle( 7, 23, 47, 32 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->label = 'L';
	cutShape->ccwPermutation.DefineCycle( 8, 13, 15, 10 );
	cutShape->ccwPermutation.DefineCycle( 9, 11, 14, 12 );
	cutShape->ccwPermutation.DefineCycle( 0, 39, 40, 16 );
	cutShape->ccwPermutation.DefineCycle( 3, 36, 43, 19 );
	cutShape->ccwPermutation.DefineCycle( 5, 34, 45, 21 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->label = 'U';
	cutShape->ccwPermutation.DefineCycle( 0, 5, 7, 2 );
	cutShape->ccwPermutation.DefineCycle( 1, 3, 6, 4 );
	cutShape->ccwPermutation.DefineCycle( 8, 16, 24, 32 );
	cutShape->ccwPermutation.DefineCycle( 9, 17, 25, 33 );
	cutShape->ccwPermutation.DefineCycle( 10, 18, 26, 34 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->label = 'D';
	cutShape->ccwPermutation.DefineCycle( 40, 45, 47, 42 );
	cutShape->ccwPermutation.DefineCycle( 41, 43, 46, 44 );
	cutShape->ccwPermutation.DefineCycle( 13, 37, 29, 21 );
	cutShape->ccwPermutation.DefineCycle( 14, 38, 30, 22 );
	cutShape->ccwPermutation.DefineCycle( 15, 39, 31, 23 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->label = 'F';
	cutShape->ccwPermutation.DefineCycle( 16, 21, 23, 18 );
	cutShape->ccwPermutation.DefineCycle( 17, 19, 22, 20 );
	cutShape->ccwPermutation.DefineCycle( 5, 15, 42, 24 );
	cutShape->ccwPermutation.DefineCycle( 6, 12, 41, 27 );
	cutShape->ccwPermutation.DefineCycle( 7, 10, 40, 29 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->label = 'B';
	cutShape->ccwPermutation.DefineCycle( 32, 37, 39, 24 );
	cutShape->ccwPermutation.DefineCycle( 33, 35, 38, 36 );
	cutShape->ccwPermutation.DefineCycle( 2, 31, 45, 8 );
	cutShape->ccwPermutation.DefineCycle( 1, 28, 46, 11 );
	cutShape->ccwPermutation.DefineCycle( 0, 26, 47, 13 );
	cutShapeList.push_back( cutShape );

	DoubleSurfaceCutShape* doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'X';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'Y';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'Z';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'x';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'y';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'z';
	doubleSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	// TODO: Add extraneous generator here.
	cutShapeList.push_back( doubleSurfaceCutShape );

	SetupDynamicLabelsUsingCutShapeList();
}

/*virtual*/ wxString Rubiks3x3x3::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Rubiks3x3x3.txt" );
}

// Rubiks3x3x3.cpp