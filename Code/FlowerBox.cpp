// FlowerBox.cpp

#include "FlowerBox.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( FlowerBox, TwistyPuzzle );

FlowerBox::FlowerBox( void )
{
}

/*virtual*/ FlowerBox::~FlowerBox( void )
{
}

/*virtual*/ void FlowerBox::Reset( void )
{
	Clear();

	SetupStandardDynamicCornerTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	double radius = 10.0;

	// TODO: The cut is too deep.  Move the center of the sphere out, then increase the radius.

	CutShape* cutShape = new CutShape();
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
}

// FlowerBox.cpp