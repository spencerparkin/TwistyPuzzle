// EitansStar.h

#pragma once

#include "TwistyPuzzle.h"

class EitansStar : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( EitansStar );

	EitansStar( void );
	virtual ~EitansStar( void );

	virtual void Reset( void ) override;
};

// EitansStar.h