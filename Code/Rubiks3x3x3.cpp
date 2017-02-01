// Rubiks3x3x3.cpp

#include "Rubiks3x3x3.h"
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
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->label = 'L';
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->label = 'U';
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->label = 'D';
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->label = 'F';
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->label = 'B';
	cutShapeList.push_back( cutShape );

	DoubleSurfaceCutShape* doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'X';
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'Y';
	cutShapeList.push_back( doubleSurfaceCutShape );

	doubleSurfaceCutShape = new DoubleSurfaceCutShape();
	doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	doubleSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	doubleSurfaceCutShape->vectorLength = 12.0;
	doubleSurfaceCutShape->label = 'Z';
	cutShapeList.push_back( doubleSurfaceCutShape );

	SetupDynamicLabelsUsingCutShapeList();
}

// Rubiks3x3x3.cpp