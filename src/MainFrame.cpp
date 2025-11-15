#include "MainFrame.hpp"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/tglbtn.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)) {
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap stopClock(wxT("../../src/ui/img/stopClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap runClock(wxT("../../src/ui/img/runClock.png"), wxBITMAP_TYPE_PNG);
    wxBitmap nextTick(wxT("../../src/ui/img/nextTick.png"), wxBITMAP_TYPE_PNG);


    menuBar = new wxMenuBar;

    file = new wxMenu;
    file->Append(ID_LOAD_CONFIG_FILE, wxT("&Load config file"));
    file->AppendSeparator();
    file->Append(wxID_EXIT, wxT("&Quit"));

    wxToolBar *toolBar = CreateToolBar();
    wxTextCtrl *clockPeriodTextCtrl = new wxTextCtrl(toolBar, ID_CLOCK_PERIOD_TEXT_CTRL, "", wxDefaultPosition, wxSize(200, -1));
    wxToggleButton *overrideClockPeriodButton = new wxToggleButton(toolBar, ID_OVERRIDE_CLOCK_PERIOD_BUTTON, "Override clock period");
    overrideClockPeriodButton->Disable();
    toolBar->AddTool(ID_STOP_CLOCK, wxT("Stop clock"), stopClock);
    toolBar->AddTool(ID_RUN_CLOCK, wxT("Run clock"), runClock);
    toolBar->AddTool(ID_NEXT_TICK, wxT("Next tick"), nextTick);
    toolBar->AddSeparator();
    toolBar->AddControl(clockPeriodTextCtrl);
    toolBar->AddControl(overrideClockPeriodButton);
    toolBar->Realize();
    menuBar->Append(file, wxT("&File"));
    SetMenuBar(menuBar);


    wxPanel *mainPanel = new wxPanel(this);
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxListCtrl *instancesList = new wxListCtrl(mainPanel, ID_INSTANCES_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
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
    Connect(ID_STOP_CLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::StopClock));
    Connect(ID_RUN_CLOCK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::RunClock));
    Connect(ID_NEXT_TICK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::NextTick));
    Connect(ID_CLOCK_PERIOD_TEXT_CTRL, wxEVT_TEXT, wxCommandEventHandler(MainFrame::ValidateClockPeriodValue));
    Connect(ID_OVERRIDE_CLOCK_PERIOD_BUTTON, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(MainFrame::OverrideClockPeriodButton));
    Centre();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}
