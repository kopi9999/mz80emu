#include "MainFrame.h"
#include "FileOperations.hpp"
#include <wx/wx.h>
#include <filesystem>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    new wxStaticText(this, wxID_ANY, ReturnDirectory(), 
        wxPoint(50, 50)); // (pozycja x=50, y=50)

        wxButton* button = new wxButton(this, wxID_ANY, "Click Me", wxPoint(200, 30));
    
        // Connect the button click event to the handler
        button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
}

void MainFrame::OnButtonClicked(wxCommandEvent& event) {
    wxMessageBox("Button was clicked!", "Info", wxOK | wxICON_INFORMATION);
    createTextFile("output.txt", "Hello from C++!");
}