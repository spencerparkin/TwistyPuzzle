// Canvas.h

#pragma once

#include <wx/glcanvas.h>
#include <Vector.h>
#include <AffineTransform.h>

class GLRenderer;

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

private:

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );
	void OnMouseCaptureLost( wxMouseCaptureLostEvent& event );

	void BindContext( void );

	wxGLContext* context;
	GLRenderer* renderer;
	_3DMath::AffineTransform transform;
	double eyeDistance;
	wxPoint mouseDragLastPos;
	bool mouseDragging;
};

// Canvas.h
