#ifndef MEMORY_UI_MOD
#define MEMORY_UI_MOD

#define GRID_HEIGHT 6554

#include <stdint.h>
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <cstdint>
#include "../uiModuleInternal.hpp"

struct Instance{
    uint8_t* data;
    uint32_t size;
    uint8_t readState;
    uint8_t writeState;
    uint8_t readTrigger;
};

enum { ID_MENU_REFRESH = wxID_HIGHEST + 1 };
enum { ID_MENU_LOAD = wxID_HIGHEST + 2 };
enum { ID_MENU_SAVE = wxID_HIGHEST + 3 };

class UiModulePanel : public wxPanel {
    public:
        UiModulePanel(wxControl* parent, void* instance, void** interfaces);

    private:
        struct Instance* instance = NULL;
        void** interfaces = NULL;

        wxListBox* selectedModulesList; 
        wxListBox* instanceList;
        wxListBox* interfacesList;
        wxTextCtrl* clockPeriodInput;
        wxTextCtrl* clockDepthInput;
        wxListBox* strobeUpInstanceList;
        wxListBox* strobeDownInstanceList;
        wxGrid* grid;
        wxTimer refresherTimer;

        void OnTimer(wxTimerEvent& event);

        std::vector<std::string> selectedModules;
        std::vector<std::string> instanceNames;
        //std::map<int, std::vector<std::string>> instanceInterfaces;

    
        void OnGridContextMenu(wxContextMenuEvent& event);
        void OnRefreshMenu(wxCommandEvent&);
        void GridCreate(wxPanel* panel);
        void TableTextValues();
        void SizerEventTale();
        void Refresher();
        void OnChangeRow(wxGridEvent& event);
        void GridFill(int Rows , int Cols);
        void OnRightClick(wxGridEvent& event);

        bool ReadFromSelectedBINFile(const wxString& filePath ); 
        bool SaveUint32TableToBin(const wxString& filePath);
        void SelectFileWindow(wxCommandEvent& event );
        void SelectSaveFile(wxCommandEvent& event);
        
};

#endif
