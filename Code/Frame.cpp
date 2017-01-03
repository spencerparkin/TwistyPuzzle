// Frame.cpp

#include "Frame.h"
#include "Canvas.h"
#include "Application.h"
#include "TwistyPuzzle.h"
#include "GLRenderer.h"
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aboutdlg.h>

Frame::Frame( void ) : wxFrame( nullptr, wxID_ANY, "Twisty Puzzle", wxDefaultPosition, wxSize( 700, 700 ) ), timer( this, ID_Timer )
{
	wxMenu* programMenu = new wxMenu();
	wxMenuItem* exitMenuItem = new wxMenuItem( programMenu, ID_Exit, "Exit", "Exit this program." );
	programMenu->Append( exitMenuItem );

	wxMenu* puzzleMenu = CreatePuzzleMenu();

	wxMenu* renderMenu = new wxMenu();
	wxMenuItem* drawWireFrameMenuItem = new wxMenuItem( renderMenu, ID_DrawWireFrame, "Draw Wire-Frame", "Draw the twisty frame as a bunch of line segments.", wxITEM_CHECK );
	wxMenuItem* drawSolidMenuItem = new wxMenuItem( renderMenu, ID_DrawSolid, "Draw Solid", "Draw the twisty puzzle as a bunch of solid triangles.", wxITEM_CHECK );
	renderMenu->Append( drawWireFrameMenuItem );
	renderMenu->Append( drawSolidMenuItem );

	wxMenu* helpMenu = new wxMenu();
	wxMenuItem* aboutMenuItem = new wxMenuItem( helpMenu, ID_About, "About", "Show the about box." );
	helpMenu->Append( aboutMenuItem );

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( programMenu, "Program" );
	menuBar->Append( puzzleMenu, "Puzzle" );
	menuBar->Append( renderMenu, "Render" );
	menuBar->Append( helpMenu, "Help" );
	SetMenuBar( menuBar );

	wxStatusBar* statusBar = new wxStatusBar( this );
	SetStatusBar( statusBar );

	canvas = new Canvas( this );

	wxBoxSizer* boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( canvas, 1, wxGROW );
	SetSizer( boxSizer );

	Bind( wxEVT_MENU, &Frame::OnExit, this, ID_Exit );
	Bind( wxEVT_TIMER, &Frame::OnTimer, this, ID_Timer );
	Bind( wxEVT_MENU, &Frame::OnDrawWireFrame, this, ID_DrawWireFrame );
	Bind( wxEVT_MENU, &Frame::OnDrawSolid, this, ID_DrawSolid );
	Bind( wxEVT_MENU, &Frame::OnAbout, this, ID_About );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawWireFrame );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawSolid );

	timer.Start(0);
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnAbout( wxCommandEvent& event )
{
	wxAboutDialogInfo aboutDialogInfo;

	aboutDialogInfo.SetName( "Twisty Puzzle" );
	aboutDialogInfo.SetVersion( "1.0" );
	aboutDialogInfo.SetDescription( "This program is distributed under the MIT license." );
	aboutDialogInfo.SetCopyright( "Copyright (C) 2017 Spencer T. Parkin (spencertparkin@gmail.com)" );
	aboutDialogInfo.SetWebSite( "https://github.com/spencerparkin/TwistyPuzzle" );

	wxAboutBox( aboutDialogInfo );
}

void Frame::OnDrawWireFrame( wxCommandEvent& event )
{
	canvas->GetRenderer()->drawStyle = _3DMath::Renderer::DRAW_STYLE_WIRE_FRAME;
	canvas->Refresh();
}

void Frame::OnDrawSolid( wxCommandEvent& event )
{
	canvas->GetRenderer()->drawStyle = _3DMath::Renderer::DRAW_STYLE_SOLID;
	canvas->Refresh();
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
	else
	{
		switch( event.GetId() )
		{
			case ID_DrawWireFrame:
			{
				event.Check( canvas->GetRenderer()->drawStyle == _3DMath::Renderer::DRAW_STYLE_WIRE_FRAME ? true : false );
				break;
			}
			case ID_DrawSolid:
			{
				event.Check( canvas->GetRenderer()->drawStyle == _3DMath::Renderer::DRAW_STYLE_SOLID ? true : false );
				break;
			}
		}
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