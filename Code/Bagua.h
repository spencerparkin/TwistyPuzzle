// Bagua.h

#pragma once

#include "TwistyPuzzle.h"

// TODO: This is just a cube with shallow face cuts where each face turns in 45 degree increments.
//       The key to making this work is to require a pre-cut sequence be executed before the user
//       can use the puzzle.  Then we require that no move the user makes from that point onward
//       is allowed to cut the puzzle.  This will simulate the internal bandaging.
class Bagua : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Bagua );

	Bagua( void );
	virtual ~Bagua( void );

	virtual void Reset( void ) override;
};

// Bagua.h