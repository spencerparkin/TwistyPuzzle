// SquareOne.cpp

#include "SquareOne.h"

wxIMPLEMENT_DYNAMIC_CLASS( SquareOne, TwistyPuzzle );

SquareOne::SquareOne( void )
{
	topCutShapeHandle = 0;
	bottomCutShapeHandle = 0;
	rightCutShapeHandle = 0;
	leftCutShapeHandle = 0;

	wedgeAngleDelta = 2.0 * M_PI / 12.0;
}

/*virtual*/ SquareOne::~SquareOne( void )
{
}

/*virtual*/ void SquareOne::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 1.5, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = wedgeAngleDelta;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	topCutShapeHandle = cutShape->GetHandle();

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -1.5, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = wedgeAngleDelta;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	bottomCutShapeHandle = cutShape->GetHandle();

	_3DMath::Vector normal( -sin( wedgeAngleDelta / 2.0 ), 0.0, cos( wedgeAngleDelta / 2.0 ) );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal = normal;
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	rightCutShapeHandle = cutShape->GetHandle();

	normal.Negate();

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal = normal;
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	leftCutShapeHandle = cutShape->GetHandle();
}

/*virtual*/ bool SquareOne::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	if( topCutShapeHandle == cutShape->GetHandle() )
	{
		// TODO: Calculate cutShape->rotationAngleForSingleTurn for the shape.
		//       This needs to take into account rotation->turnCount.
	}
	else if( bottomCutShapeHandle = cutShape->GetHandle() )
	{
	}
	else if( rightCutShapeHandle == cutShape->GetHandle() )
	{

	}
	else if( leftCutShapeHandle == cutShape->GetHandle() )
	{
	}

	return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );
}

// SquareOne.cpp