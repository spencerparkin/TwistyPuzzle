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
};

// Rubiks3x3x3.h