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

	typedef std::vector< int > WedgeSizeArray;
	WedgeSizeArray* topWedgeSizeArray;
	WedgeSizeArray* bottomWedgeSizeArray;

	int topRight, topLeft;
	int bottomRight, bottomLeft;

	enum Side { SIDE_LEFT, SIDE_RIGHT };

	int RotateIndices( int& topRight, int& topLeft, const WedgeSizeArray& wedgeSizeArray, int delta, int rotationCount );
	void MoveIndex( int& index, int& balance, const WedgeSizeArray& wedgeSizeArray, int delta, Side side );

	static int Wrap( int i, int modulus );
};

// SquareOne.h