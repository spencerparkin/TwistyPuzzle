// Bubbloid3x3x3.cpp

#include "Bubbloid3x3x3.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( Bubbloid3x3x3, TwistyPuzzle );

Bubbloid3x3x3::Bubbloid3x3x3( void )
{
}

/*virtual*/ Bubbloid3x3x3::~Bubbloid3x3x3( void )
{
}

/*virtual*/ void Bubbloid3x3x3::Reset( void )
{
	Clear();

	SetupStandardDynamicCornerTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	double radius = 10.0 / sqrt( 2.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );
}

// Bubbloid3x3x3.cpp