// Frame.h

#pragma once

#include <wx/frame.h>

class Canvas;

class Frame : public wxFrame
{
public:

	Frame( void );
	virtual ~Frame( void );

private:

	enum
	{
		ID_Exit = wxID_HIGHEST,
	};

	void OnExit( wxCommandEvent& event );

	Canvas* canvas;
};

// Frame.h
