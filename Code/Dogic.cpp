// Dogic.cpp

#include "Dogic.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Dogic, TwistyPuzzle );

Dogic::Dogic( void )
{
}

/*virtual*/ Dogic::~Dogic( void )
{
}

/*virtual*/ void Dogic::Reset( void )
{
	Clear();

	_3DMath::TriangleMesh triangleMesh;
	double radius = 4.0;
	MakePolyhedron( ICOSAHEDRON, radius, &triangleMesh );

	char label = 'A';

	for( int i = 0; i < ( signed )triangleMesh.vertexArray->size(); i++ )
	{
		_3DMath::Vector normal;
		( *triangleMesh.vertexArray )[i].position.GetNormalized( normal );

		_3DMath::Vector center( 0.0, 0.0, 0.0 );
		int count = 0;

		_3DMath::IndexTriangleList::iterator iter = triangleMesh.triangleList->begin();
		while( iter != triangleMesh.triangleList->end() )
		{
			_3DMath::IndexTriangle triangle = *iter;
			if( triangle.HasVertex(i) )
			{
				for( int j = 0; j < 3; j++ )
				{
					if( triangle.vertex[j] != i )
					{
						center.Add( ( *triangleMesh.vertexArray )[ triangle.vertex[j] ].position );
						count++;
					}
				}
			}

			iter++;
		}

		center.Scale( 1.0 / double( count ) );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 5.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->axisOfRotation.center = center;
		cutShape->label = label++;
		cutShapeList.push_back( cutShape );

		center.Lerp( center, ( *triangleMesh.vertexArray )[i].position, 0.5 );

		cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 5.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->axisOfRotation.center = center;
		cutShape->label = label++;
		cutShapeList.push_back( cutShape );
	}
}

// Dogic.cpp