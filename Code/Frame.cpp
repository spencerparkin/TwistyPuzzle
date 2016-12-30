// Frame.cpp

#include "Frame.h"
#include "Canvas.h"
#include "Application.h"
#include "TwistyPuzzle.h"
#include <wx/sizer.h>
#include <wx/menu.h>

Frame::Frame( void ) : wxFrame( nullptr, wxID_ANY, "Twisty Puzzle", wxDefaultPosition, wxSize( 700, 700 ) ), timer( this, ID_Timer )
{
	wxMenu* programMenu = new wxMenu();
	wxMenuItem* exitMenuItem = new wxMenuItem( programMenu, ID_Exit, "Exit", "Exit this program." );
	programMenu->Append( exitMenuItem );

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( programMenu, "Program" );
	SetMenuBar( menuBar );

	wxStatusBar* statusBar = new wxStatusBar( this );
	SetStatusBar( statusBar );

	canvas = new Canvas( this );

	wxBoxSizer* boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( canvas, 1, wxGROW );
	SetSizer( boxSizer );

	Bind( wxEVT_MENU, &Frame::OnExit, this, ID_Exit );
	Bind( wxEVT_TIMER, &Frame::OnTimer, this, ID_Timer );

	timer.Start(0);
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnExit( wxCommandEvent& event )
{
	Close( true );
}

void Frame::OnTimer( wxTimerEvent& event )
{
	canvas->Animate();
}

// Frame.cpp