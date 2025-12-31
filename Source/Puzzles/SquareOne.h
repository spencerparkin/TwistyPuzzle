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

	virtual void Clear( void ) override;
	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual Rotation* CalculateNearestRotation( CutShape* cutShape ) override;
	virtual bool LoadFromXml( const wxXmlDocument& xmlDocument ) override;
	virtual bool SaveToXml( wxXmlDocument& xmlDocument ) const override;

	int topCutShapeHandle;
	int bottomCutShapeHandle;
	int rightCutShapeHandle;
	int leftCutShapeHandle;

	double wedgeAngle;

	struct Wedge
	{
		int size;
		Wedge* next;
		Wedge* prev;
	};

	Wedge* topRight;
	Wedge* topLeft;
	Wedge* bottomRight;
	Wedge* bottomLeft;
	Wedge* wedgeArray;

	int Advance( Wedge*& wedgeA, Wedge*& wedgeB, Rotation::Direction direction );
	void AdvanceAndAccumulate( Wedge*& wedge, Rotation::Direction direction, int& totalSize );

	void SanityCheck( void );
};

// SquareOne.h