// HtmlFrame.h

#pragma once

#include <wx/frame.h>
#include <wx/html/htmlwin.h>
#include <wx/bmpbuttn.h>
#include <wx/artprov.h>

class HtmlFrame : public wxFrame
{
public:

	HtmlFrame( wxWindow* parent, const wxString& initialPage /*= wxEmptyString*/ );
	virtual ~HtmlFrame( void );

	void UpdateUI( void );

	void GoHome( void );
	void GoToPage( const wxString& page );

	enum
	{
		ID_Home = wxID_HIGHEST,
		ID_Forward,
		ID_Backward,
	};

	void OnLinkClicked( wxHtmlLinkEvent& event );
	void OnHome( wxCommandEvent& event );
	void OnForward( wxCommandEvent& event );
	void OnBackward( wxCommandEvent& event );

	wxBitmapButton* homeButton;
	wxBitmapButton* backwardButton;
	wxBitmapButton* forwardButton;
	wxHtmlWindow* htmlWindow;
};

// HtmlFrame.h