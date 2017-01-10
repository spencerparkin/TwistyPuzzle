// IcosahedronSkewb.cpp

#include "IcosahedronSkewb.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( IcosahedronSkewb, TwistyPuzzle );

IcosahedronSkewb::IcosahedronSkewb( void )
{
}

/*virtual*/ IcosahedronSkewb::~IcosahedronSkewb( void )
{
}

/*virtual*/ void IcosahedronSkewb::Reset( void )
{
	Clear();

	_3DMath::TriangleMesh triangleMesh;
	double radius = 4.0;
	MakePolyhedron( ICOSAHEDRON, radius, &triangleMesh );

	for( int i = 0; i < ( signed )triangleMesh.vertexArray->size(); i++ )
	{
		_3DMath::Vector normal;
		( *triangleMesh.vertexArray )[i].position.GetNormalized( normal );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 5.0;
		cutShape->axisOfRotation.normal = normal;
		cutShapeList.push_back( cutShape );
	}
}

// IcosahedronSkewb.cpp