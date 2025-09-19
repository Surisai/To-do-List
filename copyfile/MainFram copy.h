#pragma once
#include <wx/wx.h>
#include "Task.h"

class MainFrameCopy : public wxFrame{

    public:
    MainFrameCopy(const wxString& title);
    private:

        wxButton* button;
        void OnResize(wxSizeEvent& event);

};