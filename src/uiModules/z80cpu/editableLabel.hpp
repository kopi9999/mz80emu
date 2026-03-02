#ifndef EDITABLE_LABEL
#define EDITABLE_LABEL

#include <stdint.h>
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <cstdint>

class EditableLabel : public wxPanel {
    public:
        EditableLabel(wxWindow* parent, uint8_t* registerPointer);
        wxString GetValue();

    private:
        wxStaticText* text;
        wxTextCtrl* edit;
        uint8_t* registerPointer;

        wxTimer refresherTimer;

        void OnClick(wxMouseEvent&);
        void OnCommit(wxCommandEvent&);
        void OnKillFocus(wxFocusEvent&);
        void FinishEdit();
        void OnTimer(wxTimerEvent& event);
};

#endif
