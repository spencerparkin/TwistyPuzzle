// SkewbDiamond.h

#pragma once

#include "TwistyPuzzle.h"

class SkewbDiamond : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( SkewbDiamond );

	SkewbDiamond( void );
	virtual ~SkewbDiamond( void );

	virtual void Reset( void ) override;
};

// SkewbDiamond.h