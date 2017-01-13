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

	FaceList::iterator iter = faceList.begin();
	Face* face = *iter;
	double edgeLength = ( *face->polygon->vertexArray )[0].Distance( ( *face->polygon->vertexArray )[1] );

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