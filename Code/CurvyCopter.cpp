// CurvyCopter.cpp

#include "CurvyCopter.h"
#include <Surface.h>
#include <Sphere.h>
#include <Line.h>

wxIMPLEMENT_DYNAMIC_CLASS( CurvyCopter, CurvyCopterBase );

CurvyCopter::CurvyCopter( void )
{
}

/*virtual*/ CurvyCopter::~CurvyCopter( void )
{
}

/*virtual*/ _3DMath::Surface* CurvyCopter::MakeCutSphereSurfaceForEdge( const _3DMath::Vector& edgeCenter )
{
	_3DMath::Line line;
	line.center.Set( 0.0, 0.0, 0.0 );
	line.normal.Set( 1.0, 1.0, 0.0 );
	line.normal.Normalize();

	_3DMath::Sphere sphere;
	sphere.center.Set( 0.0, 5.0, 0.0 );
	sphere.radius = 7.0;

	_3DMath::VectorArray intersectionPoints;
	sphere.RayCast( line, intersectionPoints );

	int i = 0;
	if( intersectionPoints[0].x < intersectionPoints[1].x )
		i = 1;

	double length = intersectionPoints[i].Length();

	sphere.center = edgeCenter;
	sphere.center.Scale( length / sphere.center.Length() );

	return new _3DMath::SphereSurface( sphere );
}

/*virtual*/ double CurvyCopter::CalcJumbleTurnAmount( void )
{
	// These numbers were obtained by using GAVisTool.
	double ppr_radius = 2.8867513459481282;
	_3DMath::Vector ppr_center( 1.6666666666666667, 1.6666666666666667, -1.6666666666666667 );
	_3DMath::Vector ppr_normal( 0.57735026918962573, 0.57735026918962573, -0.57735026918962573 );

	_3DMath::Vector vertex = ppr_center + ppr_normal * ppr_radius;
	_3DMath::Vector origin( 0.0, 0.0, 0.0 );
	_3DMath::Vector pivot( 5.0, 0.0, 0.0 );

	// This result is correct; although, admittedly, I couldn't push through a
	// general formula in terms of the edge-length of the cube.
	double angle = ( vertex - pivot ).AngleBetween( origin - pivot );
	double amount = angle / M_PI;
	return amount;
}

// CurvyCopter.cpp