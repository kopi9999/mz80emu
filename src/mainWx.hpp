#ifndef MAINWX
#define MAINWX

#include <wx/wx.h>
#include <wx/evtloop.h>
#include <wx/msgdlg.h>
#include <wx/defs.h>

typedef class wxFrame* (*getFrame)(void*, void**);

struct UiModules {
    std::vector<std::string> names;
    uint16_t count;
    void** pointers;
    getFrame* getFrameFuncs;
};

struct UiInstanceInfo {
    uint32_t count;
    uint32_t* uiInstanceList;
    uint32_t* instanceList;
    uint32_t* interfaceArrayList;
};

#endif