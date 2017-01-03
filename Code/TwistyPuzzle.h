// TwistyPuzzle.h

#pragma once

#include <Vector.h>
#include <Polygon.h>
#include <AffineTransform.h>
#include <wx/glcanvas.h>
#include <Renderer.h>
#include <HandleObject.h>
#include <Line.h>
#include <TimeKeeper.h>
#include <Surface.h>

class TwistyPuzzle : public wxObject
{
public:

	wxDECLARE_ABSTRACT_CLASS( TwistyPuzzle );

	TwistyPuzzle( void );
	virtual ~TwistyPuzzle( void );

	void Clear( void );
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle );
	virtual void Reset( void ) = 0;

	class Rotation
	{
	public:

		enum Direction { DIR_CW, DIR_CCW };

		Rotation( int cutShapeHandle, Direction direction, double turnCount );
		~Rotation( void );

		int cutShapeHandle;
		Direction direction;
		double turnCount;
	};

	typedef std::list< Rotation* > RotationList;

	void EnqueueRotation( Rotation* rotation );
	bool ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper );

	class Face
	{
	public:

		Face( _3DMath::Polygon* polygon );
		~Face( void );

		void UpdateTessellationIfNeeded( void );

		_3DMath::Vector color;
		_3DMath::Polygon* polygon;
		_3DMath::Line axisOfRotation;
		double rotationAngleForAnimation;
		bool tessellationNeeded;
	};

	typedef std::list< Face* > FaceList;

	class CutShape : public _3DMath::HandleObject
	{
	public:

		CutShape( void );
		~CutShape( void );

		void CutAndCapture( FaceList& faceList, FaceList& capturedFaceList );

		_3DMath::Surface* surface;
		_3DMath::Line axisOfRotation;
		_3DMath::Surface::Side captureSide;
		double rotationAngleForSingleTurn;
	};

	typedef std::list< CutShape* > CutShapeList;

protected:

	void MakeBox( double width, double height, double depth );

	FaceList faceList;
	CutShapeList cutShapeList;
	RotationList rotationQueue;
};

// TwistyPuzzle.h
