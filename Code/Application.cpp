// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "TwistyPuzzle.h"
#include "Rubiks3x3x3.h"
#include <wx/fs_arc.h>

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
	frame = nullptr;
	puzzle = nullptr;
}

/*virtual*/ Application::~Application( void )
{
	delete puzzle;
}

/*virtual*/ bool Application::OnInit( void )
{
	wxImage::AddHandler( new wxPNGHandler() );
	wxFileSystem::AddHandler( new wxArchiveFSHandler() );

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

// Application.cpp