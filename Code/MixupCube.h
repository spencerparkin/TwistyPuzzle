// MixupCube.h

#pragma once

#include "TwistyPuzzle.h"
#include <Surface.h>

class MixupCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( MixupCube );

	MixupCube( void );
	virtual ~MixupCube( void );

	virtual void Reset( void ) override;
};

class MixupLayerCutShape : public TwistyPuzzle::CutShape
{
public:

	MixupLayerCutShape( void );
	virtual ~MixupLayerCutShape( void );

	virtual void CutAndCapture( TwistyPuzzle::FaceList& faceList, TwistyPuzzle::FaceList* capturedFaceList = nullptr, double eps = EPSILON ) override;
	virtual bool CapturesFace( const TwistyPuzzle::Face* face ) override;

	_3DMath::Surface* additionalSurface;
};

// MixupCube.h