#include "MainFrameApp.hpp"
#include "MainFrame.hpp"
#include <wx/wx.h>

wxIMPLEMENT_APP(MainFrameApp);

bool MainFrameApp::OnInit() {
    MainFrame *mainFrame = new MainFrame();
    mainFrame->Show();
    return true;
}