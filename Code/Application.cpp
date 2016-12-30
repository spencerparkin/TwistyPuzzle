// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "TwistyPuzzle.h"
#include "Rubiks3x3x3.h"

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
	puzzle = new Rubiks3x3x3();
	puzzle->Reset();

	frame = new Frame();
	frame->Show();

	return true;
}

// Application.cpp