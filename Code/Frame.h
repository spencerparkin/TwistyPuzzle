// Frame.h

#pragma once

#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/slider.h>

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
		ID_DrawAxes,
		ID_DrawAxisLabels,
		ID_DrawStats,
		ID_DrawBorders,
		ID_DrawDiff,
		ID_Scramble,
		ID_Solve,
		ID_Save,
		ID_Load,
		ID_GoForward,
		ID_GoBackward,
		ID_ManualSelectAxis,
		ID_AutoSelectAxis,
		ID_TakeSnapshot,
		ID_FoviSlider,
		ID_SequenceText,
		ID_LockLabels,
		ID_Puzzle,		// This needs to be the last ID.
	};

	void OnExit( wxCommandEvent& event );
	void OnTimer( wxTimerEvent& event );
	void OnPuzzleType( wxCommandEvent& event );
	void OnUpdateUI( wxUpdateUIEvent& event );
	void OnAbout( wxCommandEvent& event );
	void OnScramble( wxCommandEvent& event );
	void OnSolve( wxCommandEvent& event );
	void OnSave( wxCommandEvent& event );
	void OnLoad( wxCommandEvent& event );
	void OnDocumentation( wxCommandEvent& event );
	void OnGoForward( wxCommandEvent& event );
	void OnGoBackward( wxCommandEvent& event );
	void OnManualSelectAxis( wxCommandEvent& event );
	void OnAutoSelectAxis( wxCommandEvent& event );
	void OnTextCtrlEnter( wxCommandEvent& event );
	void OnDrawAxes( wxCommandEvent& event );
	void OnDrawAxisLabels( wxCommandEvent& event );
	void OnDrawStats( wxCommandEvent& event );
	void OnDrawBorders( wxCommandEvent& event );
	void OnDrawDiff( wxCommandEvent& event );
	void OnTakeSnapshot( wxCommandEvent& event );
	void OnFoviSlider( wxCommandEvent& event );
	void OnLockLabels( wxCommandEvent& event );

	class PuzzleMenuItemUserData : public wxObject
	{
	public:
		PuzzleMenuItemUserData( const wxClassInfo* classInfo );
		virtual ~PuzzleMenuItemUserData( void );
		const wxClassInfo* classInfo;
	};

	wxMenu* CreatePuzzleMenu( void );
	bool SaveProtect( void );
	bool Save( void );
	bool Load( void );

	Canvas* canvas;
	wxTextCtrl* textCtrl;
	wxSlider* sliderCtrl;
	wxTimer timer;
};

// Frame.h
