// CurvyCoperBase.h

#pragma once

#include "TwistyPuzzle.h"
#include <Surface.h>

class CurvyCopterBase : public TwistyPuzzle
{
public:

	wxDECLARE_ABSTRACT_CLASS( CurvyCopterBase );

	CurvyCopterBase( void );
	virtual ~CurvyCopterBase( void );

	virtual void Clear( void ) override;
	virtual void Reset( void ) override;
	virtual bool SpecialAction( double wheelClicks, int selectedObjectHandle, int flags ) override;
	virtual void EnqueueRandomRotations( _3DMath::Random& random, int rotationCount ) override;
	virtual double CalcJumbleTurnAmount( void ) = 0;
	virtual _3DMath::Surface* MakeCutSphereSurfaceForEdge( const _3DMath::Vector& edgeCenter ) { return nullptr; }
	virtual CutShape* GetEdgeCutShapeByLetter( char letter );

	void PopulateJumbleMap( void );

	struct Jumble
	{
		std::vector< int > adjCutShapeHandles;
	};

	typedef std::map< int, Jumble* > JumbleMap;
	JumbleMap jumbleMap;

	void EnqueueJumble( JumbleMap::iterator iter, int flags );
};

// CurvyCopterBase.h
