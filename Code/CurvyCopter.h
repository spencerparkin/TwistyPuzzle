// CurvyCopter.h

#pragma once

#include "TwistyPuzzle.h"

// TODO: Make the CurvyCopterTwo and CurvyCopterThree.
// TODO: I think we can get the jumble move working.
class CurvyCopter : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( CurvyCopter );

	CurvyCopter( void );
	virtual ~CurvyCopter( void );

	virtual void Reset( void ) override;
};

// CurvyCopter.h