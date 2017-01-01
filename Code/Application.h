// Application.h

#pragma once

#include <wx/app.h>

class Frame;
class TwistyPuzzle;

class Application : public wxApp
{
public:

	Application( void );
	virtual ~Application( void );

	virtual bool OnInit( void ) override;

	Frame* GetFrame( void ) { return frame; }
	TwistyPuzzle* GetPuzzle( void ) { return puzzle; }
	void SetPuzzle( TwistyPuzzle* puzzle );

private:

	Frame* frame;
	TwistyPuzzle* puzzle;
};

wxDECLARE_APP( Application );

// Application.h