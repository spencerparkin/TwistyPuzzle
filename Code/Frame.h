// Frame.h

#pragma once

#include <wx/frame.h>
#include <wx/timer.h>

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
		ID_Timer,
	};

	void OnExit( wxCommandEvent& event );
	void OnTimer( wxTimerEvent& event );

	Canvas* canvas;

	wxTimer timer;
};

// Frame.h
