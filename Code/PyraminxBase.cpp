// PyraminxBase.cpp

#include "PyraminxBase.h"
#include <Surface.h>
#include <Plane.h>
#include <LineSegment.h>

wxIMPLEMENT_ABSTRACT_CLASS( PyraminxBase, TwistyPuzzle );

PyraminxBase::PyraminxBase( void )
{
}

/*virtual*/ PyraminxBase::~PyraminxBase( void )
{
}

/*virtual*/ void PyraminxBase::Reset( void )
{
	Clear();

	double radius = 8.0;
	MakePolyhedron( TETRAHEDRON, radius );

	_3DMath::Vector vertex[4];

	vertex[0].Set( 1.0, 0.0, -1.0 / sqrt( 2.0 ) );
	vertex[1].Set( -1.0, 0.0, -1.0 / sqrt( 2.0 ) );
	vertex[2].Set( 0.0, 1.0, 1.0 / sqrt( 2.0 ) );
	vertex[3].Set( 0.0, -1.0, 1.0 / sqrt( 2.0 ) );

	for( int i = 0; i < 4; i++ )
		vertex[i].Scale( radius );

	for( int i = 0; i < 4; i++ )
	{
		_3DMath::Vector center( 0.0, 0.0, 0.0 );
		for( int j = 0; j < 4; j++ )
			if( j != i )
				center.Add( vertex[j] );
		center.Scale( 1.0 / 3.0 );

		_3DMath::LineSegment lineSegment( center, vertex[i] );

		_3DMath::Vector normal;
		vertex[i].GetNormalized( normal );

		for( int j = 1; j < Layers(); j++ )
		{
			double lambda = double(j) / double( Layers() );
			lineSegment.Lerp( lambda, center );

			CutShape* cutShape = new CutShape();
			cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
			cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
			cutShape->axisOfRotation.normal = normal;
			cutShape->axisOfRotation.center = center;
			cutShapeList.push_back( cutShape );
		}
	}
}

// PyraminxBase.cpp