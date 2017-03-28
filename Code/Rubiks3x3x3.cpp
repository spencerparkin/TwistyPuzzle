// Rubiks3x3x3.cpp

#include "Rubiks3x3x3.h"
#include "Application.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Rubiks3x3x3, TwistyPuzzle );

Rubiks3x3x3::Rubiks3x3x3( void )
{
	posXSurfaceCutShape = nullptr;
	posYSurfaceCutShape = nullptr;
	posZSurfaceCutShape = nullptr;
	negXSurfaceCutShape = nullptr;
	negYSurfaceCutShape = nullptr;
	negZSurfaceCutShape = nullptr;

	leftCutShape = rightCutShape = nullptr;
	upCutShape = downCutShape = nullptr;
	frontCutShape = backCutShape = nullptr;
}

/*virtual*/ Rubiks3x3x3::~Rubiks3x3x3( void )
{
}

/*virtual*/ void Rubiks3x3x3::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	rightCutShape = new CutShape();
	rightCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	rightCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	rightCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	rightCutShape->label = 'R';
	rightCutShape->ccwPermutation.DefineCycle( 24, 29, 31, 26 );
	rightCutShape->ccwPermutation.DefineCycle( 25, 27, 30, 28 );
	rightCutShape->ccwPermutation.DefineCycle( 2, 18, 42, 37 );
	rightCutShape->ccwPermutation.DefineCycle( 4, 20, 44, 35 );
	rightCutShape->ccwPermutation.DefineCycle( 7, 23, 47, 32 );
	cutShapeList.push_back( rightCutShape );

	leftCutShape = new CutShape();
	leftCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	leftCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	leftCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	leftCutShape->label = 'L';
	leftCutShape->ccwPermutation.DefineCycle( 8, 13, 15, 10 );
	leftCutShape->ccwPermutation.DefineCycle( 9, 11, 14, 12 );
	leftCutShape->ccwPermutation.DefineCycle( 0, 39, 40, 16 );
	leftCutShape->ccwPermutation.DefineCycle( 3, 36, 43, 19 );
	leftCutShape->ccwPermutation.DefineCycle( 5, 34, 45, 21 );
	cutShapeList.push_back( leftCutShape );

	upCutShape = new CutShape();
	upCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	upCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	upCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	upCutShape->label = 'U';
	upCutShape->ccwPermutation.DefineCycle( 0, 5, 7, 2 );
	upCutShape->ccwPermutation.DefineCycle( 1, 3, 6, 4 );
	upCutShape->ccwPermutation.DefineCycle( 8, 16, 24, 32 );
	upCutShape->ccwPermutation.DefineCycle( 9, 17, 25, 33 );
	upCutShape->ccwPermutation.DefineCycle( 10, 18, 26, 34 );
	cutShapeList.push_back( upCutShape );

	downCutShape = new CutShape();
	downCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	downCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	downCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	downCutShape->label = 'D';
	downCutShape->ccwPermutation.DefineCycle( 40, 45, 47, 42 );
	downCutShape->ccwPermutation.DefineCycle( 41, 43, 46, 44 );
	downCutShape->ccwPermutation.DefineCycle( 13, 37, 29, 21 );
	downCutShape->ccwPermutation.DefineCycle( 14, 38, 30, 22 );
	downCutShape->ccwPermutation.DefineCycle( 15, 39, 31, 23 );
	cutShapeList.push_back( downCutShape );

	frontCutShape = new CutShape();
	frontCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	frontCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	frontCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	frontCutShape->label = 'F';
	frontCutShape->ccwPermutation.DefineCycle( 16, 21, 23, 18 );
	frontCutShape->ccwPermutation.DefineCycle( 17, 19, 22, 20 );
	frontCutShape->ccwPermutation.DefineCycle( 5, 15, 42, 24 );
	frontCutShape->ccwPermutation.DefineCycle( 6, 12, 41, 27 );
	frontCutShape->ccwPermutation.DefineCycle( 7, 10, 40, 29 );
	cutShapeList.push_back( frontCutShape );

	backCutShape = new CutShape();
	backCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	backCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	backCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	backCutShape->label = 'B';
	backCutShape->ccwPermutation.DefineCycle( 32, 37, 39, 34 );
	backCutShape->ccwPermutation.DefineCycle( 33, 35, 38, 36 );
	backCutShape->ccwPermutation.DefineCycle( 2, 31, 45, 8 );
	backCutShape->ccwPermutation.DefineCycle( 1, 28, 46, 11 );
	backCutShape->ccwPermutation.DefineCycle( 0, 26, 47, 13 );
	cutShapeList.push_back( backCutShape );

	// Disable for now; this is too much of a pain in the butt.
	// I believe there is a way to do this, but I'm too lazy to get it correct right now.
#if 0
	Permutation cwLeft, cwRight;
	Permutation cwUp, cwDown;
	Permutation cwBack, cwFront;

	leftCutShape->ccwPermutation.GetInverse( cwLeft );
	rightCutShape->ccwPermutation.GetInverse( cwRight );
	upCutShape->ccwPermutation.GetInverse( cwUp );
	downCutShape->ccwPermutation.GetInverse( cwDown );
	backCutShape->ccwPermutation.GetInverse( cwBack );
	frontCutShape->ccwPermutation.GetInverse( cwFront );

	posXSurfaceCutShape = new DoubleSurfaceCutShape();
	posXSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	posXSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	posXSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	posXSurfaceCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	posXSurfaceCutShape->vectorLength = 12.0;
	posXSurfaceCutShape->label = 'X';
	posXSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	posXSurfaceCutShape->ccwPermutation.Multiply( cwRight, leftCutShape->ccwPermutation );
	cutShapeList.push_back( posXSurfaceCutShape );

	posYSurfaceCutShape = new DoubleSurfaceCutShape();
	posYSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	posYSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	posYSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	posYSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	posYSurfaceCutShape->vectorLength = 12.0;
	posYSurfaceCutShape->label = 'Y';
	posYSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	posYSurfaceCutShape->ccwPermutation.Multiply( cwUp, downCutShape->ccwPermutation );
	cutShapeList.push_back( posYSurfaceCutShape );

	posZSurfaceCutShape = new DoubleSurfaceCutShape();
	posZSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	posZSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	posZSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	posZSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	posZSurfaceCutShape->vectorLength = 12.0;
	posZSurfaceCutShape->label = 'Z';
	posZSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	posZSurfaceCutShape->ccwPermutation.Multiply( cwFront, backCutShape->ccwPermutation );
	cutShapeList.push_back( posZSurfaceCutShape );

	negXSurfaceCutShape = new DoubleSurfaceCutShape();
	negXSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	negXSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	negXSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	negXSurfaceCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	negXSurfaceCutShape->vectorLength = 12.0;
	negXSurfaceCutShape->label = 'x';
	negXSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	negXSurfaceCutShape->ccwPermutation.SetInverse( posXSurfaceCutShape->ccwPermutation );
	cutShapeList.push_back( negXSurfaceCutShape );

	negYSurfaceCutShape = new DoubleSurfaceCutShape();
	negYSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	negYSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	negYSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	negYSurfaceCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	negYSurfaceCutShape->vectorLength = 12.0;
	negYSurfaceCutShape->label = 'y';
	negYSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	negYSurfaceCutShape->ccwPermutation.SetInverse( posYSurfaceCutShape->ccwPermutation );
	cutShapeList.push_back( negYSurfaceCutShape );

	negZSurfaceCutShape = new DoubleSurfaceCutShape();
	negZSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	negZSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	negZSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	negZSurfaceCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	negZSurfaceCutShape->vectorLength = 12.0;
	negZSurfaceCutShape->label = 'z';
	negZSurfaceCutShape->captureSide = _3DMath::Surface::INSIDE;
	negZSurfaceCutShape->ccwPermutation.SetInverse( posZSurfaceCutShape->ccwPermutation );
	cutShapeList.push_back( negZSurfaceCutShape );
#endif

	SetupDynamicLabelsUsingCutShapeList();
}

/*virtual*/ void Rubiks3x3x3::Clear( void )
{
	TwistyPuzzle::Clear();

	posXSurfaceCutShape = nullptr;
	posYSurfaceCutShape = nullptr;
	posZSurfaceCutShape = nullptr;
	negXSurfaceCutShape = nullptr;
	negYSurfaceCutShape = nullptr;
	negZSurfaceCutShape = nullptr;

	leftCutShape = rightCutShape = nullptr;
	upCutShape = downCutShape = nullptr;
	frontCutShape = backCutShape = nullptr;
}

/*virtual*/ wxString Rubiks3x3x3::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/Rubiks3x3x3.txt" );
}

/*virtual*/ bool Rubiks3x3x3::ApplyRotationToPermutation( CutShape* cutShape, const Rotation* rotation )
{
	if( !TwistyPuzzle::ApplyRotationToPermutation( cutShape, rotation ) )
		return false;

#if 0
	typedef std::vector< CutShape* > CutShapeArray;
	CutShapeArray cutShapeArray;
	int rollDir = 1;
	int rollCount = ( int )abs( rotation->turnCount );

	if( rotation->direction == Rotation::DIR_CW )
		rollDir *= -1;

	if( rotation->turnCount < 0.0 )
		rollDir *= -1;

	// This is rather complicated, but if we want to support the middle slices,
	// we need to account for them as actually rotated outer slices while also
	// re-orienting the entire puzzle.
	if( cutShape == posXSurfaceCutShape || cutShape == negXSurfaceCutShape )
	{
		cutShapeArray.push_back( backCutShape );
		cutShapeArray.push_back( upCutShape );
		cutShapeArray.push_back( frontCutShape );
		cutShapeArray.push_back( downCutShape );
		
		if( cutShape == negXSurfaceCutShape )
			rollDir *= -1;
	}
	else if( cutShape == posYSurfaceCutShape || cutShape == negYSurfaceCutShape )
	{
		cutShapeArray.push_back( frontCutShape );
		cutShapeArray.push_back( rightCutShape );
		cutShapeArray.push_back( backCutShape );
		cutShapeArray.push_back( leftCutShape );

		if( cutShape == negYSurfaceCutShape )
			rollDir *= -1;
	}
	else if( cutShape == posZSurfaceCutShape || cutShape == negZSurfaceCutShape )
	{
		cutShapeArray.push_back( downCutShape );
		cutShapeArray.push_back( leftCutShape );
		cutShapeArray.push_back( upCutShape );
		cutShapeArray.push_back( rightCutShape );

		if( cutShape == negZSurfaceCutShape )
			rollDir *= -1;
	}

	if( cutShapeArray.size() > 0 )
	{
		while( rollCount > 0 )
		{
			if( rollDir < 0 )
			{
				Permutation ccwPermutation = cutShapeArray[0]->ccwPermutation;
				for( uint i = 0; i < cutShapeArray.size() - 1; i++ )
					cutShapeArray[i]->ccwPermutation = cutShapeArray[ i + 1 ]->ccwPermutation;
				cutShapeArray[ cutShapeArray.size() - 1 ]->ccwPermutation = ccwPermutation;
			}
			else
			{
				Permutation ccwPermutation = cutShapeArray[ cutShapeArray.size() - 1 ]->ccwPermutation;
				for( uint i = cutShapeArray.size() - 1; i > 0; i-- )
					cutShapeArray[i]->ccwPermutation = cutShapeArray[ i - 1 ]->ccwPermutation;
				cutShapeArray[0]->ccwPermutation = ccwPermutation;
			}

			rollCount--;
		}
	}
#endif

	return true;
}

// Rubiks3x3x3.cpp