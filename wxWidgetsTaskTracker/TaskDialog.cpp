#include "TaskDialog.h"
#include "wx/wxprec.h"
#include "wx/valtext.h"
#include "wx/valgen.h"

IMPLEMENT_CLASS(TaskDialog, wxDialog)

/*!
* Transfer data from the window
*/
BEGIN_EVENT_TABLE(TaskDialog, wxDialog)
EVT_UPDATE_UI(ID_VOTE, TaskDialog::OnVoteUpdate)
EVT_BUTTON(ID_RESET, TaskDialog::OnResetClick)
EVT_BUTTON(wxID_HELP, TaskDialog::OnHelpClick)
END_EVENT_TABLE()

/*!
* TaskDialog constructors
*/
TaskDialog::TaskDialog()
{
	Init();
}

TaskDialog::TaskDialog(
	wxWindow* parent,
	wxWindowID id, const wxString& caption,
	const wxPoint& pos, const wxSize& size, long style)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}

void TaskDialog::Init()
{
	m_name = wxEmptyString;
	m_age = 25;
	m_sex = false;
	m_vote = false;
}

/*!
* Task creator
*/
bool TaskDialog::Create(wxWindow* parent,
	wxWindowID id, const wxString& caption,
	const wxPoint& pos, const wxSize& size, long style)
{
	// We have to set extra styles before creating the
	// dialog
	SetExtraStyle(wxWS_EX_BLOCK_EVENTS | wxDIALOG_EX_CONTEXTHELP);

	if (!wxDialog::Create(parent, id, caption, pos, size, style))
	{
		return false;
	}

	CreateControls();
	SetDialogHelp();
	SetDialogValidators();

	// This fits the dialog to the minimum size dictated by
	// the sizers
	GetSizer()->Fit(this);

	// This ensures that the dialog cannot be sized smaller
	// than the minimum size
	GetSizer()->SetSizeHints(this);

	// Centre the dialog on the parent or (if none) screen
	Centre();

	return true;
}
/*!
* Control creation for TaskDialog
*/
void TaskDialog::CreateControls()
{
	// A top-level sizer
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(topSizer);

	// A second box sizer to give more space around the controls
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	// A friendly message
	wxStaticText* descr = new wxStaticText(
		this,
		wxID_STATIC,
		wxT("Please enter your name, age and sex, and specify whether you wish to\nvote in a general election."),
		wxDefaultPosition,
		wxDefaultSize,
		0
	);

	// Label for the name text control
	wxStaticText* nameLabel = new wxStaticText(
		this,
		wxID_STATIC,
		wxT(" & Name:"),
		wxDefaultPosition,
		wxDefaultSize,
		0
	);
	boxSizer->Add(descr, 0, wxALIGN_LEFT | wxALL, 5);
	// Spacer
	boxSizer->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	boxSizer->Add(nameLabel, 0, wxALIGN_LEFT | wxALL, 5);

	// A text control for the user�s name
	wxTextCtrl* nameCtrl = new wxTextCtrl(this, ID_NAME, wxT("Emma"), wxDefaultPosition, wxDefaultSize, 0);
	boxSizer->Add(nameCtrl, 0, wxGROW | wxALL, 5);

	// A horizontal box sizer to contain age, sex and vote
	wxBoxSizer* ageSexVoteBox = new wxBoxSizer(wxHORIZONTAL);
	boxSizer->Add(ageSexVoteBox, 0, wxGROW | wxALL, 5);

	// Label for the age control
	wxStaticText* ageLabel = new wxStaticText(
		this,
		wxID_STATIC,
		wxT(" & Age:"),
		wxDefaultPosition,
		wxDefaultSize,
		0
	);
	ageSexVoteBox->Add(ageLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// A spin control for the user�s age
	wxSpinCtrl* ageSpin = new wxSpinCtrl(
		this,
		ID_AGE,
		wxEmptyString,
		wxDefaultPosition,
		wxSize(60, -1),
		wxSP_ARROW_KEYS,
		0,
		120,
		25
	);
	ageSexVoteBox->Add(ageSpin, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// Label for the sex control
	wxStaticText* sexLabel = new wxStaticText(
		this,
		wxID_STATIC,
		wxT(" & Sex:"),
		wxDefaultPosition,
		wxDefaultSize,
		0
	);
	ageSexVoteBox->Add(sexLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// Create the sex choice control
	wxString sexStrings[] = {
		wxT("Male"),
		wxT("Female")
	};

	wxChoice* sexChoice = new wxChoice(
		this, 
		ID_SEX,
		wxDefaultPosition, 
		wxSize(80, -1), 
		WXSIZEOF(sexStrings),
		sexStrings, 0
	);
	sexChoice->SetStringSelection(wxT("Female"));
	
	ageSexVoteBox->Add(sexChoice, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	// Add a spacer that stretches to push the Vote control to the right
	ageSexVoteBox->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxCheckBox* voteCheckBox = new wxCheckBox(
		this, 
		ID_VOTE,
		wxT(" & Vote"), 
		wxDefaultPosition, 
		wxDefaultSize, 
		0
	);
	voteCheckBox->SetValue(true);
	ageSexVoteBox->Add(voteCheckBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	// A dividing line before the OK and Cancel buttons
	wxStaticLine* line = new wxStaticLine(
		this, 
		wxID_STATIC,
		wxDefaultPosition, 
		wxDefaultSize, 
		wxLI_HORIZONTAL
	);
	boxSizer->Add(line, 0, wxGROW | wxALL, 5);

	// A horizontal box sizer to contain Reset, OK, Cancel and Help
	wxBoxSizer* okCancelBox = new wxBoxSizer(wxHORIZONTAL);
	boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	
	// The Reset button
	wxButton* reset = new wxButton(
		this, 
		ID_RESET, 
		wxT(" & Reset"),
		wxDefaultPosition, 
		wxDefaultSize, 
		0
	);
	okCancelBox->Add(reset, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// The OK button
	wxButton* ok = new wxButton(
		this, 
		wxID_OK, 
		wxT(" & OK"),
		wxDefaultPosition, 
		wxDefaultSize, 
		0
	);
	okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// The Cancel button
	wxButton* cancel = new wxButton(
		this, 
		wxID_CANCEL,
		wxT(" & Cancel"), 
		wxDefaultPosition, 
		wxDefaultSize, 
		0
	);
	okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	// The Help button
	wxButton* help = new wxButton(
		this, 
		wxID_HELP, 
		wxT(" & Help"),
		wxDefaultPosition, 
		wxDefaultSize, 
		0
	);
	okCancelBox->Add(help, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
}
// Set the validators for the dialog controls
void TaskDialog::SetDialogValidators()
{
	FindWindow(ID_NAME)->SetValidator(wxTextValidator(wxFILTER_ALPHA, &m_name));
	FindWindow(ID_AGE)->SetValidator(wxGenericValidator(&m_age));
	FindWindow(ID_SEX)->SetValidator(wxGenericValidator(&m_sex));
	FindWindow(ID_VOTE)->SetValidator(wxGenericValidator(&m_vote));
}

// Sets the help text for the dialog controls
void TaskDialog::SetDialogHelp()
{
	wxString nameHelp = wxT("Enter your full name.");
	wxString ageHelp = wxT("Specify your age.");
	wxString sexHelp = wxT("Specify your gender, male or female.");
	wxString voteHelp = wxT("Check this if you wish to vote.");

	FindWindow(ID_NAME)->SetHelpText(nameHelp);
	FindWindow(ID_NAME)->SetToolTip(nameHelp);
	FindWindow(ID_AGE)->SetHelpText(ageHelp);
	FindWindow(ID_AGE)->SetToolTip(ageHelp);
	FindWindow(ID_SEX)->SetHelpText(sexHelp);
	
	/*FindWindow(ID_SEX)->SetToolTip(sexHelp);
		FindWindow(ID_VOTE)->SetHelpText(voteHelp);*/
	FindWindow(ID_VOTE)->SetToolTip(voteHelp);
}
/*!
* wxEVT_UPDATE_UI event handler for ID_CHECKBOX
*/
void TaskDialog::OnVoteUpdate(wxUpdateUIEvent& event)
{
	wxSpinCtrl* ageCtrl = (wxSpinCtrl*)FindWindow(ID_AGE);
	if (ageCtrl->GetValue() < 18)
	{
		event.Enable(false);
		event.Check(false);
	}
	else {
		event.Enable(true);
	}
}

/*!
* wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESET
*/
void TaskDialog::OnResetClick(wxCommandEvent& event)
{
	Init();
	TransferDataToWindow();
}

/*!
* wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
*/
void TaskDialog::OnHelpClick(wxCommandEvent& event)
{
	// Normally we would wish to display proper online help.
	// For this example, we�re just using a message box.
	/*
	wxGetApp().GetHelpController().DisplaySection(wxT("Personal record
	dialog"));
	*/
	wxString helpText =
		wxT("Please enter your full name, age and gender.\n")
		wxT("Also indicate your willingness to vote in general elections.\n\n")
		wxT("No non - alphabetical characters are allowed in the name field.\n")
		wxT("Try to be honest about your age."
	);

	wxMessageBox(helpText,
		wxT("Personal Record Dialog Help"),
		wxOK | wxICON_INFORMATION, 
		this
	);
}