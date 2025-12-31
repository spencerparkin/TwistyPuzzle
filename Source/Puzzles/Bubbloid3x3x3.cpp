// Bubbloid3x3x3.cpp

#include "Bubbloid3x3x3.h"
#include "Application.h"
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
	cutShape->ccwPermutation.Define( 0, 4 );
	cutShape->ccwPermutation.Define( 4, 7 );
	cutShape->ccwPermutation.Define( 7, 0 );
	cutShape->ccwPermutation.Define( 12, 13 );
	cutShape->ccwPermutation.Define( 13, 14 );
	cutShape->ccwPermutation.Define( 14, 12 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 1, 5 );
	cutShape->ccwPermutation.Define( 5, 4 );
	cutShape->ccwPermutation.Define( 4, 1 );
	cutShape->ccwPermutation.Define( 15, 16 );
	cutShape->ccwPermutation.Define( 16, 17 );
	cutShape->ccwPermutation.Define( 17, 15 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 3, 7 );
	cutShape->ccwPermutation.Define( 7, 6 );
	cutShape->ccwPermutation.Define( 6, 3 );
	cutShape->ccwPermutation.Define( 21, 22 );
	cutShape->ccwPermutation.Define( 22, 23 );
	cutShape->ccwPermutation.Define( 23, 21 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 2, 6 );
	cutShape->ccwPermutation.Define( 6, 5 );
	cutShape->ccwPermutation.Define( 5, 2 );
	cutShape->ccwPermutation.Define( 18, 19 );
	cutShape->ccwPermutation.Define( 19, 20 );
	cutShape->ccwPermutation.Define( 20, 18 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 0, 11 );
	cutShape->ccwPermutation.Define( 11, 8 );
	cutShape->ccwPermutation.Define( 8, 0 );
	cutShape->ccwPermutation.Define( 24, 25 );
	cutShape->ccwPermutation.Define( 25, 26 );
	cutShape->ccwPermutation.Define( 26, 24 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, 5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, 1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 1, 8 );
	cutShape->ccwPermutation.Define( 8, 9 );
	cutShape->ccwPermutation.Define( 9, 1 );
	cutShape->ccwPermutation.Define( 27, 28 );
	cutShape->ccwPermutation.Define( 28, 29 );
	cutShape->ccwPermutation.Define( 29, 27 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( -1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 3, 10 );
	cutShape->ccwPermutation.Define( 10, 11 );
	cutShape->ccwPermutation.Define( 11, 3 );
	cutShape->ccwPermutation.Define( 33, 34 );
	cutShape->ccwPermutation.Define( 34, 35 );
	cutShape->ccwPermutation.Define( 35, 33 );
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, -5.0 ), radius ) );
	cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
	cutShape->axisOfRotation.normal.Set( 1.0, -1.0, -1.0 );
	cutShape->axisOfRotation.normal.Normalize();
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShape->ccwPermutation.Define( 2, 9 );
	cutShape->ccwPermutation.Define( 9, 10 );
	cutShape->ccwPermutation.Define( 10, 2 );
	cutShape->ccwPermutation.Define( 30, 31 );
	cutShape->ccwPermutation.Define( 31, 32 );
	cutShape->ccwPermutation.Define( 32, 30 );
	cutShapeList.push_back( cutShape );
}

/*virtual*/ wxString Bubbloid3x3x3::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Bubbloid3x3x3.txt" );
}

// Bubbloid3x3x3.cpp