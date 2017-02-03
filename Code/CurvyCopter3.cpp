// CurvyCopter3.cpp

#include "CurvyCopter3.h"
#include <Surface.h>
#include <Sphere.h>

// TODO: Sigh...So this puzzle was had been working well for a long time, but recent changes,
//       I suppose, have added a new bug where I'm hitting the "intersectionCount >= 2" case
//       in the polygon splitter algorithm.  This is 100% reproducable right now with a scramble.
//       And the bug manifests itself in a very unsightly way.  This is a must fix.

wxIMPLEMENT_DYNAMIC_CLASS( CurvyCopter3, CurvyCopterBase );

CurvyCopter3::CurvyCopter3( void )
{
}

/*virtual*/ CurvyCopter3::~CurvyCopter3( void )
{
}

/*virtual*/ _3DMath::Surface* CurvyCopter3::MakeCutSphereSurfaceForEdge( const _3DMath::Vector& edgeCenter )
{
	double radius = 5.0 * sqrt( 4.0 / 9.0 + 1.0 );
	return new _3DMath::SphereSurface( _3DMath::Sphere( edgeCenter, radius ) );
}

/*virtual*/ double CurvyCopter3::CalcJumbleTurnAmount( void )
{
	// The calculation we're making here is exactly the same as that made for the CurvyCopter 1.
	double ppr_radius = 2.8867513459481282;
	_3DMath::Vector ppr_center( 1.6666666666666667, 1.6666666666666667, -1.6666666666666667 );
	_3DMath::Vector ppr_normal( 0.57735026918962573, 0.57735026918962573, -0.57735026918962573 );

	_3DMath::Vector vertex = ppr_center + ppr_normal * ppr_radius;
	_3DMath::Vector origin( 0.0, 0.0, 0.0 );
	_3DMath::Vector pivot( 5.0, 0.0, 0.0 );

	double angle = ( vertex - pivot ).AngleBetween( origin - pivot );
	double amount = angle / M_PI;
	return amount;
}

// CurvyCopter3.cpp