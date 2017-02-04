// Cuboid3x3x3.cpp

#include "Cuboid3x3x3.h"

#if 0

wxIMPLEMENT_DYNAMIC_CLASS( Cuboid3x3x5, Cuboid3x3x3Base );

Cuboid3x3x5::Cuboid3x3x5( void ) : Cuboid3x3x3Base( 0, 0, 1, 1, 0, 0 )
{
}

/*virtual*/ Cuboid3x3x5::~Cuboid3x3x5( void )
{
}

wxIMPLEMENT_DYNAMIC_CLASS( Cuboid3x3x7, Cuboid3x3x3Base );

Cuboid3x3x7::Cuboid3x3x7( void ) : Cuboid3x3x3Base( 0, 0, 2, 2, 0, 0 )
{
}

/*virtual*/ Cuboid3x3x7::~Cuboid3x3x7( void )
{
}

wxIMPLEMENT_DYNAMIC_CLASS( LCube, Cuboid3x3x3Base );

LCube::LCube( void ) : Cuboid3x3x3Base( 1, 0, 1, 0, 0, 0 )
{
}

/*virtual*/ LCube::~LCube( void )
{
}

wxIMPLEMENT_DYNAMIC_CLASS( XCube, Cuboid3x3x3Base );

XCube::XCube( void ) : Cuboid3x3x3Base( 1, 1, 1, 1, 0, 0 )
{
}

/*virtual*/ XCube::~XCube( void )
{
}

#endif

// Cuboid3x3x3.cpp