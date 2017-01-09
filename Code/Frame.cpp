// Frame.cpp

#include "Frame.h"
#include "Canvas.h"
#include "Application.h"
#include "TwistyPuzzle.h"
#include "GLRenderer.h"
#include "HtmlFrame.h"
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aboutdlg.h>
#include <wx/numdlg.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

// TODO: Add rotatoin axis labeling and text sequence interface.

Frame::Frame( void ) : wxFrame( nullptr, wxID_ANY, "Twisty Puzzle", wxDefaultPosition, wxSize( 700, 700 ) ), timer( this, ID_Timer )
{
	// TODO: Add accelerators to the menu items.

	wxMenu* programMenu = new wxMenu();
	wxMenuItem* exitMenuItem = new wxMenuItem( programMenu, ID_Exit, "Exit", "Exit this program." );
	wxMenuItem* scrambleMenuItem = new wxMenuItem( programMenu, ID_Scramble, "Scramble", "Scramble the twisty puzzle." );
	wxMenuItem* solveMenuItem = new wxMenuItem( programMenu, ID_Solve, "Solve", "Solve the twisty puzzle." );
	wxMenuItem* saveMenuItem = new wxMenuItem( programMenu, ID_Save, "Save", "Save the twisty puzzle to file." );
	wxMenuItem* loadMenuItem = new wxMenuItem( programMenu, ID_Load, "Load", "Load a twisty puzzle from file." );
	programMenu->Append( saveMenuItem );
	programMenu->Append( loadMenuItem );
	programMenu->AppendSeparator();
	programMenu->Append( scrambleMenuItem );
	programMenu->Append( solveMenuItem );
	programMenu->AppendSeparator();
	programMenu->Append( exitMenuItem );

	wxMenu* puzzleMenu = CreatePuzzleMenu();

	wxMenu* renderMenu = new wxMenu();
	wxMenuItem* drawWireFrameMenuItem = new wxMenuItem( renderMenu, ID_DrawWireFrame, "Draw Wire-Frame", "Draw the twisty frame as a bunch of line segments.", wxITEM_CHECK );
	wxMenuItem* drawSolidMenuItem = new wxMenuItem( renderMenu, ID_DrawSolid, "Draw Solid", "Draw the twisty puzzle as a bunch of solid triangles.", wxITEM_CHECK );
	renderMenu->Append( drawWireFrameMenuItem );
	renderMenu->Append( drawSolidMenuItem );

	wxMenu* historyMenu = new wxMenu();
	wxMenuItem* goForwardMenuItem = new wxMenuItem( historyMenu, ID_GoForward, "Go Forward", "Go forward in your rotation history." );
	wxMenuItem* goBackwardMenuItem = new wxMenuItem( historyMenu, ID_GoBackward, "Go Backward", "Go backward in your rotation history." );
	historyMenu->Append( goForwardMenuItem );
	historyMenu->Append( goBackwardMenuItem );

	wxMenu* helpMenu = new wxMenu();
	wxMenuItem* documentationMenuItem = new wxMenuItem( helpMenu, ID_Documentation, "Documentation", "Bring up a window with documentation for this program." );
	wxMenuItem* aboutMenuItem = new wxMenuItem( helpMenu, ID_About, "About", "Show the about box." );
	helpMenu->Append( documentationMenuItem );
	helpMenu->AppendSeparator();
	helpMenu->Append( aboutMenuItem );

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( programMenu, "Program" );
	menuBar->Append( puzzleMenu, "Puzzle" );
	menuBar->Append( renderMenu, "Render" );
	menuBar->Append( historyMenu, "History" );
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
	Bind( wxEVT_MENU, &Frame::OnDocumentation, this, ID_Documentation );
	Bind( wxEVT_MENU, &Frame::OnAbout, this, ID_About );
	Bind( wxEVT_MENU, &Frame::OnScramble, this, ID_Scramble );
	Bind( wxEVT_MENU, &Frame::OnSolve, this, ID_Solve );
	Bind( wxEVT_MENU, &Frame::OnSave, this, ID_Save );
	Bind( wxEVT_MENU, &Frame::OnLoad, this, ID_Load );
	Bind( wxEVT_MENU, &Frame::OnGoForward, this, ID_GoForward );
	Bind( wxEVT_MENU, &Frame::OnGoBackward, this, ID_GoBackward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawWireFrame );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawSolid );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_Solve );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoForward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoBackward );

	timer.Start(0);
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnGoForward( wxCommandEvent& event )
{
	wxGetApp().GetPuzzle()->GoForward();
}

void Frame::OnGoBackward( wxCommandEvent& event )
{
	wxGetApp().GetPuzzle()->GoBackward();
}

void Frame::OnScramble( wxCommandEvent& event )
{
	int rotationCount = ( int )wxGetNumberFromUser( "Scramble with how many rotations?", "Scrambles:", "Scramble", 50, 1, 500, wxGetApp().GetFrame() );

	_3DMath::Random random;

	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();
	
	TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation(0);
	rotation->newRotationSpeedCoeficient = 20.0;
	puzzle->EnqueueRotation( rotation );

	puzzle->EnqueueRandomRotations( random, rotationCount );

	rotation = new TwistyPuzzle::Rotation(0);
	rotation->newRotationSpeedCoeficient = 10.0;
	puzzle->EnqueueRotation( rotation );
}

void Frame::OnSolve( wxCommandEvent& event )
{
}

bool Frame::Save( void )
{
	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

	wxFileDialog fileDialog( this, "Save puzzle to file.", wxEmptyString, wxEmptyString, "XML file (*.xml)|*.xml", wxFD_SAVE );
	if( fileDialog.ShowModal() == wxID_OK )
	{
		wxString file = fileDialog.GetPath();
		if( !puzzle->Save( file ) )
		{
			wxMessageBox( "Failed to save.", "Error", wxCENTRE | wxICON_ERROR, this );
			return false;
		}
	}

	return true;
}

bool Frame::Load( void )
{
	wxFileDialog fileDialog( this, "Load puzzle from file.", wxEmptyString, wxEmptyString, "XML file (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
	if( fileDialog.ShowModal() == wxID_OK )
	{
		wxString file = fileDialog.GetPath();
		TwistyPuzzle* puzzle = TwistyPuzzle::AllocateUsingFile( file );
		if( puzzle->Load( file ) )
			wxGetApp().SetPuzzle( puzzle );
		else
		{
			delete puzzle;
			wxMessageBox( "Failed to load.", "Error", wxCENTRE | wxICON_ERROR, this );
			return false;
		}
	}

	wxGetApp().GetFrame()->GetCanvas()->Refresh();
	return true;
}

void Frame::OnSave( wxCommandEvent& event )
{
	Save();
}

void Frame::OnLoad( wxCommandEvent& event )
{
	if( SaveProtect() )
		Load();
}

bool Frame::SaveProtect( void )
{
	TwistyPuzzle* twistyPuzzle = wxGetApp().GetPuzzle();
	if( twistyPuzzle->needsSaving )
	{
		int response = wxMessageBox( "Would you like to save your current puzzle before continuing?", "Unsaved Puzzle", wxCENTRE | wxICON_QUESTION | wxYES_NO | wxCANCEL, this );
		if( response == wxCANCEL || ( response == wxYES && !Save() ) )
			return false;
	}

	return true;
}

void Frame::OnDocumentation( wxCommandEvent& event )
{
	HtmlFrame* htmlFrame = new HtmlFrame( nullptr, wxEmptyString );
	htmlFrame->Show( true );
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
		if( classInfo != baseClassInfo && classInfo->IsKindOf( baseClassInfo ) && classInfo->IsDynamic() )
		{
			wxString className = classInfo->GetClassName();

			// TODO: Sort this by class name.

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
	if( SaveProtect() )
	{
		PuzzleMenuItemUserData* userData = ( PuzzleMenuItemUserData* )event.GetEventUserData();

		TwistyPuzzle* puzzle = ( TwistyPuzzle* )userData->classInfo->CreateObject();
		puzzle->Reset();
		wxGetApp().SetPuzzle( puzzle );
		wxGetApp().GetFrame()->GetCanvas()->Refresh();
	}
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
			case ID_Solve:
			{
				event.Enable( wxGetApp().GetPuzzle()->SolveSupported() ? true : false );
				break;
			}
			case ID_GoForward:
			{
				event.Enable( wxGetApp().GetPuzzle()->CanGoForward() ? true : false );
				break;
			}
			case ID_GoBackward:
			{
				event.Enable( wxGetApp().GetPuzzle()->CanGoBackward() ? true : false );
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