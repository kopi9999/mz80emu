#ifndef MAIN_FRAME_APP
#define MAIN_FRAME_APP
#define WinMain main
#include <wx/wx.h>

class MainFrameApp : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnExit();
    virtual void OnFatalException();
};

#endif
