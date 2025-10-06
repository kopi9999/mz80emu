#include "MemoryModule.hpp"
#include <wx/sizer.h>

MemoryModule::MemoryModule(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    
}

class MemoryModuleUp:public wxApp
{
    public:bool OnInit() override;
};

wxIMPLEMENT_APP_CONSOLE(MemoryModuleUp);
bool MemoryModuleUp::OnInit(){
    MemoryModule* Frame = new MemoryModule("MemoryModule"); 
    Frame->Show();
    return true;
}