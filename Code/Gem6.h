// Gem6.h

#pragma once

#include "TwistyPuzzle.h"
#include <Plane.h>

class Gem6 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Gem6 );

	Gem6( void );
	virtual ~Gem6( void );

	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual double PolygonOutlineScaleFactor( void ) const override { return 1.005; }

	static void AddPlaneIfNotFound( _3DMath::PlaneList& planeList, const _3DMath::Plane& newPlane );
};

// Gem6.h