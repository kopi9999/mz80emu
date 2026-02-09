#include "editableLabel.hpp"

EditableLabel::EditableLabel(wxWindow* parent, const wxString& value)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)
{
    text = new wxStaticText(this, wxID_ANY, value);
    edit = new wxTextCtrl(this, wxID_ANY, value, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

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
    text->SetLabel(edit->GetValue());
    edit->Hide();
    text->Show();
    Layout();
}