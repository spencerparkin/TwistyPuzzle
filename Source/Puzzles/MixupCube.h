// MixupCube.h

#pragma once

#include "TwistyPuzzle.h"
#include <Surface.h>

class MixupCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( MixupCube );

	MixupCube( void );
	virtual ~MixupCube( void );

	virtual void Reset( void ) override;
	virtual bool SupportsSolve( void ) const override { return true; }
	virtual wxString LocateStabChainFile( void ) const override;
};

// MixupCube.h