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

// TODO: It would be interesting if we based a puzzle off of, say, cone-shaped cut objects.
//       This would require that we trace out parts of conic sections.  Calculus methods would be in order?

// TODO: Ideas for puzzles we could implement: Skweb, master skweb, pyraminx, face-turning octahedron,
//       corner-turning octahedron, 2x2x3, 3x3x2, there are many more.

class TwistyPuzzle : public wxObject
{
public:

	wxDECLARE_ABSTRACT_CLASS( TwistyPuzzle );

	TwistyPuzzle( void );
	virtual ~TwistyPuzzle( void );

	bool Load( const wxString& file );
	bool Save( const wxString& file ) const;

	virtual void Clear( void );
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle );
	virtual void Reset( void ) = 0;
	virtual bool SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown );

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

	// Compute and return a sequence of rotations that gets us closer, if
	// not all the way, to the solved state of the puzzle.  The method is
	// called until an empty list is returned.
	virtual void IncrementallySolve( RotationList& rotationList ) const;
	virtual bool SolveSupported( void ) const { return false; }

	void EnqueueRotation( Rotation* rotation );
	bool ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper );

	class Face
	{
	public:

		Face( _3DMath::Polygon* polygon );
		~Face( void );

		void UpdateTessellationIfNeeded( void );
		void Render( _3DMath::Renderer& renderer, GLenum renderMode, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform ) const;

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
	void MakeIcosahedron( double radius );
	void MakeDodecahedron( double radius );

	static _3DMath::Vector ColorTable( int index );

	static _3DMath::Vector red, green, blue, magenta, cyan, yellow;
	static _3DMath::Vector orange, maroon, white, pink, lime, indigo;

	FaceList faceList;
	CutShapeList cutShapeList;
	RotationList rotationQueue;
};

// TwistyPuzzle.h
