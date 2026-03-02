#include "editableLabel.hpp"

EditableLabel::EditableLabel(wxWindow* parent, uint8_t* registerPointer)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)
{
    this->registerPointer = registerPointer;
    text = new wxStaticText(this, wxID_ANY, wxString::Format("%02X", static_cast<unsigned int>(*registerPointer)));
    edit = new wxTextCtrl(this, wxID_ANY, wxString::Format("%02X", static_cast<unsigned int>(*registerPointer)), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    edit->Hide();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text, 1, wxEXPAND | wxALL, 2);
    sizer->Add(edit, 1, wxEXPAND | wxALL, 2);
    SetSizer(sizer);

    text->Bind(wxEVT_LEFT_DOWN, &EditableLabel::OnClick, this);
    edit->Bind(wxEVT_TEXT_ENTER, &EditableLabel::OnCommit, this);
    edit->Bind(wxEVT_KILL_FOCUS, &EditableLabel::OnKillFocus, this);

    Bind(wxEVT_TIMER, &EditableLabel::OnTimer, this);
    refresherTimer.Start(250);
}

wxString EditableLabel::GetValue() { return text->GetLabel(); }

void EditableLabel::OnClick(wxMouseEvent&)
{
    edit->SetValue(text->GetLabel());
    text->Hide();
    edit->Show();
    edit->SetFocus();
    Layout();
}

void EditableLabel::OnCommit(wxCommandEvent&)
{
    FinishEdit();
}

void EditableLabel::OnKillFocus(wxFocusEvent&)
{
    FinishEdit();
}

void EditableLabel::FinishEdit()
{
    uint hexValue;
    if (edit->GetValue().ToUInt(&hexValue, 16) && hexValue <= 0xFF) {
        *registerPointer = static_cast<uint8_t>(hexValue);
        text->SetLabel(edit->GetValue());
        edit->Hide();
        text->Show();
        Layout();
    }
    else {
        edit->Hide();
        text->Show();
        Layout();
    }
}

void EditableLabel::OnTimer(wxTimerEvent& event) {
    
}