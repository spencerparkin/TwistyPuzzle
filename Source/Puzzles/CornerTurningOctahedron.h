// CornerTurningOctahedron.h

#pragma once

#include "TwistyPuzzle.h"

class CornerTurningOctahedron : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( CornerTurningOctahedron );

	CornerTurningOctahedron( void );
	virtual ~CornerTurningOctahedron( void );

	virtual void Reset( void ) override;

	void MakeCutPlanes( const _3DMath::LineSegment& lineSegment, char& label );
};

// CornerTurningOctahedron.h