#include "oneBitLabel.hpp"

OneBitLabel::OneBitLabel(wxWindow* parent, uint8_t* registerPointer, uint8_t mask)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE),
    refresherTimer(this)
{
    this->registerPointer = registerPointer;
    this->mask = mask;
    text = new wxStaticText(
        this,
        wxID_ANY,
        wxString::Format("%c", GetBitValue()),
        wxDefaultPosition,
        wxDefaultSize,
        wxST_NO_AUTORESIZE
    );

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text, 1, wxEXPAND | wxALL, 2);
    SetSizer(sizer);

    Bind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
    refresherTimer.Start(250);
}

char OneBitLabel::GetBitValue() {
    if (*registerPointer & mask) {
        return '1';
    }
    return '0';
}

void OneBitLabel::Refresh()
{
    wxString newValue = wxString::Format("%c", GetBitValue());

    if (text->GetLabel() != newValue)
        text->SetLabel(newValue);
}

void OneBitLabel::OnTimer(wxTimerEvent& event) {
    Refresh();
}

OneBitLabel::~OneBitLabel()
{
    refresherTimer.Stop();
    Unbind(wxEVT_TIMER, &OneBitLabel::OnTimer, this);
}