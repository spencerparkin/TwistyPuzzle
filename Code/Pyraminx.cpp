// Pyraminx.cpp

#include "Pyraminx.h"

wxIMPLEMENT_DYNAMIC_CLASS( Pyraminx, PyraminxBase );

Pyraminx::Pyraminx( void )
{
}

/*virtual*/ Pyraminx::~Pyraminx( void )
{
}

/*virtual*/ int Pyraminx::Layers( void )
{
	return 3;
}

// Pyraminx.cpp