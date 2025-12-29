// Application.h

#pragma once

#include <wx/app.h>
#include <GL/glew.h>
#include <FontSystem.h>

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
	FontSys::System* GetFontSystem( void ) { return fontSystem; }
	wxString ResolveRelativeResourcePath( const wxString& relPath );

private:

	Frame* frame;
	TwistyPuzzle* puzzle;
	FontSys::System* fontSystem;
};

wxDECLARE_APP( Application );

// Application.h