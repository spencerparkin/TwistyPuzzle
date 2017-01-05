// CurvyCopter.cpp

#include "CurvyCopter.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( CurvyCopter, TwistyPuzzle );

CurvyCopter::CurvyCopter( void )
{
}

/*virtual*/ CurvyCopter::~CurvyCopter( void )
{
}

/*virtual*/ void CurvyCopter::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	double radius = 5.0;

	// TODO: Do some math to figure out the partial turn for the jumble move.

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

// CurvyCopter.cpp