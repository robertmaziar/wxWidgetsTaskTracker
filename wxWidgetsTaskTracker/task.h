#pragma once
#include "wx\wx.h"

class task
{
public:
	task(); 

	task(wxString name, wxDateTime date, wxTimeSpan time_elapsed, wxInt32 type);

	~task();

private:
	wxString m_name;
	wxDateTime m_date;
	wxTimeSpan m_time_elapsed;
	wxInt32 m_type;
};