// Pyraminx.h

#pragma once

#include "PyraminxBase.h"

class Pyraminx : public PyraminxBase
{
public:

	wxDECLARE_DYNAMIC_CLASS( Pyraminx );

	Pyraminx( void );
	virtual ~Pyraminx( void );

	virtual int Layers( void );
};

// Pyraminx.h