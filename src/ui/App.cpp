#include "App.h"
#include "ConfiguratorFrame.h"
#include <wx/wx.h>
#define WinMain main

wxIMPLEMENT_APP(App);

bool App::OnInit(){
  ConfiguratorFrame* configuratorFrame = new ConfiguratorFrame("C++ GUI");
  configuratorFrame->Show();
  return true;
}
