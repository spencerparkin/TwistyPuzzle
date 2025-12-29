// Cuboid3x3x3.h

#pragma once

#include "Cuboid3x3x3Base.h"

class Cuboid3x3x5 : public Cuboid3x3x3Base
{
public:

	wxDECLARE_DYNAMIC_CLASS( Cuboid3x3x5 );

	Cuboid3x3x5( void );
	virtual ~Cuboid3x3x5( void );
};

class Cuboid3x3x7 : public Cuboid3x3x3Base
{
public:

	wxDECLARE_DYNAMIC_CLASS( Cuboid3x3x7 );

	Cuboid3x3x7( void );
	virtual ~Cuboid3x3x7( void );
};

class LCube : public Cuboid3x3x3Base
{
	wxDECLARE_DYNAMIC_CLASS( LCube );

	LCube( void );
	virtual ~LCube( void );
};

class XCube : public Cuboid3x3x3Base
{
	wxDECLARE_DYNAMIC_CLASS( XCube );

	XCube( void );
	virtual ~XCube( void );
};

// Cuboid3x3x3.h