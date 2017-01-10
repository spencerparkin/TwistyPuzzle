// IcosahedronSkewb.h

#pragma once

#include "TwistyPuzzle.h"

class IcosahedronSkewb : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( IcosahedronSkewb );

	IcosahedronSkewb( void );
	virtual ~IcosahedronSkewb( void );

	virtual void Reset( void ) override;
};

// IcosahedronSkewb.h