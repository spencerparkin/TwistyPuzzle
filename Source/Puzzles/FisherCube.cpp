// FisherCube.cpp

#include "FisherCube.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( FisherCube, TwistyPuzzle );

FisherCube::FisherCube( void )
{
}

/*virtual*/ FisherCube::~FisherCube( void )
{
}

/*virtual*/ void FisherCube::Reset( void )
{
	Clear();

	SetupStandardDynamicFaceTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = nullptr;

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShapeList.push_back( cutShape );

	_3DMath::AffineTransform transform;
	transform.SetRotation( _3DMath::Line( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ), M_PI / 4.0 );

	_3DMath::Plane plane;

	plane.SetCenterAndNormal( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) );
	plane.Transform( transform );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( plane );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = plane.normal;
	cutShapeList.push_back( cutShape );

	plane.SetCenterAndNormal( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) );
	plane.Transform( transform );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( plane );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = plane.normal;
	cutShapeList.push_back( cutShape );

	plane.SetCenterAndNormal( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) );
	plane.Transform( transform );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( plane );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = plane.normal;
	cutShapeList.push_back( cutShape );

	plane.SetCenterAndNormal( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) );
	plane.Transform( transform );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( plane );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = plane.normal;
	cutShapeList.push_back( cutShape );
}

// FisherCube.cpp