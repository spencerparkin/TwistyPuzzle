// Bagua.h

#pragma once

#include "TwistyPuzzle.h"

class Bagua : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Bagua );

	Bagua( void );
	virtual ~Bagua( void );

	virtual void Reset( void ) override;
};

// Bagua.h