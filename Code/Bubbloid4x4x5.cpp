// Bubbloid4x4x5.cpp

#include "Bubbloid4x4x5.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( Bubbloid4x4x5, TwistyPuzzle );

Bubbloid4x4x5::Bubbloid4x4x5( void )
{
}

/*virtual*/ Bubbloid4x4x5::~Bubbloid4x4x5( void )
{
}

/*virtual*/ void Bubbloid4x4x5::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, 5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, 5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, -5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, -5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, 5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, 5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, -5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, -5.0 ), 7.5 ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShapeList.push_back( cutShape );
}

// Bubbloid4x4x5.cpp