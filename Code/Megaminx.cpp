// Megaminx.cpp

#include "Megaminx.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Megaminx, TwistyPuzzle );

Megaminx::Megaminx( void )
{
}

/*virtual*/ Megaminx::~Megaminx( void )
{
}

/*virtual*/ void Megaminx::Reset( void )
{
	Clear();

	MakeDodecahedron( 5.0 );

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;

		_3DMath::Vector center;
		face->polygon->GetCenter( center );

		_3DMath::Vector normal;
		center.GetNormalized( normal );

		center.Scale( 0.8 );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->axisOfRotation.normal = normal;
		cutShape->captureSide = _3DMath::Surface::OUTSIDE;
		cutShapeList.push_back( cutShape );
	}
}

// Megaminx.cpp