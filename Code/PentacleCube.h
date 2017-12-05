// PentacleCube.h

#pragma once

#include "TwistyPuzzle.h"

class PentacleCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( PentacleCube );

	PentacleCube( void );
	virtual ~PentacleCube( void );

	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
};

// PentacleCube.h
