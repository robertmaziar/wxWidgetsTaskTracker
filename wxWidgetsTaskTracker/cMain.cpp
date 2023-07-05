#include "cMain.h"

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
	TaskDialog dialog(NULL, ID_ADD_TASK, wxT("Add Task"));
	dialog.SetName(wxEmptyString);
	dialog.SetAge(30);
	dialog.SetSex(0);
	dialog.SetVote(true);

	if (dialog.ShowModal() == wxID_OK)
	{
		wxString name = dialog.GetName();
		int age = dialog.GetAge();
		bool sex = dialog.GetSex();
		bool vote = dialog.GetVote();
	}
}

void cMain::OnQuit(wxCommandEvent& event)
{
	Close();
}
