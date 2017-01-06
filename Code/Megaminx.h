// Megaminx.h

#pragma once

#include "TwistyPuzzle.h"

class Megaminx : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Megaminx );

	Megaminx( void );
	virtual ~Megaminx( void );

	virtual void Reset( void ) override;
};

// Megaminx.h
