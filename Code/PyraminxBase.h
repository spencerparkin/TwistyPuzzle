// PyraminxBase.h

#pragma once

#include "TwistyPuzzle.h"

class PyraminxBase : public TwistyPuzzle
{
public:

	wxDECLARE_ABSTRACT_CLASS( PyraminxBase );

	PyraminxBase( void );
	virtual ~PyraminxBase( void );

	virtual void Reset( void ) override;

	virtual int Layers( void ) = 0;
};

// Pyraminx.h