// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "TwistyPuzzle.h"

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
	frame = nullptr;
	puzzle = new TwistyPuzzle();
}

/*virtual*/ Application::~Application( void )
{
	delete puzzle;
}

/*virtual*/ bool Application::OnInit( void )
{
	puzzle->SetType( TwistyPuzzle::CLASSIC_2x2x2 );

	frame = new Frame();
	frame->Show();

	return true;
}

// Application.cpp