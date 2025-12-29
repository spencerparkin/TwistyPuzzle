// SkewbUltimate.h

#pragma once

#include "TwistyPuzzle.h"

class SkewbUltimate : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( SkewbUltimate );

	SkewbUltimate( void );
	virtual ~SkewbUltimate( void );

	virtual void Reset( void ) override;
};

// SkewbUltimate.h