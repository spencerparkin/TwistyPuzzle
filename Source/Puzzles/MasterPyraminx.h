// MasterPyraminx.h

#pragma once

#include "PyraminxBase.h"

class MasterPyraminx : public PyraminxBase
{
public:

	wxDECLARE_DYNAMIC_CLASS( MasterPyraminx );

	MasterPyraminx( void );
	virtual ~MasterPyraminx( void );

	virtual int Layers( void );
};

// MasterPyraminx.h