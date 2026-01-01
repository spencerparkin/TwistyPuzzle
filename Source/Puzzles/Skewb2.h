// Skewb2.h

#pragma once

#include "TwistyPuzzle.h"

class Skewb2 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Skewb2 );

	Skewb2( void );
	virtual ~Skewb2( void );

	virtual void Reset( void ) override;
};

// Skewb2.h