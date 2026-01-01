// Bagua.cpp

#include "Bagua.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( Bagua, TwistyPuzzle );

Bagua::Bagua( void )
{
}

/*virtual*/ Bagua::~Bagua( void )
{
}

/*virtual*/ void Bagua::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	double distance = 2.4;

	CutShape* rightCutShape = new CutShape();
	rightCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( distance, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	rightCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	rightCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	rightCutShape->label = 'R';
	cutShapeList.push_back( rightCutShape );

	CutShape* leftCutShape = new CutShape();
	leftCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -distance, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	leftCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	leftCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	leftCutShape->label = 'L';
	cutShapeList.push_back( leftCutShape );

	CutShape* upCutShape = new CutShape();
	upCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, distance, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	upCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	upCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	upCutShape->label = 'U';
	cutShapeList.push_back( upCutShape );

	CutShape* downCutShape = new CutShape();
	downCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -distance, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	downCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	downCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	downCutShape->label = 'D';
	cutShapeList.push_back( downCutShape );

	CutShape* frontCutShape = new CutShape();
	frontCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, distance ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	frontCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	frontCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	frontCutShape->label = 'F';
	cutShapeList.push_back( frontCutShape );

	CutShape* backCutShape = new CutShape();
	backCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -distance ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	backCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
	backCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	backCutShape->label = 'B';
	cutShapeList.push_back( backCutShape );

	// L, R

	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	// U, D

	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	// F, B

	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( leftCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( rightCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CCW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( upCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( downCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	EnqueueRotation( new Rotation( frontCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );
	EnqueueRotation( new Rotation( backCutShape->GetHandle(), Rotation::DIR_CW, 1.0, Rotation::FLAG_PRECUT ) );

	// Unlike most puzzles, here we pre-cut the puzzle, then we don't allow any future cuts for bandaging purposes.
	FlushRotationQueue();

	canCut = false;

	SetupDynamicLabelsUsingCutShapeList();
}

// Bagua.cpp