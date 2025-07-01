#ifndef FRAME
#define FRAME
#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public: 
        MainFrame(const wxString&);

    private:
        wxTextCtrl* numberInput;

        void OnButtonClicked(wxCommandEvent& event);
};

#endif