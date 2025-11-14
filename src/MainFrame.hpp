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
        void OverrideClockPeriodButton(wxCommandEvent&);
        void ValidateClockPeriodValue(wxCommandEvent&);
        
        enum {
            ID_LOADCONFIGFILE = wxID_HIGHEST + 1,
            ID_STOPCLOCK,
            ID_RUNCLOCK,
            ID_NEXTTICK,
            ID_CLOCK_PERIOD_TEXT_CTRL,
            ID_OVERRIDE_CLOCK_PERIOD_BUTTON,
            ID_INSTANCESLIST
        };

        wxMenuBar *menuBar;
        wxMenu *file;
        //bool clockStopped = false;
};

#endif
