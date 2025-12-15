#ifndef MAINWX
#define MAINWX

#include <wx/wx.h>
#include <wx/evtloop.h>
#include <wx/msgdlg.h>
#include <wx/defs.h>

typedef class wxPanel* (*getPanel)(wxControl*, void*, void**);
typedef Error (*getUiName) (char*, uint32_t);

struct UiModules {
    std::vector<std::string> names;
    uint16_t count;
    void** pointers;
    getPanel* getPanelFuncs;
    getUiName* getNameFuncs;
};

struct UiInstanceInfo {
    uint32_t count;
    uint32_t* uiInstanceList;
    uint32_t* instanceList;
    uint32_t* interfaceArrayList;
};

#endif