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

	// TODO: Start by copying the CurvyCopter3 Reset routine.
}

// CurvyCopter.cpp