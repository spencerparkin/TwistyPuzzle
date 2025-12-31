// FaceTurningOctahedron.h

#pragma once

#include "TwistyPuzzle.h"
#include <LineSegment.h>

class FaceTurningOctahedron : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( FaceTurningOctahedron );

	FaceTurningOctahedron( void );
	virtual ~FaceTurningOctahedron( void );

	virtual void Reset( void ) override;
};

// FaceTurningOctahedron.h