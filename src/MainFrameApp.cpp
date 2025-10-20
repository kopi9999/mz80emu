#include "MainFrameApp.hpp"
#include "MainFrame.hpp"
#include <wx/wx.h>

wxIMPLEMENT_APP(MainFrameApp);

bool MainFrameApp::OnInit() {
    wxWeakRef<MainFrame> mainFrame = new MainFrame();
    mainFrame->Show();
    return true;
}