// Gem8.cpp

#include "Gem8.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Gem8, TwistyPuzzle );

Gem8::Gem8( void )
{
}

/*virtual*/ Gem8::~Gem8( void )
{
}

/*virtual*/ void Gem8::Reset( void )
{
	Clear();

	SetupStandardDynamicCornerTurningBoxLabels();

	double radius = 1.5;
	_3DMath::TriangleMesh triangleMesh;
	MakePolyhedron( TRUNCATED_TETRAHEDRON, radius, &triangleMesh );

	double edgeLength = sqrt( 8.0 ) * radius;

	for( FaceList::iterator iter = faceList.begin(); iter != faceList.end(); iter++ )
	{
		Face* face = *iter;

		_3DMath::LineSegmentList lineSegmentList;
		CollectAdjacentEdges( face, lineSegmentList );

		_3DMath::Vector center( 0.0, 0.0, 0.0 );

		for( _3DMath::LineSegmentList::iterator segIter = lineSegmentList.begin(); segIter != lineSegmentList.end(); segIter++ )
		{
			_3DMath::LineSegment& lineSegment = *segIter;
			_3DMath::Vector midPoint;
			lineSegment.Lerp( 0.5, midPoint );
			center.Add( midPoint );
		}

		center.Scale( 1.0 / double( lineSegmentList.size() ) );

		_3DMath::Vector normal;
		center.GetNormalized( normal );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->axisOfRotation.center.Set( 0.0, 0.0, 0.0 );
		cutShape->vectorLength = center.Length() + 4.0;
		cutShapeList.push_back( cutShape );
	}
}

// Gem8.cpp