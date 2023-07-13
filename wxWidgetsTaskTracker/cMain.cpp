#include "cMain.h"
#include <chrono>
#include <ctime> 
#include <string>
#include "TaskDialog.h"
//#include "customDialog.h"

BEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_MENU(wxID_ABOUT, cMain::OnAbout)
	EVT_MENU(wxID_ADD, cMain::OnAdd)
	EVT_MENU(wxID_EXIT, cMain::OnQuit)
END_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "wxWidgets - Task Tracker", wxPoint(30, 30), wxSize(800, 600))
{
	// Set the frame icon
	//SetIcon(wxIcon(mondrian_xpm));

	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, wxT(" & Exit \tAlt+X"),
		wxT("Quit this program"));

	wxMenu* taskMenu = new wxMenu;
	taskMenu->Append(wxID_ADD, wxT(" & Add...\tCtrl+Shift+N"),
		wxT("Add a task"));

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, wxT(" & About...\tF1"),
		wxT("Show about dialog"));

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT(" & File"));
	menuBar->Append(taskMenu, wxT(" & Tasks"));
	menuBar->Append(helpMenu, wxT(" & Help"));
	SetMenuBar(menuBar);

	//task_current = new wxTextCtrl(this, wxID_ANY);
	//task_list = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));

	CreateStatusBar(2);
	SetStatusText(wxT("Welcome to wxWidgets!"));
}

cMain::~cMain()
{
}

void cMain::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("Hello and welcome to % s"), wxVERSION_STRING);
	wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void cMain::OnAdd(wxCommandEvent& event)
{
	TaskDialog dialog(this, wxID_ANY, wxT("Add Task"));

	if (dialog.ShowModal() == wxID_OK)
	{
		wxMessageBox(wxString::Format("Name = %s\nDate = %s\nType = %s\n",
			dialog.getName(), dialog.getDate().FormatISODate(), dialog.getType()));
	}
}

void cMain::OnQuit(wxCommandEvent& event)
{
	Close();
}