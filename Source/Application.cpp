// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "TwistyPuzzle.h"
#include "Puzzles/Rubiks3x3x3.h"

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
	frame = nullptr;
	puzzle = nullptr;
	fontSystem = nullptr;
}

/*virtual*/ Application::~Application( void )
{
	delete puzzle;
	delete fontSystem;
}

/*virtual*/ bool Application::OnInit( void )
{
	wxImage::AddHandler( new wxPNGHandler() );

	fontSystem = new FontSys::System();
	fontSystem->Initialize();
	fontSystem->SetFontBaseDir( ( const char* )ResolveRelativeResourcePath( "Data/Fonts" ).c_str() );

	puzzle = new Rubiks3x3x3();
	puzzle->Reset();

	frame = new Frame();
	frame->Show();

	return true;
}

void Application::SetPuzzle( TwistyPuzzle* puzzle )
{
	delete this->puzzle;
	this->puzzle = puzzle;
}

wxString Application::ResolveRelativeResourcePath( const wxString& relPath )
{
	wxString fullPath = relPath;

#if defined LINUX
	wxString snapDir;
	if( wxGetEnv( "SNAP", &snapDir ) )
		fullPath = snapDir + "/share/TwistyPuzzle/" + fullPath;
#endif

	return fullPath;
}

// Application.cpp