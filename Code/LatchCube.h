// LatchCube.h

#pragma once

#include "Rubiks3x3x3.h"
#include "Vector.h"

class LatchCube : public Rubiks3x3x3
{
public:

	wxDECLARE_DYNAMIC_CLASS( LatchCube );

	LatchCube( void );
	virtual ~LatchCube( void );

	virtual void Reset( void ) override;
	virtual bool SupportsSolve( void ) const override { return false; }
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, int renderFlags ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual void ApplyingTransformWithRotation( const _3DMath::AffineTransform& transform, const Rotation* rotation ) override;

	struct Constraint
	{
		Rotation::Direction direction;
		_3DMath::Vector location;
	};

	typedef std::list< Constraint > ConstraintList;
	ConstraintList constraintList;

	bool CanRotate( const Rotation* rotation ) const;
};

// LatchCube.h
