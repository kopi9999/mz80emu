#ifndef ONE_BIT_LABEL
#define ONE_BIT_LABEL

#include <stdint.h>
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <cstdint>

class OneBitLabel : public wxPanel {
    public:
        OneBitLabel(wxWindow* parent, wxString label, uint8_t* registerPointer, uint8_t mask);
        ~OneBitLabel();

    private:
        wxButton* button;
        uint8_t* registerPointer;
        uint8_t mask;

        wxTimer refresherTimer;

        bool GetBitValue();
        void SetButtonColor(bool bitValue);
        void OnClick(wxCommandEvent& event);
        void RefreshValue();

        void OnTimer(wxTimerEvent& event);
};

#endif

/*
class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Zmiana koloru"), isRed(true)
    {
        button = new wxButton(this, wxID_ANY, "Kliknij mnie", wxPoint(50,50), wxSize(150,50));
        button->SetBackgroundColour(*wxRED);

        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    }

private:
    wxButton* button;
    bool isRed;

    void OnButtonClick(wxCommandEvent& event)
    {
        if (isRed)
        {
            button->SetBackgroundColour(*wxGREEN);
        }
        else
        {
            button->SetBackgroundColour(*wxRED);
        }

        isRed = !isRed;
        button->Refresh();
    }
};
*/