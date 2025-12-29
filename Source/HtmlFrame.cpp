// HtmlFrame.cpp

#include "HtmlFrame.h"
#include "Application.h"
#include <wx/sizer.h>

HtmlFrame::HtmlFrame( wxWindow* parent, const wxString& initialPage /*= wxEmptyString*/ ) : wxFrame( parent, wxID_ANY, "Twisty Puzzle Documentation", wxDefaultPosition, wxSize( 600, 400 ) )
{
	wxPanel* navPanel = new wxPanel( this );

	homeButton = new wxBitmapButton( navPanel, ID_Home, wxArtProvider::GetBitmap( wxART_GO_HOME ) );
	backwardButton = new wxBitmapButton( navPanel, ID_Backward, wxArtProvider::GetBitmap( wxART_GO_BACK ) );
	forwardButton = new wxBitmapButton( navPanel, ID_Forward, wxArtProvider::GetBitmap( wxART_GO_FORWARD ) );

	wxBoxSizer* boxSizer = new wxBoxSizer( wxHORIZONTAL );
	boxSizer->Add( homeButton, 0 );
	boxSizer->Add( backwardButton, 0 );
	boxSizer->Add( forwardButton, 0 );
	navPanel->SetSizer( boxSizer );

	htmlWindow = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN );

	if( initialPage.IsEmpty() )
		GoHome();
	else
	{
		GoToPage( initialPage );
		UpdateUI();
	}

	boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( navPanel, 0, wxALL, 5 );
	boxSizer->Add( htmlWindow, 1, wxEXPAND );
	SetSizer( boxSizer );

	Bind( wxEVT_BUTTON, &HtmlFrame::OnHome, this, ID_Home );
	Bind( wxEVT_BUTTON, &HtmlFrame::OnForward, this, ID_Forward );
	Bind( wxEVT_BUTTON, &HtmlFrame::OnBackward, this, ID_Backward );
	Bind( wxEVT_HTML_LINK_CLICKED, &HtmlFrame::OnLinkClicked, this, wxID_ANY );
}

/*virtual*/ HtmlFrame::~HtmlFrame( void )
{
}

void HtmlFrame::UpdateUI( void )
{
	backwardButton->Enable( htmlWindow->HistoryCanBack() );
	forwardButton->Enable( htmlWindow->HistoryCanForward() );

	wxString pageTitle = htmlWindow->GetOpenedPageTitle();
	//...
}

// Instead of skipping this event to let the HTML window go to the
// hyperlink target, we have to do it ourselves so that we actually
// add to the HTML window's history list.
void HtmlFrame::OnLinkClicked( wxHtmlLinkEvent& event )
{
	const wxHtmlLinkInfo& linkInfo = event.GetLinkInfo();
	wxString reference = linkInfo.GetHref();

	if( reference.Find( "https://" ) >= 0 || reference.Find( "http://" ) >= 0 || reference.Find( "mailto:" ) >= 0 )
	{
#if defined LINUX
		system( "/usr/local/bin/xdg-open " + reference );
#else
		wxLaunchDefaultBrowser( reference );
#endif
	}
	else
	{
		reference = wxGetApp().ResolveRelativeResourcePath( "Data/Documentation/" + reference );
		htmlWindow->LoadPage( reference );
		UpdateUI();
	}
}

void HtmlFrame::OnHome( wxCommandEvent& event )
{
	GoHome();
	UpdateUI();
}

void HtmlFrame::GoHome( void )
{
	wxString indexPath = "Data/Documentation/index.html";
	indexPath = wxGetApp().ResolveRelativeResourcePath( indexPath );
	GoToPage( indexPath );
}

void HtmlFrame::GoToPage( const wxString& page )
{
	htmlWindow->LoadPage( page );
}

void HtmlFrame::OnForward( wxCommandEvent& event )
{
	htmlWindow->HistoryForward();
	UpdateUI();
}

void HtmlFrame::OnBackward( wxCommandEvent& event )
{
	htmlWindow->HistoryBack();
	UpdateUI();
}

// HtmlFrame.cpp