#include "customDialog.h"
#include "wx/sizer.h"
#include "wx/button.h"

customDialog::customDialog(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	create(parent, id, caption, pos, size, style);
	EnableCloseButton(true);
}

void customDialog::init()
{
	m_timeDisplay = new wxStaticText(
		this,
		wxID_ANY,
		"",
		wxDefaultPosition,
		wxDefaultSize,
		wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE | wxBORDER_SIMPLE
	);
}

bool customDialog::create(
	wxWindow* parent,
	wxWindowID id, const wxString& caption,
	const wxPoint& pos, const wxSize& size, long style)
{
	// We have to set extra styles before creating the dialog
	SetExtraStyle(wxWS_EX_BLOCK_EVENTS | wxDIALOG_EX_CONTEXTHELP);

	if (!wxDialog::Create(parent, id, caption, pos, size, style))
	{
		return false;
	}

	init();
	createControls();

	// This fits the dialog to the minimum size dictated by the sizers
	GetSizer()->Fit(this);

	// This ensures that the dialog cannot be sized smaller than the minimum size
	GetSizer()->SetSizeHints(this);

	// Centre the dialog on the parent or (if none) screen
	Centre();

	return true;
}

void customDialog::createControls()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(topSizer);

	wxButton* startButton = nullptr;
	wxButton* stopButton = nullptr;
	wxFont font;

	font = m_timeDisplay->GetFont();
	font.MakeBold().MakeLarger();

	m_timeDisplay->SetFont(font);

	updateDisplayedTime();


	topSizer->Add(m_timeDisplay, wxSizerFlags().Expand().DoubleBorder());

	startButton = new wxButton(this, wxID_ANY, "Start timer");
	startButton->Bind(wxEVT_BUTTON, &customDialog::onStartTimer, this);
	topSizer->Add(startButton, wxSizerFlags().Expand().Border());
	
	stopButton = new wxButton(this, wxID_ANY, "Stop timer");
	stopButton->Bind(wxEVT_BUTTON, &customDialog::onStopTimer, this);
	topSizer->Add(stopButton,wxSizerFlags().Expand().Border());

	m_timer.Bind(wxEVT_TIMER, &customDialog::onUpdateDisplayedTime, this);
}

void customDialog::onStartTimer(wxCommandEvent&)
{
	m_startTime = wxDateTime::Now();
	m_timer.Start(1000); // every second
	updateDisplayedTime(); // update immediatelly do not wait a second
}

void customDialog::onStopTimer(wxCommandEvent&)
{
	m_timer.Stop();
	updateDisplayedTime();
}

void customDialog::onUpdateDisplayedTime(wxTimerEvent&)
{
	updateDisplayedTime();
}

void customDialog::updateDisplayedTime()
{
	if (m_timer.IsRunning())
	{
		const wxDateTime currentTime = wxDateTime::Now();
		const wxTimeSpan ellapsedTime = currentTime - m_startTime;

		m_timeDisplay->SetLabel(ellapsedTime.Format("%D:%H:%M:%S"));
	}
	else
	{
		m_timeDisplay->SetLabel("  <Not Timing>  ");
	}
}
