#include "MainFrame.hpp"
#include <wx/wx.h>

enum
{
    ID_OPENCONFIGFILE = wxID_HIGHEST + 1,
    ID_STOPCLOCK,
    ID_RUNCLOCK,
    ID_NEXTTICK
};

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)) {
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap stopClock(wxT("../../src/ui/img/stopClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap runClock(wxT("../../src/ui/img/runClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap nextTick(wxT("../../src/ui/img/nextTick.png"), wxBITMAP_TYPE_PNG);

    menuBar = new wxMenuBar;

    file = new wxMenu;
    file->Append(ID_OPENCONFIGFILE, wxT("&Open config file"));
    file->AppendSeparator();
    file->Append(wxID_EXIT, wxT("&Quit"));

    wxToolBar *toolBar = CreateToolBar();
    toolBar->AddTool(ID_STOPCLOCK, wxT("Stop clock"), stopClock);
    toolBar->AddTool(ID_RUNCLOCK, wxT("Run clock"), runClock);
    toolBar->AddTool(ID_NEXTTICK, wxT("Next tick"), nextTick);
    toolBar->Realize();

    menuBar->Append(file, wxT("&File"));
    SetMenuBar(menuBar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));
    Connect(ID_STOPCLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::StopClock));
    Connect(ID_RUNCLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::RunClock));
    Connect(ID_NEXTTICK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::NextTick));
    Centre();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}
