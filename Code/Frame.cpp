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

	wxMenu* puzzleMenu = CreatePuzzleMenu();

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( programMenu, "Program" );
	menuBar->Append( puzzleMenu, "Puzzle" );
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

wxMenu* Frame::CreatePuzzleMenu( void )
{
	wxMenu* puzzleMenu = new wxMenu();
	int itemId = ID_Puzzle;

	const wxClassInfo* baseClassInfo = wxClassInfo::FindClass( "TwistyPuzzle" );

	const wxClassInfo* classInfo = wxClassInfo::GetFirst();
	while( classInfo )
	{
		if( classInfo != baseClassInfo && classInfo->IsKindOf( baseClassInfo ) )
		{
			wxString className = classInfo->GetClassName();
			wxMenuItem* puzzleMenuItem = new wxMenuItem( puzzleMenu, itemId, className, "Create a twisty puzzle of type \"" + className + "\".", wxITEM_CHECK );
			puzzleMenu->Append( puzzleMenuItem );

			Bind( wxEVT_MENU, &Frame::OnPuzzleType, this, itemId, -1, new PuzzleMenuItemUserData( classInfo ) );
			Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, itemId, -1, new PuzzleMenuItemUserData( classInfo ) );

			itemId++;
		}

		classInfo = classInfo->GetNext();
	}

	return puzzleMenu;
}

void Frame::OnPuzzleType( wxCommandEvent& event )
{
	PuzzleMenuItemUserData* userData = ( PuzzleMenuItemUserData* )event.GetEventUserData();

	TwistyPuzzle* puzzle = ( TwistyPuzzle* )userData->classInfo->CreateObject();
	puzzle->Reset();
	wxGetApp().SetPuzzle( puzzle );
	wxGetApp().GetFrame()->GetCanvas()->Refresh();
}

void Frame::OnUpdateUI( wxUpdateUIEvent& event )
{
	if( event.GetId() >= ID_Puzzle )
	{
		PuzzleMenuItemUserData* userData = ( PuzzleMenuItemUserData* )event.GetEventUserData();

		if( wxGetApp().GetPuzzle()->IsKindOf( userData->classInfo ) )
			event.Check( true );
		else
			event.Check( false );
	}
}

Frame::PuzzleMenuItemUserData::PuzzleMenuItemUserData( const wxClassInfo* classInfo )
{
	this->classInfo = classInfo;
}

/*virtual*/ Frame::PuzzleMenuItemUserData::~PuzzleMenuItemUserData( void )
{
}

// Frame.cpp