// CurvyCopter3.h

#pragma once

#include "CurvyCopterBase.h"

class CurvyCopter3 : public CurvyCopterBase
{
public:

	wxDECLARE_DYNAMIC_CLASS( CurvyCopter3 );

	CurvyCopter3( void );
	virtual ~CurvyCopter3( void );

	virtual double CalcJumbleTurnAmount( void ) override;
	virtual _3DMath::Surface* MakeCutSphereSurfaceForEdge( const _3DMath::Vector& edgeCenter ) override;
};

// CurvyCopter3.h
