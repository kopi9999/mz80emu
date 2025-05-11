#ifndef FRAME
#define FRAME
#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public: 
        MainFrame(const wxString&);

    private:
        void OnButtonClicked(wxCommandEvent& event);
};

#endif