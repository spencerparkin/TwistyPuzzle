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

private:

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseWheel( wxMouseEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseRightDown( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );
	void OnMouseCaptureLost( wxMouseCaptureLostEvent& event );

	void BindContext( void );
	void Render( GLenum renderMode, wxPoint* mousePos = nullptr, int* objectHandle = nullptr );

	wxGLContext* context;
	GLRenderer* renderer;
	_3DMath::AffineTransform transform;
	double eyeDistance;
	wxPoint mouseDragLastPos;
	bool mouseDragging;
	int selectedObjectHandle;
	_3DMath::TimeKeeper timeKeeper;
};

// Canvas.h
