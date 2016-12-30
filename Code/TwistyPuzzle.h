// TwistyPuzzle.h

#pragma once

#include <Vector.h>
#include <Polygon.h>
#include <AffineTransform.h>
#include <wx/glcanvas.h>
#include <Renderer.h>
#include <HandleObject.h>
#include <Line.h>

class TwistyPuzzle
{
public:

	TwistyPuzzle( void );
	virtual ~TwistyPuzzle( void );

	void Clear( void );
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle );
	virtual void Reset( void ) = 0;

	class Face
	{
	public:

		Face( _3DMath::Polygon* polygon );
		~Face( void );

		_3DMath::Vector color;
		_3DMath::Polygon* polygon;
		_3DMath::AffineTransform transform;
		bool tessellationNeeded;
	};

	typedef std::list< Face* > FaceList;

	class CutShape : public _3DMath::HandleObject
	{
	public:

		CutShape( void );
		~CutShape( void );

		void CutAndCapture( FaceList& faceList );

		_3DMath::Surface* surface;
		_3DMath::Line axisOfRotation;
		double rotationAngleForSingleTurn;
		FaceList capturedFaceList;
	};

	typedef std::list< CutShape* > CutShapeList;

protected:

	void MakeBox( double width, double height, double depth );

	FaceList faceList;
	CutShapeList cutShapeList;
};

// TwistyPuzzle.h
