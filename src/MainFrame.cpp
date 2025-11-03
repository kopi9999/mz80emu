#include "MainFrame.hpp"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/tglbtn.h>

enum
{
    ID_LOADCONFIGFILE = wxID_HIGHEST + 1,
    ID_STOPCLOCK,
    ID_RUNCLOCK,
    ID_NEXTTICK,
    ID_CLOCKPERIODTEXTCTRL,
    ID_OVERRIDECLOCKPERIODBUTTON,
    ID_INSTANCESLIST
};

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)) {
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap stopClock(wxT("../../src/ui/img/stopClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap runClock(wxT("../../src/ui/img/runClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap nextTick(wxT("../../src/ui/img/nextTick.png"), wxBITMAP_TYPE_PNG);


    menuBar = new wxMenuBar;

    file = new wxMenu;
    file->Append(ID_LOADCONFIGFILE, wxT("&Load config file"));
    file->AppendSeparator();
    file->Append(wxID_EXIT, wxT("&Quit"));

    wxToolBar *toolBar = CreateToolBar();
    wxTextCtrl *clockPeriodTextCtrl = new wxTextCtrl(toolBar, ID_CLOCKPERIODTEXTCTRL, "", wxDefaultPosition, wxSize(200, -1));
    wxToggleButton *overrideClockPeriodButton = new wxToggleButton(toolBar, ID_OVERRIDECLOCKPERIODBUTTON, "Override clock period");
    toolBar->AddTool(ID_STOPCLOCK, wxT("Stop clock"), stopClock);
    toolBar->AddTool(ID_RUNCLOCK, wxT("Run clock"), runClock);
    toolBar->AddTool(ID_NEXTTICK, wxT("Next tick"), nextTick);
    toolBar->AddSeparator();
    toolBar->AddControl(clockPeriodTextCtrl);
    toolBar->AddControl(overrideClockPeriodButton);
    toolBar->Realize();
    menuBar->Append(file, wxT("&File"));
    SetMenuBar(menuBar);


    wxPanel *mainPanel = new wxPanel(this);
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxListCtrl *instancesList = new wxListCtrl(mainPanel, ID_INSTANCESLIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    wxListItem instancesColumn;
    instancesColumn.SetId(0);
    instancesColumn.SetText( _("Module instances") );
    instancesColumn.SetWidth(200);
    instancesList->InsertColumn(0, instancesColumn);

    mainSizer->Add(instancesList, 0, wxEXPAND);
    /* Adding new element to the sizer:
    mainSizer->Add(
        elementName,
        1, // 1 - make element stretchable horizontally, 0 - unstretchable
        wxEXPAND | wxALL, // wxEXPAND - elements stretches vertically, wxALL - border around all element
        10 // border size
    );
    */
    mainPanel->SetSizer(mainSizer);


    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));
    Connect(ID_STOPCLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::StopClock));
    Connect(ID_RUNCLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::RunClock));
    Connect(ID_NEXTTICK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::NextTick));
    Connect(ID_OVERRIDECLOCKPERIODBUTTON, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(MainFrame::OverrideClockPeriodButton));
    Centre();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}
