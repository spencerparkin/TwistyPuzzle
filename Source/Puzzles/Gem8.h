// Gem8.h

#pragma once

#include "TwistyPuzzle.h"
#include <Plane.h>

class Gem8 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Gem8 );

	Gem8( void );
	virtual ~Gem8( void );

	virtual void Reset( void ) override;
};

// Gem8.h