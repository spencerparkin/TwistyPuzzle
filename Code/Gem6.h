// Gem6.h

#pragma once

#include "TwistyPuzzle.h"

class Gem6 : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( Gem6 );

	Gem6( void );
	virtual ~Gem6( void );

	virtual void Reset( void ) override;
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, bool renderAxisLabels ) override;

	_3DMath::VectorArray vectorArray;
	_3DMath::TriangleMesh mesh;
};

// Gem6.h