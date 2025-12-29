// Dogic.h

#pragma once

#include "TwistyPuzzle.h"

class Dogic : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Dogic );

	Dogic( void );
	virtual ~Dogic( void );

	virtual void Reset( void ) override;
};

// Dogic.h