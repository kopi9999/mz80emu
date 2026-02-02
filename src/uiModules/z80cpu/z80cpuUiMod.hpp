#ifndef Z80_CPU_UI_MOD
#define Z80_CPU_UI_MOD

#include <stdint.h>
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <cstdint>
#include "../uiModuleInternal.hpp"

#include "../../modules/z80cpu/z80cpuMod.h"

enum { ID_MENU_REFRESH = wxID_HIGHEST + 1 };

class UiModulePanel : public wxPanel {
    public:
        UiModulePanel(wxControl* parent, void* instance, void** interfaces);

    private:
        struct Instance* instance = NULL;
        void** interfaces = NULL;

        wxTimer refresherTimer;

        void OnTimer(wxTimerEvent& event);
};

#endif
