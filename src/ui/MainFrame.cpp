#include "MainFrame.h"
#include "FileOperations.hpp"
#include <wx/wx.h>
#include <filesystem>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    new wxStaticText(this, wxID_ANY, ReturnDirectory(), 
        wxPoint(50, 50)); // (pozycja x=50, y=50)
}