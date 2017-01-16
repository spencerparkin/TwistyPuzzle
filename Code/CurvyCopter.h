// CurvyCopter.h

#pragma once

#include "CurvyCopterBase.h"
#include <vector>
#include <map>

class CurvyCopter : public CurvyCopterBase
{
public:

	wxDECLARE_DYNAMIC_CLASS( CurvyCopter );

	CurvyCopter( void );
	virtual ~CurvyCopter( void );

	virtual double CalcJumbleTurnAmount( void ) override;
	virtual _3DMath::Surface* MakeCutSphereSurfaceForEdge( const _3DMath::Vector& edgeCenter ) override;
};

// CurvyCopter.h