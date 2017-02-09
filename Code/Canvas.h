// Canvas.h

#pragma once

#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <Vector.h>
#include <AffineTransform.h>
#include "wxTimeKeeper.h"

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

	enum RenderFlag
	{
		RENDER_AXES =				0x00000001,
		RENDER_AXIS_LABELS =		0x00000002,
		RENDER_STATS =				0x00000004,
		RENDER_BORDERS =			0x00000008,
		RENDER_DIFF =				0x00000010,
	};

	void SetRenderFlags( int renderFlags );
	int GetRenderFlags( void ) { return renderFlags; }

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
	void OnMouseRightDoubleClick( wxMouseEvent& event );
	void OnKeyDown( wxKeyEvent& event );

	void BindContext( void );
	void Render( GLenum renderMode, wxPoint* mousePos = nullptr, int* objectHandle = nullptr );

	class Grip
	{
	public:

		Grip( void );
		~Grip( void );

		bool PartiallyRotate( Canvas* canvas );
		bool CommitPartialRotation( Canvas* canvas );

		int DetermineCutShapeAndRotation( Canvas* canvas );
	};

	double foviAngle;
	wxGLContext* context;
	GLRenderer* renderer;
	_3DMath::AffineTransform transform;
	double eyeDistance;
	wxPoint mouseDragLastPos, mouseDragClickPos, mouseDragCurrentPos;
	enum MouseDragMode { DRAG_MODE_NONE, DRAG_MODE_ORIENT_PUZZLE, DRAG_MODE_ROTATE_FACES };
	MouseDragMode mouseDragMode;
	int selectedObjectHandle;
	wxTimeKeeper timeKeeper;
	Grip* grip;
	int renderFlags;
#if defined LINUX
	double timeOfLastWheelClickSeconds;
#endif
};

// Canvas.h
