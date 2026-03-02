#include "editableLabel.hpp"

EditableLabel::EditableLabel(wxWindow* parent, uint8_t* registerPointer)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)
{
    this->registerPointer = registerPointer;
    text = new wxStaticText(this, wxID_ANY, registerPointer);
    edit = new wxTextCtrl(this, wxID_ANY, registerPointer, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    edit->Hide();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text, 1, wxEXPAND | wxALL, 2);
    sizer->Add(edit, 1, wxEXPAND | wxALL, 2);
    SetSizer(sizer);

    text->Bind(wxEVT_LEFT_DOWN, &EditableLabel::OnClick, this);
    edit->Bind(wxEVT_TEXT_ENTER, &EditableLabel::OnCommit, this);
    edit->Bind(wxEVT_KILL_FOCUS, &EditableLabel::OnKillFocus, this);
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
    if (edit->GetValue().Length() == 1) {
        *registerPointer = static_cast<uint8_t>(edit->GetValue()[0]);
        text->SetLabel(registerPointer);
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