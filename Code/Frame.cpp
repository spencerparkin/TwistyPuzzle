// Frame.cpp

#include "TwistyPuzzle.h"
#include "Frame.h"
#include "Canvas.h"
#include "Application.h"
#include "GLRenderer.h"
#include "HtmlFrame.h"
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aboutdlg.h>
#include <wx/numdlg.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <ListFunctions.h>

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
	wxMenuItem* lockLabelsMenuItem = new wxMenuItem( interfaceMenu, ID_LockLabels, "Lock Labels\tF4", "Toggle dynamic label assignment.", wxITEM_CHECK );
	wxMenuItem* takeSnapshotMenuItem = new wxMenuItem( interfaceMenu, ID_TakeSnapshot, "Take Snap-shot", "Take a snap-shot of the puzzle faces for diff-ing later." );
	interfaceMenu->Append( selectAxisMenuItem );
	interfaceMenu->Append( nearestAxisMenuItem );
	interfaceMenu->AppendSeparator();
	interfaceMenu->Append( lockLabelsMenuItem );
	interfaceMenu->AppendSeparator();
	interfaceMenu->Append( takeSnapshotMenuItem );

	wxMenu* renderMenu = new wxMenu();
	wxMenuItem* drawBordersMenuItem = new wxMenuItem( renderMenu, ID_DrawBorders, "Draw Borders", "Draw a crappy border around faces.", wxITEM_CHECK );
	wxMenuItem* drawAxesMenuItem = new wxMenuItem( renderMenu, ID_DrawAxes, "Draw Axes", "Draw the rotation axes of the puzzle.", wxITEM_CHECK );
	wxMenuItem* drawAxisLabelsMenuItem = new wxMenuItem( renderMenu, ID_DrawAxisLabels, "Draw Axis Labels", "Draw the names of each axis.  These are used in the command sequence text control.", wxITEM_CHECK );
	wxMenuItem* drawStatsMenuItem = new wxMenuItem( renderMenu, ID_DrawStats, "Draw Stats", "Draw some statistics about the puzzle and its rendering.", wxITEM_CHECK );
	wxMenuItem* drawDiffMenuItem = new wxMenuItem( renderMenu, ID_DrawDiff, "Draw Diff", "If you've taken a snap-shot, show the difference between the current state of the puzzle and the stored snap-shot.", wxITEM_CHECK );
	renderMenu->Append( drawBordersMenuItem );
	renderMenu->Append( drawAxesMenuItem );
	renderMenu->Append( drawAxisLabelsMenuItem );
	renderMenu->Append( drawStatsMenuItem );
	renderMenu->Append( drawDiffMenuItem );

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

	wxPanel* controlPanel = new wxPanel( this, wxID_ANY );

	textCtrl = new wxTextCtrl( controlPanel, ID_SequenceText, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_LEFT );
	sliderCtrl = new wxSlider( controlPanel, ID_FoviSlider, ( int )canvas->GetFoviAngleDegrees(), 20, 100, wxDefaultPosition, wxSize( 100, -1 ) );

	wxBoxSizer* horizBoxSizer = new wxBoxSizer( wxHORIZONTAL );
	horizBoxSizer->Add( textCtrl, 1, wxGROW );
	horizBoxSizer->Add( sliderCtrl, 0 );
	controlPanel->SetSizer( horizBoxSizer );

	wxBoxSizer* vertBoxSizer = new wxBoxSizer( wxVERTICAL );
	vertBoxSizer->Add( canvas, 1, wxGROW );
	vertBoxSizer->Add( controlPanel, 0, wxGROW );
	SetSizer( vertBoxSizer );

	wxAcceleratorEntry acceleratorEntries[4];
	acceleratorEntries[0].Set( wxACCEL_NORMAL, WXK_F5, ID_GoBackward );
	acceleratorEntries[1].Set( wxACCEL_NORMAL, WXK_F6, ID_GoForward );
	acceleratorEntries[2].Set( wxACCEL_NORMAL, WXK_F1, ID_Documentation );
	acceleratorEntries[3].Set( wxACCEL_NORMAL, WXK_F4, ID_LockLabels );

	wxAcceleratorTable acceleratorTable( sizeof( acceleratorEntries ) / sizeof( wxAcceleratorEntry ), acceleratorEntries );
	SetAcceleratorTable( acceleratorTable );

	Bind( wxEVT_MENU, &Frame::OnExit, this, ID_Exit );
	Bind( wxEVT_TIMER, &Frame::OnTimer, this, ID_Timer );
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
	Bind( wxEVT_MENU, &Frame::OnDrawAxes, this, ID_DrawAxes );
	Bind( wxEVT_MENU, &Frame::OnDrawAxisLabels, this, ID_DrawAxisLabels );
	Bind( wxEVT_MENU, &Frame::OnDrawStats, this, ID_DrawStats );
	Bind( wxEVT_MENU, &Frame::OnDrawBorders, this, ID_DrawBorders );
	Bind( wxEVT_MENU, &Frame::OnDrawDiff, this, ID_DrawDiff );
	Bind( wxEVT_MENU, &Frame::OnTakeSnapshot, this, ID_TakeSnapshot );
	Bind( wxEVT_MENU, &Frame::OnLockLabels, this, ID_LockLabels );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_Solve );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoForward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_GoBackward );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_ManualSelectAxis );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_AutoSelectAxis );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawAxes );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawAxisLabels );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawStats );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawBorders );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_DrawDiff );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_LockLabels );
	Bind( wxEVT_COMMAND_TEXT_ENTER, &Frame::OnTextCtrlEnter, this, ID_SequenceText );
	Bind( wxEVT_SLIDER, &Frame::OnFoviSlider, this, ID_FoviSlider );

	timer.Start(1);
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnLockLabels( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_DYNAMIC_LABELS;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnFoviSlider( wxCommandEvent& event )
{
	double angleDegrees = ( double )sliderCtrl->GetValue();
	canvas->SetFoviAngleDegrees( angleDegrees );
}

void Frame::OnDrawAxes( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_AXES;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnDrawAxisLabels( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_AXIS_LABELS;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnDrawStats( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_STATS;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnDrawBorders( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_BORDERS;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnDrawDiff( wxCommandEvent& event )
{
	int renderFlags = canvas->GetRenderFlags();
	renderFlags ^= Canvas::RENDER_DIFF;
	canvas->SetRenderFlags( renderFlags );
}

void Frame::OnTakeSnapshot( wxCommandEvent& event )
{
	wxGetApp().GetPuzzle()->TakeSnapshot();
	wxMessageBox( "Snap-shot taken!", "Snapshot", wxICON_INFORMATION, this );
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
		bool special;
		bool alternate;
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
		element.special = false;
		element.alternate = false;
		
		char lastChar = label.GetChar( label.Length() - 1 );
		if( lastChar == 'i' )
		{
			label.Truncate( label.Length() - 1 );
			element.inverse = true;
		}

		char firstChar = label.GetChar(0);
		if( firstChar == '!' || firstChar == '^' )
		{
			element.special = true;
			if( firstChar == '^' )
				element.alternate = true;
			label.erase( 0, 1 );
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
		if( element.special )
		{
			double wheelClicks = 1.0;
			if( element.inverse )
				wheelClicks = -wheelClicks;
			puzzle->SpecialAction( 1.0, element.cutShape->GetHandle(), element.alternate );
		}
		else
		{
			TwistyPuzzle::Rotation::Direction rotDir = TwistyPuzzle::Rotation::DIR_CW;
			if( element.inverse )
				rotDir = TwistyPuzzle::Rotation::DIR_CCW;

			TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation( element.cutShape->GetHandle(), rotDir );
			puzzle->EnqueueRotation( rotation );
		}

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
	random.Seed( time( nullptr ) );

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
	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

	TwistyPuzzle::RotationList rotationList;
	if( !puzzle->Solve( rotationList ) )
		wxMessageBox( "Failed to find solution.  I suck.", "Solution not found.", wxICON_ERROR | wxCENTRE, this );
	else if( wxYES == wxMessageBox( wxString::Format( "A solution was found with %d rotations.  Run solution?", int( rotationList.size() ) ), "Solution found", wxICON_QUESTION | wxCENTRE | wxYES_NO, this ) )
		puzzle->EnqueueRotationList( rotationList );
	else
		_3DMath::FreeList< TwistyPuzzle::Rotation >( rotationList );
}

bool Frame::Save( void )
{
	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

	wxFileDialog fileDialog( this, "Save puzzle to file.", wxEmptyString, wxEmptyString, "XML file (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if( fileDialog.ShowModal() == wxID_OK )
	{
		wxString file = fileDialog.GetPath();
		wxFileName fileName( file );
		fileName.SetExt( "xml" );	// This must be done on Linux and won't hurt other platforms.
		file = fileName.GetFullPath();

		wxBusyCursor busyCursor;

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

		wxBusyCursor busyCursor;

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

void Frame::OnExit( wxCommandEvent& event )
{
	if( SaveProtect() )
	{
		timer.Stop();
		Close( true );
	}
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
			case ID_Solve:
			{
				event.Enable( wxGetApp().GetPuzzle()->SupportsSolve() ? true : false );
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
			case ID_DrawAxes:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_AXES ) ? true : false );
				break;
			}
			case ID_DrawAxisLabels:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_AXIS_LABELS ) ? true : false );
				break;
			}
			case ID_DrawStats:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_STATS ) ? true : false );
				break;
			}
			case ID_DrawBorders:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_BORDERS ) ? true : false );
				break;
			}
			case ID_DrawDiff:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_DIFF ) ? true : false );
				break;
			}
			case ID_LockLabels:
			{
				event.Check( ( canvas->GetRenderFlags() & Canvas::RENDER_DYNAMIC_LABELS ) ? false : true );
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
