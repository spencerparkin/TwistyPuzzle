// DreidelCube.h

#pragma once

#include "TwistyPuzzle.h"

class DreidelCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( DreidelCube );

	DreidelCube( void );
	virtual ~DreidelCube( void );

	virtual void Reset( void ) override;
};

// DreidelCube.h