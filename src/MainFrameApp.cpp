#include "MainFrameApp.hpp"
#include "MainFrame.hpp"
#include <wx/wx.h>
#define WinMain main

wxIMPLEMENT_APP(MainFrameApp);

bool MainFrameApp::OnInit() {
    MainFrame *mainFrame = new MainFrame();
    mainFrame->Show();
    return true;
}