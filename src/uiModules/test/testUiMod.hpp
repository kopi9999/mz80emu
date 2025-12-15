#ifndef TEST_UI_MOD
#define TEST_UI_MOD

#include <stdint.h>
#include <wx/wx.h>
#include "../uiModuleInternal.hpp"

struct Instance {
    uint8_t value;
    char* character;
};

class UiModulePanel : public wxPanel {
    public:
        UiModulePanel(wxControl* parent, void* instance, void** interfaces);

    private:
        struct Instance* instance = NULL;
        void** interfaces = NULL;
};

#endif
