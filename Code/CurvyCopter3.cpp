// CurvyCopter3.cpp

#include "CurvyCopter3.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( CurvyCopter3, CurvyCopterBase );

CurvyCopter3::CurvyCopter3( void )
{
}

/*virtual*/ CurvyCopter3::~CurvyCopter3( void )
{
}

/*virtual*/ double CurvyCopter3::CutSphereRadius( void )
{
	return 5.0 * sqrt( 4.0 / 9.0 + 1.0 );
}

/*virtual*/ double CurvyCopter3::CalcJumbleTurnAmount( void )
{
	// TODO: Figure this out.
	return 0.0;
}

// CurvyCopter3.cpp