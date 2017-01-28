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
#include <wx/textctrl.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

Frame::Frame( void ) : wxFrame( nullptr, wxID_ANY, "Twisty Puzzle", wxDefaultPosition, wxSize( 700, 700 ) ), timer( this, ID_Timer )
{
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

	wxMenu* interfaceMenu = new wxMenu();
	wxMenuItem* selectAxisMenuItem = new wxMenuItem( interfaceMenu, ID_ManualSelectAxis, "Manual Select Axis", "Manually select the axis to rotate about with the mouse wheel.", wxITEM_CHECK );
	wxMenuItem* nearestAxisMenuItem = new wxMenuItem( interfaceMenu, ID_AutoSelectAxis, "Auto Select Axis", "Auto-select the axis to rotate about with the mouse wheel.", wxITEM_CHECK );
	interfaceMenu->Append( selectAxisMenuItem );
	interfaceMenu->Append( nearestAxisMenuItem );

	wxMenu* renderMenu = new wxMenu();
	wxMenuItem* drawWireFrameMenuItem = new wxMenuItem( renderMenu, ID_DrawWireFrame, "Draw Wire-Frame", "Draw the twisty frame as a bunch of line segments.", wxITEM_CHECK );
	wxMenuItem* drawSolidMenuItem = new wxMenuItem( renderMenu, ID_DrawSolid, "Draw Solid", "Draw the twisty puzzle as a bunch of solid triangles.", wxITEM_CHECK );
	wxMenuItem* drawBordersMenuItem = new wxMenuItem( renderMenu, ID_DrawBorders, "Draw Borders", "Draw a crappy border around faces.", wxITEM_CHECK );
	wxMenuItem* drawAxisLabelsMenuItem = new wxMenuItem( renderMenu, ID_DrawAxisLabels, "Draw Axis Labels", "Draw the names of each axis.  These are used in the command sequence text control.", wxITEM_CHECK );
	wxMenuItem* drawStatsMenuItem = new wxMenuItem( renderMenu, ID_DrawStats, "Draw Stats", "Draw some statistics about the puzzle and its rendering.", wxITEM_CHECK );
	renderMenu->Append( drawWireFrameMenuItem );
	renderMenu->Append( drawSolidMenuItem );
	renderMenu->Append( drawBordersMenuItem );
	renderMenu->AppendSeparator();
	renderMenu->Append( drawAxisLabelsMenuItem );
	renderMenu->Append( drawStatsMenuItem );

	wxMenu* historyMenu = new wxMenu();
	wxMenuItem* goForwardMenuItem = new wxMenuItem( historyMenu, ID_GoForward, "Go Forward\tF6", "Go forward in your rotation history." );
	wxMenuItem* goBackwardMenuItem = new wxMenuItem( historyMenu, ID_GoBackward, "Go Backward\tF5", "Go backward in your rotation history." );
	historyMenu->Append( goForwardMenuItem );
	historyMenu->Append( goBackwardMenuItem );

	wxMenu* helpMenu = new wxMenu();
	wxMenuItem* documentationMenuItem = new wxMenuItem( helpMenu, ID_Documentation, "Documentation\tF1", "Bring up a window with documentation for this program." );
	wxMenuItem* aboutMenuItem = new wxMenuItem( helpMenu, ID_About, "About", "Show the about box." );
	helpMenu->Append( documentationMenuItem );
	helpMenu->AppendSeparator();
	helpMenu->Append( aboutMenuItem );

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( programMenu, "Program" );
	menuBar->Append( puzzleMenu, "Puzzle" );
	menuBar->Append( interfaceMenu, "Interface" );
	menuBar->Append( renderMenu, "Render" );
	menuBar->Append( historyMenu, "History" );
	menuBar->Append( helpMenu, "Help" );
	SetMenuBar( menuBar );

	wxStatusBar* statusBar = new wxStatusBar( this );
	SetStatusBar( statusBar );

	canvas = new Canvas( this );

	textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_LEFT );

	wxBoxSizer* boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( canvas, 1, wxGROW );
	boxSizer->Add( textCtrl, 0, wxALL | wxGROW, 0 );
	SetSizer( boxSizer );

	wxAcceleratorEntry acceleratorEntries[3];
	acceleratorEntries[0].Set( wxACCEL_NORMAL, WXK_F5, ID_GoBackward );
	acceleratorEntries[1].Set( wxACCEL_NORMAL, WXK_F6, ID_GoForward );
	acceleratorEntries[2].Set( wxACCEL_NORMAL, WXK_F1, ID_Documentation );

	wxAcceleratorTable acceleratorTable( sizeof( acceleratorEntries ) / sizeof( wxAcceleratorEntry ), acceleratorEntries );
	SetAcceleratorTable( acceleratorTable );

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
	Bind( wxEVT_MENU, &Frame::OnManualSelectAxis, this, ID_ManualSelectAxis );
	Bind( wxEVT_MENU, &Frame::OnAutoSelectAxis, this, ID_AutoSelectAxis );
	Bind( wxEVT_MENU, &Frame::OnDrawAxisLabels, this, ID_DrawAxisLabels );
	Bind( wxEVT_MENU, &Frame::OnDrawStats, this, ID_DrawStats );
	Bind( wxEVT_MENU, &Frame::OnDrawBorders, this, ID_DrawBorders );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawWireFrame );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawSolid );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_Solve );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoForward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoBackward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_ManualSelectAxis );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_AutoSelectAxis );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawAxisLabels );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawStats );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawBorders );
	Bind( wxEVT_COMMAND_TEXT_ENTER, &Frame::OnTextCtrlEnter, this );

	timer.Start(1);
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnDrawAxisLabels( wxCommandEvent& event )
{
	canvas->SetRenderAxisLabels( !canvas->GetRenderAxisLabels() );
}

void Frame::OnDrawStats( wxCommandEvent& event )
{
	canvas->SetRenderStats( !canvas->GetRenderStats() );
}

void Frame::OnTextCtrlEnter( wxCommandEvent& event )
{
	std::string rotationSequence = ( const char* )textCtrl->GetValue().c_str();

	boost::char_separator< char > separator( " ", "," );
	typedef boost::tokenizer< boost::char_separator< char > > Tokenizer;
	Tokenizer tokenizer( rotationSequence, separator );

	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

	struct Element
	{
		TwistyPuzzle::CutShape* cutShape;
		bool inverse;
	};

	std::list< Element > elementList;

	for( Tokenizer::iterator iter = tokenizer.begin(); iter != tokenizer.end(); iter++ )
	{
		std::string token = *iter;
		if( token == "," )
			continue;

		wxString label( token.c_str() );

		Element element;
		element.inverse = false;
		
		char lastChar = label.GetChar( label.Length() - 1 );
		if( lastChar == 'i' )
		{
			label.Truncate( label.Length() - 1 );
			element.inverse = true;
		}

		element.cutShape = puzzle->FindCutShapeWithLabel( label );
		if( element.cutShape )
			elementList.push_back( element );
		else
		{
			wxMessageBox( "Failed to find cut-shape with label: " + label, "Error", wxICON_ERROR | wxCENTRE, this );
			return;
		}
	}

	std::list< Element >::iterator iter = elementList.begin();
	while( iter != elementList.end() )
	{
		Element& element = *iter;

		TwistyPuzzle::Rotation::Direction rotDir = TwistyPuzzle::Rotation::DIR_CW;
		if( element.inverse )
			rotDir = TwistyPuzzle::Rotation::DIR_CCW;

		TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation( element.cutShape->GetHandle(), rotDir );
		puzzle->EnqueueRotation( rotation );

		iter++;
	}
}

void Frame::OnGoForward( wxCommandEvent& event )
{
	wxGetApp().GetPuzzle()->GoForward();
}

void Frame::OnGoBackward( wxCommandEvent& event )
{
	wxGetApp().GetPuzzle()->GoBackward();
}

void Frame::OnManualSelectAxis( wxCommandEvent& event )
{
	canvas->axisSelectMode = Canvas::AXIS_SELECT_MANUAL;
}

void Frame::OnAutoSelectAxis( wxCommandEvent& event )
{
	canvas->axisSelectMode = Canvas::AXIS_SELECT_AUTO;
}

void Frame::OnScramble( wxCommandEvent& event )
{
	timer.Stop();

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

	timer.Start(1);
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
		wxFileName fileName( file );
		fileName.SetExt( "xml" );	// This must be done on Linux and won't hurt other platforms.
		file = fileName.GetFullPath();

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
}

void Frame::OnDrawSolid( wxCommandEvent& event )
{
	canvas->GetRenderer()->drawStyle = _3DMath::Renderer::DRAW_STYLE_SOLID;
}

void Frame::OnDrawBorders( wxCommandEvent& event )
{
	canvas->SetRenderBorders( !canvas->GetRenderBorders() );
}

void Frame::OnExit( wxCommandEvent& event )
{
	timer.Stop();

	Close( true );
}

void Frame::OnTimer( wxTimerEvent& event )
{
	canvas->Refresh();
}

wxMenu* Frame::CreatePuzzleMenu( void )
{
	wxMenu* puzzleMenu = new wxMenu();
	int itemId = ID_Puzzle;

	const wxClassInfo* baseClassInfo = wxClassInfo::FindClass( "TwistyPuzzle" );

	wxArrayString classNameArray;
	
	const wxClassInfo* classInfo = wxClassInfo::GetFirst();
	while( classInfo )
	{
		if( classInfo != baseClassInfo && classInfo->IsKindOf( baseClassInfo ) && classInfo->IsDynamic() )
		{
			wxString className = classInfo->GetClassName();
			classNameArray.push_back( className );
		}

		classInfo = classInfo->GetNext();
	}

	classNameArray.Sort();

	for( int i = 0; i < ( signed )classNameArray.size(); i++ )
	{
		wxString className = classNameArray[i];
		const wxClassInfo* classInfo = wxClassInfo::FindClass( className );
		wxASSERT( classInfo != nullptr );

		wxMenuItem* puzzleMenuItem = new wxMenuItem( puzzleMenu, itemId, className, "Create a twisty puzzle of type \"" + className + "\".", wxITEM_CHECK );
		puzzleMenu->Append( puzzleMenuItem );

		Bind( wxEVT_MENU, &Frame::OnPuzzleType, this, itemId, -1, new PuzzleMenuItemUserData( classInfo ) );
		Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, itemId, -1, new PuzzleMenuItemUserData( classInfo ) );

		itemId++;
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
			case ID_ManualSelectAxis:
			{
				event.Check( canvas->axisSelectMode == Canvas::AXIS_SELECT_MANUAL );
				break;
			}
			case ID_AutoSelectAxis:
			{
				event.Check( canvas->axisSelectMode == Canvas::AXIS_SELECT_AUTO );
				break;
			}
			case ID_DrawAxisLabels:
			{
				event.Check( canvas->GetRenderAxisLabels() );
				break;
			}
			case ID_DrawStats:
			{
				event.Check( canvas->GetRenderStats() );
				break;
			}
			case ID_DrawBorders:
			{
				event.Check( canvas->GetRenderBorders() );
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