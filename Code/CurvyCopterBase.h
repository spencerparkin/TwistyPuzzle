// CurvyCoperBase.h

#pragma once

#include "TwistyPuzzle.h"

class CurvyCopterBase : public TwistyPuzzle
{
public:

	wxDECLARE_ABSTRACT_CLASS( CurvyCopterBase );

	CurvyCopterBase( void );
	virtual ~CurvyCopterBase( void );

	virtual void Clear( void ) override;
	virtual void Reset( void ) override;
	virtual bool SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown ) override;
	virtual void EnqueueRandomRotations( _3DMath::Random& random, int rotationCount ) override;
	virtual double CalcJumbleTurnAmount( void ) = 0;
	virtual double CutSphereRadius( void ) = 0;

	struct Jumble
	{
		std::vector< int > adjCutShapeHandles;
	};

	typedef std::map< int, Jumble* > JumbleMap;
	JumbleMap jumbleMap;

	void EnqueueJumble( JumbleMap::iterator iter, bool shiftDown );
};

// CurvyCopterBase.h
