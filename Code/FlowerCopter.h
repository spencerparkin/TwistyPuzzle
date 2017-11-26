// FlowerCopter.h

#pragma once

#include "CurvyCopterBase.h"

class FlowerCopter : public CurvyCopterBase
{
public:

	wxDECLARE_DYNAMIC_CLASS( FlowerCopter );

	FlowerCopter( void );
	virtual ~FlowerCopter( void );

	virtual void Reset( void ) override;
	virtual double CalcJumbleTurnAmount( void ) override;
	virtual CutShape* GetEdgeCutShapeByLetter( char letter ) override;
};

// FlowerCopter.h