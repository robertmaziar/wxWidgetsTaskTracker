#pragma once
#include "wx/wx.h"
#include "wx/toplevel.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"

enum {
	ID_ADD_TASK = 10000,

	ID_NAME = 10001,
	ID_AGE = 10002,
	ID_SEX = 10003,
	ID_VOTE = 10006,
	ID_RESET = 10004
};

/*!
* TaskDialog class declaration
*/
class TaskDialog : public wxDialog
{
	DECLARE_CLASS(TaskDialog)
	DECLARE_EVENT_TABLE()
public:
	TaskDialog();
	TaskDialog(
		wxWindow* parent, 
		wxWindowID id = ID_ADD_TASK, 
		const wxString& caption = wxT("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
	);

	void Init();
	bool Create(
		wxWindow* parent,
		wxWindowID id = ID_ADD_TASK,
		const wxString& caption = wxT("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
	);
	void CreateControls();
	void SetDialogValidators();
	void SetDialogHelp();
	void SetName(const wxString& name) { m_name = name; }
	wxString GetName() const { return m_name; }
	void SetAge(int age) { m_age = age; }
	int GetAge() const { return m_age; }

	void SetSex(bool sex) { sex ? m_sex = 1 : m_sex = 0; }
	bool GetSex() const { return m_sex == 1; }
	void SetVote(bool vote) { m_vote = vote; }
	bool GetVote() const { return m_vote; }

	//// TaskDialog event handler declarations
	/// wxEVT_UPDATE_UI event handler for ID_VOTE
	void OnVoteUpdate(wxUpdateUIEvent& event);
	/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESET
	void OnResetClick(wxCommandEvent& event);
	/// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
	void OnHelpClick(wxCommandEvent& event);
	
	//// TaskDialog member variables
	/// Data members
	wxString m_name;
	int m_age;
	int m_sex;
	bool m_vote;
};