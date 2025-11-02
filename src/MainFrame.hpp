#ifndef MAIN_FRAME
#define MAIN_FRAME
#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public:
        MainFrame();
        void OnQuit(wxCommandEvent&);
        void RunClock(wxCommandEvent&);
        void StopClock(wxCommandEvent&);
        void NextTick(wxCommandEvent&);

        wxMenuBar *menuBar;
        wxMenu *file;
        //bool clockStopped = false;
};

#endif
