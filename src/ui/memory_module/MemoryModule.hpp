#ifndef FRAME
#define FRAME
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <cstdint>
//#include <map>
enum { ID_MENU_REFRESH = wxID_HIGHEST + 1 };

class App : public wxApp
{
  public:
    bool OnInit();
};

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
    wxGrid* grid;
    wxTimer refresherTimer;
    wxLongLong startTime;

    void OnTimer(wxTimerEvent& event);

    std::vector<std::string> selectedModules;
    std::vector<std::string> instanceNames;
    //std::map<int, std::vector<std::string>> instanceInterfaces;
    uint8_t memory_table [65536]; 

    
    void OnGridContextMenu(wxContextMenuEvent& event);
    void OnRefreshMenu(wxCommandEvent&);
    void GridCreate(wxPanel* panel);
    void TableTextValues();
    void SizerEventTale();
    void Refresher();
    void OnChangeRow(wxGridEvent& event);
    void GridFill(int Rows , int Cols);
    void OnRightClick(wxGridEvent& event);
};


#endif
