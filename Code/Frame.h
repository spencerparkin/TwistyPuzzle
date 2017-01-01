// Frame.h

#pragma once

#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>

class Canvas;

class Frame : public wxFrame
{
public:

	Frame( void );
	virtual ~Frame( void );

	Canvas* GetCanvas( void ) { return canvas; }

private:

	enum
	{
		ID_Exit = wxID_HIGHEST,
		ID_Timer,
		ID_Puzzle,
	};

	void OnExit( wxCommandEvent& event );
	void OnTimer( wxTimerEvent& event );
	void OnPuzzleType( wxCommandEvent& event );
	void OnUpdateUI( wxUpdateUIEvent& event );

	class PuzzleMenuItemUserData : public wxObject
	{
	public:
		PuzzleMenuItemUserData( const wxClassInfo* classInfo );
		virtual ~PuzzleMenuItemUserData( void );
		const wxClassInfo* classInfo;
	};

	wxMenu* CreatePuzzleMenu( void );

	Canvas* canvas;

	wxTimer timer;
};

// Frame.h
