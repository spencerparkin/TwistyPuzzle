// Skewb.h

#pragma once

#include "TwistyPuzzle.h"

class Skewb : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Skewb );

	Skewb( void );
	virtual ~Skewb( void );

	virtual void Reset( void ) override;
};

// Skewb.h