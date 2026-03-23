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
        OneBitLabel(wxWindow* parent, wxString labelText, uint8_t* registerPointer, uint8_t mask);
        ~OneBitLabel();

    private:
        wxStaticText* label;
        uint8_t* registerPointer;
        uint8_t mask;

        wxTimer refresherTimer;

        bool GetBitValue();
        void SetLabelColor(bool bitValue);
        void OnClick(wxMouseEvent& event);

        void OnTimer(wxTimerEvent& event);
};

#endif