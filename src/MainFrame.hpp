#ifndef MAIN_FRAME
#define MAIN_FRAME
#include <wx/wx.h>
#include <wx/notebook.h>

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
            //ID_LOAD_CONFIG_FILE = wxID_HIGHEST + 1,
            ID_STOP_CLOCK = wxID_HIGHEST + 1,
            ID_RUN_CLOCK,
            ID_NEXT_TICK,
            ID_CLOCK_PERIOD_TEXT_CTRL,
            ID_OVERRIDE_CLOCK_PERIOD_BUTTON,
            ID_INSTANCES_LIST,
            ID_UI_MODULE_CONTROL
        };

        wxMenuBar *menuBar;
        wxMenu *file;
        wxNotebook *uiModuleControl;
    
    private:
        void OnTimer(wxTimerEvent& event);
        wxTimer crashHandlingTimer;
};

#endif
