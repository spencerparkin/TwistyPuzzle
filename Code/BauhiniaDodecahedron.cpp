// BauhiniaDodecahedron.cpp

#include "BauhiniaDodecahedron.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( BauhiniaDodecahedron, TwistyPuzzle );

BauhiniaDodecahedron::BauhiniaDodecahedron( void )
{
}

/*virtual*/ BauhiniaDodecahedron::~BauhiniaDodecahedron( void )
{
}

/*virtual*/ void BauhiniaDodecahedron::Reset( void )
{
	Clear();

	double radius = 4.0;
	_3DMath::TriangleMesh triangleMesh;
	MakePolyhedron( DODECAHEDRON, radius, &triangleMesh );

	_3DMath::IndexTriangleList::iterator iter = triangleMesh.triangleList->begin();
	_3DMath::IndexTriangle& indexTriangle = *iter;

	_3DMath::Triangle triangle;
	indexTriangle.GetTriangle( triangle, triangleMesh.vertexArray );

	double edgeLength = ( triangle.vertex[1] - triangle.vertex[0] ).Length();

	for( int i = 0; i < ( signed )triangleMesh.vertexArray->size(); i++ )
	{
		_3DMath::Vector center = ( *triangleMesh.vertexArray )[i].position;

		_3DMath::Vector normal;
		center.GetNormalized( normal );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( center, edgeLength ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->captureSide = _3DMath::Surface::INSIDE;
		cutShapeList.push_back( cutShape );
	}
}

// BauhiniaDodecahedron.cpp