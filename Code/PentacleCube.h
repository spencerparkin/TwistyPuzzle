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
	virtual bool SupportsSolve( void ) const override { return false; }
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, int renderFlags ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual bool LoadFromXml( const wxXmlDocument& xmlDocument ) override;
	virtual bool SaveToXml( wxXmlDocument& xmlDocument ) const override;
	virtual void EnqueueRandomRotations( _3DMath::Random& random, int rotationCount ) override;

	void GetAdjacentSides( char side, std::list< char >& sideList );

	typedef std::map< char, _3DMath::Vector > VectorMap;
	VectorMap vectorMap;
};

// PentacleCube.h
