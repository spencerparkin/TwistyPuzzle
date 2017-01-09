// BauhiniaDodecahedron.h

#pragma once

#include "TwistyPuzzle.h"

class BauhiniaDodecahedron : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( BauhiniaDodecahedron );

	BauhiniaDodecahedron( void );
	virtual ~BauhiniaDodecahedron( void );

	virtual void Reset( void ) override;
};

// BauhiniaDodecahedron.h