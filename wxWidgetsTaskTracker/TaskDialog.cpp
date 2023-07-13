#include "TaskDialog.h"
#include "wx/stattext.h"

BEGIN_EVENT_TABLE(TaskDialog, wxDialog)
	EVT_UPDATE_UI(wxID_OK, TaskDialog::onUpdateOKButton)
END_EVENT_TABLE()


TaskDialog::TaskDialog(
	wxWindow* parent, 
	wxWindowID id, 
	const wxString& caption, 
	const wxPoint& pos, 
	const wxSize& size, 
	long style) : wxDialog(parent, id, caption, pos, size, style)
{
	EnableCloseButton(true);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	
	// NAME FIELD START
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText* nameLabel = new wxStaticText(this, wxID_ANY, _("Name"));
	nameLabel->SetMinSize(wxSize(50, nameLabel->GetMinSize().y));
	nameSizer->Add(nameLabel);

	m_nameTextCtrl = new wxTextCtrl(this, wxID_ANY);
	nameSizer->Add(m_nameTextCtrl, 1);
	mainSizer->Add(nameSizer, 0, wxEXPAND | wxALL, 5);
	// NAME FIELD END
	
	// DATE FIELD START
	wxBoxSizer* dateAndTypeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* dateLabel = new wxStaticText(this, wxID_ANY, _("Date"));
	dateLabel->SetMinSize(wxSize(50, dateLabel->GetMinSize().y));
	dateAndTypeSizer->Add(dateLabel);
	
	m_datePickerCtrl = new wxDatePickerCtrl(this, wxID_ANY);
	dateAndTypeSizer->Add(m_datePickerCtrl, 1, wxRIGHT, 5);
	mainSizer->Add(dateAndTypeSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
	// DATE FIELD END
	
	// TYPE FIELD START
	wxArrayString types;
	types.push_back("CEP - Product Improvements");
	types.push_back("Green Button - Product Improvements");
	types.push_back("CEP - Bugs");
	types.push_back("Green Button - Bugs");
	types.push_back("Misc.");
	
	wxStaticText* typeLabel = new wxStaticText(this, wxID_ANY, _("Type"));
	typeLabel->SetMinSize(wxSize(50, typeLabel->GetMinSize().y));
	dateAndTypeSizer->Add(typeLabel);
	
	m_typeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, types);
	dateAndTypeSizer->Add(m_typeChoice);
	// TYPE FIELD END
	
	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxBOTTOM, 5);

	SetSizer(mainSizer);
	SetMinSize(wxSize(400, 100));
	Fit();
}

TaskDialog::~TaskDialog()
{
}

bool TaskDialog::TransferDataToWindow()
{
	m_nameTextCtrl->SetValue(m_name);
	m_datePickerCtrl->SetValue(m_date);
	
	int selection = m_typeChoice->FindString(m_type);
	if (selection != wxNOT_FOUND)
	{
		m_typeChoice->SetSelection(selection);
	}

	return true;
}

bool TaskDialog::TransferDataFromWindow()
{
	m_name = m_nameTextCtrl->GetValue();
	m_date = m_datePickerCtrl->GetValue();

	int selection = m_typeChoice->GetSelection();
	if (selection != wxNOT_FOUND) {
		m_type = m_typeChoice->GetString(selection);
	}

	return true;
}

void TaskDialog::onUpdateOKButton(wxUpdateUIEvent& event)
{
	event.Enable(false);

	if (!m_nameTextCtrl->GetValue().empty())
	{
		if (!m_datePickerCtrl->GetValue().FormatISODate().empty())
		{
			int selection = m_typeChoice->GetSelection();
			if (selection != wxNOT_FOUND)
			{
				event.Enable(true);
			}
		}
	}
}
