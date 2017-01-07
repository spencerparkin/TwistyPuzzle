// Canvas.h

#pragma once

#include <wx/glcanvas.h>
#include <Vector.h>
#include <AffineTransform.h>
#include <TimeKeeper.h>

class GLRenderer;

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

	void Animate( void );

	GLRenderer* GetRenderer( void ) { return renderer; }

private:

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseWheel( wxMouseEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseRightDown( wxMouseEvent& event );
	void OnMouseRightUp( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );
	void OnMouseCaptureLost( wxMouseCaptureLostEvent& event );

	void BindContext( void );
	void Render( GLenum renderMode, wxPoint* mousePos = nullptr, int* objectHandle = nullptr );

	class Grip
	{
	public:

		Grip( void );
		~Grip( void );

		bool PartiallyRotate( Canvas* canvas );
		bool CommitRotation( Canvas* canvas );

		int DetermineEffectedCutShape( Canvas* canvas, _3DMath::Vector& mouseVector );
		double CalculateRotationAngle( const _3DMath::Vector& mouseVector );
	};

	wxGLContext* context;
	GLRenderer* renderer;
	_3DMath::AffineTransform transform;
	double eyeDistance;
	wxPoint mouseDragLastPos, mouseDragClickPos, mouseDragCurrentPos;
	enum MouseDragMode { DRAG_MODE_NONE, DRAG_MODE_ORIENT_PUZZLE, DRAG_MODE_ROTATE_FACES };
	MouseDragMode mouseDragMode;
	int selectedObjectHandle;
	_3DMath::TimeKeeper timeKeeper;
	Grip* grip;
};

// Canvas.h
