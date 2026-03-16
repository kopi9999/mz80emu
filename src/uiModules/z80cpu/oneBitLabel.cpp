#include "oneBitLabel.hpp"

OneBitLabel::OneBitLabel(wxWindow* parent, wxString label, uint8_t* registerPointer, uint8_t mask)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize),
    refresherTimer(this)
{
    this->registerPointer = registerPointer;
    this->mask = mask;
    button = new wxButton(this, wxID_ANY, label);
    //button->SetMinSize(wxSize(50, 20));
    SetButtonColor(GetBitValue());

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(button, 1, wxEXPAND | wxALL, 2);
    SetSizer(sizer);

    button->Bind(wxEVT_BUTTON, &OneBitLabel::OnClick, this);
    Bind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
    refresherTimer.Start(250);
}

bool OneBitLabel::GetBitValue() {
    if (*registerPointer & mask) {
        return true;
    }
    return false;
}

void OneBitLabel::SetButtonColor(bool bitValue) {
    if (bitValue) {
        button->SetBackgroundColour(*wxGREEN);
    }
    else {
        button->SetBackgroundColour(*wxRED);
    }
    button->Refresh();
}

void OneBitLabel::OnClick(wxCommandEvent& event) {
    bool newValue = !GetBitValue();
    SetButtonColor(newValue);
}

void OneBitLabel::RefreshValue()
{
    SetButtonColor(GetBitValue());
}

void OneBitLabel::OnTimer(wxTimerEvent& event) {
    RefreshValue();
}

OneBitLabel::~OneBitLabel()
{
    refresherTimer.Stop();
    Unbind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
}