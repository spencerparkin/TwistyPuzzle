// Canvas.h

#pragma once

#include <wx/glcanvas.h>

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

private:

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );

	void BindContext( void );

	wxGLContext* context;
};

// Canvas.h
