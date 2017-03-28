// Rubiks3x3x3.h

#pragma once

#include "TwistyPuzzle.h"

class Rubiks3x3x3 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Rubiks3x3x3 );

	Rubiks3x3x3( void );
	virtual ~Rubiks3x3x3( void );

	virtual void Reset( void ) override;
	virtual bool SupportsSolve( void ) const override { return true; }
	virtual wxString LocateStabChainFile( void ) const override;
	virtual bool ApplyRotationToPermutation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual void Clear( void ) override;

	DoubleSurfaceCutShape* posXSurfaceCutShape;
	DoubleSurfaceCutShape* posYSurfaceCutShape;
	DoubleSurfaceCutShape* posZSurfaceCutShape;
	DoubleSurfaceCutShape* negXSurfaceCutShape;
	DoubleSurfaceCutShape* negYSurfaceCutShape;
	DoubleSurfaceCutShape* negZSurfaceCutShape;

	CutShape* leftCutShape, *rightCutShape;
	CutShape* upCutShape, *downCutShape;
	CutShape* frontCutShape, *backCutShape;
};

// Rubiks3x3x3.h