#ifndef TEST_UI_MOD
#define TEST_UI_MOD

#include <stdint.h>
#include <wx/wx.h>

struct Instance {
    uint8_t value;
    char* character;
};

class UiModuleFrame : public wxFrame {
    public:
        UiModuleFrame(void* instance, void** interfaces);

    private:
        struct Instance* instance = NULL;
        void** interfaces = NULL;
};

#endif
