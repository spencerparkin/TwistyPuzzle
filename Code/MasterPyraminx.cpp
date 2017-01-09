// MasterPyraminx.cpp

#include "MasterPyraminx.h"

wxIMPLEMENT_DYNAMIC_CLASS( MasterPyraminx, PyraminxBase );

MasterPyraminx::MasterPyraminx( void )
{
}

/*virtual*/ MasterPyraminx::~MasterPyraminx( void )
{
}

/*virtual*/ int MasterPyraminx::Layers( void )
{
	return 4;
}

// MasterPyraminx.cpp