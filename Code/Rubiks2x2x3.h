// Rubiks2x2x3.h

#pragma once

#include "TwistyPuzzle.h"

class Rubiks2x2x3 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Rubiks2x2x3 );

	Rubiks2x2x3( void );
	virtual ~Rubiks2x2x3( void );

	virtual void Reset( void ) override;
};

// Rubiks2x2x3.h