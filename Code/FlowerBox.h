// FlowerBox.h

#pragma once

#include "TwistyPuzzle.h"

class FlowerBox : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( FlowerBox );

	FlowerBox( void );
	virtual ~FlowerBox( void );

	virtual void Reset( void ) override;
};

// FlowerBox.h
