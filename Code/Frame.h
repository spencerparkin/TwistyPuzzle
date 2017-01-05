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
		ID_Documentation,
		ID_About,
		ID_DrawWireFrame,
		ID_DrawSolid,
		ID_Scramble,
		ID_Solve,
		ID_Save,
		ID_Load,
		ID_Puzzle,		// This needs to be the last ID.
	};

	void OnExit( wxCommandEvent& event );
	void OnTimer( wxTimerEvent& event );
	void OnDrawWireFrame( wxCommandEvent& event );
	void OnDrawSolid( wxCommandEvent& event );
	void OnPuzzleType( wxCommandEvent& event );
	void OnUpdateUI( wxUpdateUIEvent& event );
	void OnAbout( wxCommandEvent& event );
	void OnScramble( wxCommandEvent& event );
	void OnSolve( wxCommandEvent& event );
	void OnSave( wxCommandEvent& event );
	void OnLoad( wxCommandEvent& event );
	void OnDocumentation( wxCommandEvent& event );

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
