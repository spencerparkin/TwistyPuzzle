// Rubiks2x2x2.h

#pragma once

#include "TwistyPuzzle.h"

class Rubiks2x2x2 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Rubiks2x2x2 );

	Rubiks2x2x2( void );
	virtual ~Rubiks2x2x2( void );

	virtual void Reset( void ) override;
	virtual bool SupportsSolve( void ) const override { return true; }
	virtual wxString LocateStabChainFile( void ) const override;
};

// Rubiks2x2x2.h