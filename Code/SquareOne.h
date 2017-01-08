// SquareOne.h

#pragma once

#include "TwistyPuzzle.h"
#include <vector>

class SquareOne : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( SquareOne );

	SquareOne( void );
	virtual ~SquareOne( void );

	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual Rotation* CalculateNearestRotation( CutShape* cutShape, double rotationAngle ) override;

	int topCutShapeHandle;
	int bottomCutShapeHandle;
	int rightCutShapeHandle;
	int leftCutShapeHandle;

	double wedgeAngleDelta;

	// TODO: Add data-structure for managing wedge-unit state on top and bottom.
};

// SquareOne.h