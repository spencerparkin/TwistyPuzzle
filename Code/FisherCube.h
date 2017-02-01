// FisherCube.h

#pragma once

#include "TwistyPuzzle.h"

class FisherCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( FisherCube );

	FisherCube( void );
	virtual ~FisherCube( void );

	virtual void Reset( void ) override;
};

// FisherCube.h