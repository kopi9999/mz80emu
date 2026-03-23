#include "oneBitLabel.hpp"

OneBitLabel::OneBitLabel(wxWindow* parent, wxString labelText, uint8_t* registerPointer, uint8_t mask)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE),
    refresherTimer(this)
{
    this->registerPointer = registerPointer;
    this->mask = mask;
    label = new wxStaticText(
        this,
        wxID_ANY,
        labelText,
        wxDefaultPosition,
        wxDefaultSize,
        wxST_NO_AUTORESIZE
    );

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(label, 0, wxEXPAND | wxALL, 2);
    SetSizer(sizer);
    
    label->Bind(wxEVT_LEFT_DOWN, &OneBitLabel::OnClick, this);
    Bind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
    refresherTimer.Start(250);
}

bool OneBitLabel::GetBitValue() {
    if (*registerPointer & mask) {
        return true;
    }
    return false;
}

void OneBitLabel::SetLabelColor(bool bitValue) {
    if (bitValue) {
        label->SetBackgroundColour(*wxGREEN);
    }
    else {
        label->SetBackgroundColour(*wxRED);
    }
    label->Refresh();
}

void OneBitLabel::OnClick(wxMouseEvent& event) {
    *registerPointer = *registerPointer xor mask;
    SetLabelColor(GetBitValue());
}

void OneBitLabel::OnTimer(wxTimerEvent& event) {
    SetLabelColor(GetBitValue());
}

OneBitLabel::~OneBitLabel()
{
    refresherTimer.Stop();
    Unbind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
}