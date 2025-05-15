#ifndef FRAME
#define FRAME

#include <wx/wx.h>
#include <vector>
#include <string>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString&);

private:
    wxListBox* availableModulesList;
    wxListBox* selectedModulesList;
    wxButton* addModuleButton;

    std::vector<std::string> moduleNames;

    void OnAddModuleClicked(wxCommandEvent& event);
    void LoadModules();
};

#endif
