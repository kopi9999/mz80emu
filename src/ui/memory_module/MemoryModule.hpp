#ifndef FRAME
#define FRAME
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <map>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    wxListBox* selectedModulesList;
    wxListBox* instanceList;
    wxListBox* interfacesList;
    wxTextCtrl* clockPeriodInput;
    wxTextCtrl* clockDepthInput;
    wxListBox* strobeUpInstanceList;
    wxListBox* strobeDownInstanceList;

    std::vector<std::string> selectedModules;
    std::vector<std::string> instanceNames;
    std::map<int, std::vector<std::string>> instanceInterfaces;

};

#endif
