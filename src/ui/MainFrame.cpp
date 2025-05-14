#include "MainFrame.h"
#include "FileOperations.hpp"
#include <wx/wx.h>
#include <filesystem>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    wxTextValidator validator(wxFILTER_DIGITS);

    new wxStaticText(this, wxID_ANY, ReturnDirectory(), wxPoint(50, 50)); // (pozycja x=50, y=50)

    numberInput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(200, 20), wxSize(200, 30), 0, validator);

    wxButton* button = new wxButton(this, wxID_ANY, "Click Me", wxPoint(200, 70));
    
    // Connect the button click event to the handler
    button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
}

void MainFrame::OnButtonClicked(wxCommandEvent& event) {
    wxString val = numberInput->GetValue();

    wxMessageBox("Button was clicked!" + val, "Info", wxOK | wxICON_INFORMATION);
    createTextFile("output.txt" , "Hello from C++! ");
}