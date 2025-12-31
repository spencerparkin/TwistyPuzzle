// CornerTurningOctahedron.cpp

#include "CornerTurningOctahedron.h"
#include <Surface.h>
#include <Plane.h>
#include <LineSegment.h>

wxIMPLEMENT_DYNAMIC_CLASS( CornerTurningOctahedron, TwistyPuzzle );

CornerTurningOctahedron::CornerTurningOctahedron( void )
{
}

/*virtual*/ CornerTurningOctahedron::~CornerTurningOctahedron( void )
{
}

/*virtual*/ void CornerTurningOctahedron::Reset( void )
{
	Clear();

	double radius = 8.0;

	MakePolyhedron( OCTAHEDRON, radius );

	char label = 'A';

	MakeCutPlanes( _3DMath::LineSegment( _3DMath::Vector( -radius, 0.0, 0.0 ), _3DMath::Vector( radius, 0.0, 0.0 ) ), label );
	MakeCutPlanes( _3DMath::LineSegment( _3DMath::Vector( 0.0, -radius, 0.0 ), _3DMath::Vector( 0.0, radius, 0.0 ) ), label );
	MakeCutPlanes( _3DMath::LineSegment( _3DMath::Vector( 0.0, 0.0, -radius ), _3DMath::Vector( 0.0, 0.0, radius ) ), label );
}

void CornerTurningOctahedron::MakeCutPlanes( const _3DMath::LineSegment& lineSegment, char& label )
{
	_3DMath::Vector normal;
	normal.Subtract( lineSegment.vertex[1], lineSegment.vertex[0] );
	normal.Normalize();

	_3DMath::Vector center;
	lineSegment.Lerp( 2.0 / 3.0, center );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = normal;
	cutShape->axisOfRotation.center = center;
	cutShape->label = label++;
	cutShapeList.push_back( cutShape );

	SetupDynamicLabelUsingCutShape( cutShape );

	lineSegment.Lerp( 5.0 / 6.0, center );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = normal;
	cutShape->axisOfRotation.center = center;
	cutShape->label = label++;
	cutShapeList.push_back( cutShape );

	SetupDynamicLabelUsingCutShape( cutShape );

	normal.Negate();

	lineSegment.Lerp( 1.0 / 3.0, center );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = normal;
	cutShape->axisOfRotation.center = center;
	cutShape->label = label++;
	cutShapeList.push_back( cutShape );

	SetupDynamicLabelUsingCutShape( cutShape );

	lineSegment.Lerp( 1.0 / 6.0, center );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	cutShape->axisOfRotation.normal = normal;
	cutShape->axisOfRotation.center = center;
	cutShape->label = label++;
	cutShapeList.push_back( cutShape );

	SetupDynamicLabelUsingCutShape( cutShape );
}

// CornerTurningOctahedron.cpp