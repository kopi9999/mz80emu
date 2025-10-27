#include "MainFrame.hpp"
#include <wx/wx.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)) {
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap stopClock(wxT("../../src/ui/img/stopClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap runClock(wxT("../../src/ui/img/runClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap nextTick(wxT("../../src/ui/img/nextTick.png"), wxBITMAP_TYPE_PNG);

    menuBar = new wxMenuBar;

    file = new wxMenu;
    file->Append(wxID_ANY, wxT("&Open config file"));
    file->AppendSeparator();
    file->Append(wxID_EXIT, wxT("&Quit"));

    wxToolBar *toolBar = CreateToolBar();
    toolBar->AddTool(wxID_ANY, wxT("Stop clock"), stopClock);
    toolBar->AddTool(wxID_ANY, wxT("Run clock"), runClock);
    toolBar->AddTool(wxID_ANY, wxT("Next tick"), nextTick);
    toolBar->Realize();

    menuBar->Append(file, wxT("&File"));
    SetMenuBar(menuBar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));
    Centre();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}