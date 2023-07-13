#pragma once
#include "wx\dialog.h"
#include "wx\stattext.h"
#include "wx\timer.h"

enum {
	ID_ON_START_TIMER = 10006,
	ID_ON_STOP_TIMER = 10007,
	ID_ON_UPDATE_DISPLAYED_TIME = 10008
};

class customDialog : public wxDialog
{
public:
	customDialog();
	customDialog(
		wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& caption = wxT("Task Timer"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
	);
private:
	wxStaticText* m_timeDisplay;
	wxTimer m_timer; // why not a pointer??????
	wxDateTime m_startTime;

	void init();

	bool create(
		wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& caption = wxT("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
	);

	void createControls();

	void onStartTimer(wxCommandEvent&);

	void onStopTimer(wxCommandEvent&);

	void onUpdateDisplayedTime(wxTimerEvent&);

	void updateDisplayedTime();
};