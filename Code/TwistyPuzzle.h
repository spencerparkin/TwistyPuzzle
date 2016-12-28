// TwistyPuzzle.h

#pragma once

#include <Vector.h>
#include <Polygon.h>
#include <AffineTransform.h>
#include <wx/glcanvas.h>
#include <Renderer.h>

class TwistyPuzzle
{
public:

	TwistyPuzzle( void );
	virtual ~TwistyPuzzle( void );

	enum Type
	{
		CLASSIC_2x2x2,
		CLASSIC_3x3x3,
		CLASSIC_4x4x4,
		BUBBLOID_3x3x4,
		BUBBLOID_3x4x4,
		CURVEY_COPTER,
		REX_CUBE,
	};

	void Clear( void );
	void SetType( Type type );
	Type GetType( void ) const { return type; }
	void Render( _3DMath::Renderer& renderer );

	class Face
	{
	public:

		Face( void );
		~Face( void );

		_3DMath::Vector color;
		_3DMath::Polygon polygon;
		_3DMath::AffineTransform transform;
		bool tessellationNeeded;
	};

	typedef std::list< Face* > FaceList;

	class CutShape
	{
	public:

		CutShape( void );
		~CutShape( void );

		void CutAndCapture( FaceList& faceList );

		_3DMath::Surface* surface;
		_3DMath::Vector unitRotationAxis;
		double rotationAngle;
		double rotationDivisor;
		FaceList capturedFaceList;
	};

	typedef std::list< CutShape* > CutShapeList;

private:

	void MakeBox( double width, double height, double depth );

	Type type;
	FaceList faceList;
	CutShapeList cutShapeList;
};

// TwistyPuzzle.h
