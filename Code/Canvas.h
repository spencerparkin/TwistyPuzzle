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

	enum AxisSelectMode
	{
		AXIS_SELECT_MANUAL,
		AXIS_SELECT_AUTO,
	};

	AxisSelectMode axisSelectMode;

	void SetRenderAxisLabels( bool renderAxisLabels );
	bool GetRenderAxisLabels( void ) { return renderAxisLabels; }

private:

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseWheel( wxMouseEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseMiddleDown( wxMouseEvent& event );
	void OnMouseMiddleUp( wxMouseEvent& event );
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

		int DetermineCutShapeAndRotation( Canvas* canvas, double& rotationAngle );
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
	bool renderAxisLabels;
};

// Canvas.h
