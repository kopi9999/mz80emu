#include "editableLabel.hpp"

EditableLabel::EditableLabel(wxWindow* parent, uint8_t* registerPointer)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE),
    refresherTimer(this)
{
    this->registerPointer = registerPointer;
    text = new wxStaticText(
        this,
        wxID_ANY,
        wxString::Format("%02X", static_cast<unsigned int>(*registerPointer)),
        wxDefaultPosition,
        wxDefaultSize,
        wxST_NO_AUTORESIZE
    );
    edit = new wxTextCtrl(this, wxID_ANY, wxString::Format("%02X", static_cast<unsigned int>(*registerPointer)), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    edit->Hide();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text, 1, wxEXPAND | wxALL, 2);
    sizer->Add(edit, 1, wxEXPAND | wxALL, 2);
    SetSizer(sizer);

    text->Bind(wxEVT_LEFT_DOWN, &EditableLabel::OnClick, this);
    edit->Bind(wxEVT_TEXT_ENTER, &EditableLabel::OnCommit, this);
    edit->Bind(wxEVT_KILL_FOCUS, &EditableLabel::OnKillFocus, this);
    edit->Bind(wxEVT_KEY_DOWN, &EditableLabel::OnKeyDown, this);

    Bind(wxEVT_TIMER, &EditableLabel::OnTimer, this);
    refresherTimer.Start(250);
}

wxString EditableLabel::GetValue() { return text->GetLabel(); }

void EditableLabel::OnClick(wxMouseEvent& event)
{
    isEditing = true;
    edit->SetValue(text->GetLabel());
    text->Hide();
    edit->Show();
    edit->SetFocus();
    Layout();
}

void EditableLabel::OnCommit(wxCommandEvent& event)
{
    SaveEdit();
}

void EditableLabel::OnKillFocus(wxFocusEvent& event)
{
    CancelEdit();
    event.Skip();
}

void EditableLabel::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_ESCAPE) {
        CancelEdit();
    }
    else {
        event.Skip();
    }
}

void EditableLabel::SaveEdit()
{
    uint hexValue;
    if (edit->GetValue().ToUInt(&hexValue, 16) && hexValue <= 0xFF) {
        isEditing = false;
        *registerPointer = static_cast<uint8_t>(hexValue);
        text->SetLabel(edit->GetValue());
        edit->Hide();
        text->Show();
        Layout();
    }
    else {
        CancelEdit();
    }
}

void EditableLabel::CancelEdit()
{
    isEditing = false;
    edit->Hide();
    text->Show();
    Layout();
}

void EditableLabel::Refresh()
{
    if (isEditing)
        return;

    wxString newValue = wxString::Format("%02X", (unsigned int)*registerPointer);

    if (text->GetLabel() != newValue)
        text->SetLabel(newValue);
}

void EditableLabel::OnTimer(wxTimerEvent& event) {
    Refresh();
}

EditableLabel::~EditableLabel()
{
    refresherTimer.Stop();
    Unbind(wxEVT_TIMER, &EditableLabel::OnTimer, this);
}