// MixupCube.cpp

#include "MixupCube.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( MixupCube, TwistyPuzzle );

MixupCube::MixupCube( void )
{
}

/*virtual*/ MixupCube::~MixupCube( void )
{
}

/*virtual*/ void MixupCube::Reset( void )
{
	Clear();

	double radius = 5.0;

	MakeBox( radius * 2.0, radius * 2.0, radius * 2.0 );

	double distance = radius * tan( M_PI / 8.0 );

	char label = 'A';

	for( int i = 0; i < 6; i++ )
	{
		_3DMath::Vector center, normal;

		switch( i / 2 )
		{
			case 0: normal.Set( 1.0, 0.0, 0.0 ); break;
			case 1: normal.Set( 0.0, 1.0, 0.0 ); break;
			case 2: normal.Set( 0.0, 0.0, 1.0 ); break;
		}

		if( i % 2 )
			normal.Negate();

		center = center + normal * distance;

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->label = label++;
		cutShapeList.push_back( cutShape );

		DoubleSurfaceCutShape* doubleSurfaceCutShape = new DoubleSurfaceCutShape();
		doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal * -1.0 ) );
		doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( center * -1.0, normal ) );
		doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
		doubleSurfaceCutShape->axisOfRotation.normal = normal;
		doubleSurfaceCutShape->axisOfRotation.center = center;
		doubleSurfaceCutShape->label = label++;
		doubleSurfaceCutShape->captureSide = _3DMath::Surface::OUTSIDE;
		cutShapeList.push_back( doubleSurfaceCutShape );
	}

	SetupDynamicLabelUsingCutShapeList();
}

// MixupCube.cpp