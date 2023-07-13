#pragma once
#include "wx/dialog.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/datectrl.h"
#include "wx/choice.h"


class TaskDialog : public wxDialog
{
public:
	TaskDialog(
		wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& caption = wxT("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
	);
	
	~TaskDialog();

	wxString getName() const { return m_name; }
	wxDateTime getDate() const { return m_date; }
	wxString getType() const { return m_type; }

private:
	wxTextCtrl* m_nameTextCtrl = nullptr;
	wxDatePickerCtrl* m_datePickerCtrl = nullptr;
	wxChoice* m_typeChoice = nullptr;
	wxString m_name = wxEmptyString;
	wxDateTime m_date = wxDefaultDateTime.Now();
	wxString m_type = "Misc.";

	virtual bool TransferDataToWindow() override;
	virtual bool TransferDataFromWindow() override;

	void onUpdateOKButton(wxUpdateUIEvent& event);

	DECLARE_EVENT_TABLE()
};

