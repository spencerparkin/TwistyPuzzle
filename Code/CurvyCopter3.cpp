// CurvyCopter3.cpp

#include "CurvyCopter3.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( CurvyCopter3, TwistyPuzzle );

CurvyCopter3::CurvyCopter3( void )
{
}

/*virtual*/ CurvyCopter3::~CurvyCopter3( void )
{
}

/*virtual*/ void CurvyCopter3::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	double radius = 5.0 * sqrt( 4.0 / 9.0 + 1.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, 0.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, 0.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, 0.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, 0.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, 0.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, 0.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, 0.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, 0.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );
}

// CurvyCopter3.cpp