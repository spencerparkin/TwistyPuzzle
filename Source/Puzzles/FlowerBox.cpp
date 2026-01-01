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

	double length = 10.0;

	MakeBox( length, length, length );

	double lengthToSphereCenter = 25.0;

	_3DMath::Vector vector( 1.0, 1.0, 1.0 );
	vector.Scale( lengthToSphereCenter / vector.Length() );
	double sphereRadius = _3DMath::Vector( -length / 2.0, length / 2.0, length / 2.0 ).Distance( vector );

	for( int i = 0; i < 8; i++ )
	{
		_3DMath::Vector normal;

		normal.x = ( i & 1 ) ? -1.0 : 1.0;
		normal.y = ( i & 2 ) ? -1.0 : 1.0;
		normal.z = ( i & 4 ) ? -1.0 : 1.0;

		normal.Normalize();

		_3DMath::Vector sphereCenter = normal * lengthToSphereCenter;

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( sphereCenter, sphereRadius ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->captureSide = _3DMath::Surface::INSIDE;
		cutShapeList.push_back( cutShape );
	}
}

// FlowerBox.cpp