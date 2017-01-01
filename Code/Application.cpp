// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "TwistyPuzzle.h"
#include "Bubbloid4x4x5.h"

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
	puzzle = new Bubbloid4x4x5();
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