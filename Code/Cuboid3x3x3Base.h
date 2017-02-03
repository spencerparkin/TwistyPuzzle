// Cuboid3x3x3Base.h

#pragma once

#include "TwistyPuzzle.h"

class Cuboid3x3x3Base : public TwistyPuzzle
{
public:

	wxDECLARE_ABSTRACT_CLASS( Cuboid3x3x3Base );

	Cuboid3x3x3Base( int negX, int posX, int negY, int posY, int negZ, int posZ );
	virtual ~Cuboid3x3x3Base( void );

	virtual void Clear( void ) override;
	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;

	void MakeHead( const _3DMath::LinearTransform& linearTransform, int extrusion );

	int negX, posX;
	int negY, posY;
	int negZ, posZ;
};

// Cuboid3x3x3Base.h