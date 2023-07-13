#pragma once
#include "wx/wx.h"
#include "wx/frame.h"
#include "wx/chartype.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void OnAbout(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
private:
	DECLARE_EVENT_TABLE();
};