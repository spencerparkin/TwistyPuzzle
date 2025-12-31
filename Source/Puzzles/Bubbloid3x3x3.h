// Bubbloid3x3x3.h

#pragma once

#include "TwistyPuzzle.h"

class Bubbloid3x3x3 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Bubbloid3x3x3 );

	Bubbloid3x3x3( void );
	virtual ~Bubbloid3x3x3( void );

	virtual void Reset( void ) override;
	virtual bool SupportsSolve( void ) const override { return true; }
	virtual wxString LocateStabChainFile( void ) const override;
};

// Bubbloid3x3x3.h