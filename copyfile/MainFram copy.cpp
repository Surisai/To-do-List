#include "Task.h"
#include "MainFram.h"
#include "MainFram copy.h"
#include <wx/wx.h>
#include <vector>
#include <string>


MainFrameCopy::MainFrameCopy(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    SetClientSize(wxSize(1000, 600));

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    button = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(375, 250), wxSize(250,100));

    Bind(wxEVT_SIZE, &MainFrameCopy::OnResize, this);
}

void MainFrameCopy::OnResize(wxSizeEvent& event)
{
    wxSize clientSize = GetClientSize();
    wxSize buttonSize(clientSize.GetWidth() * 0.25, clientSize.GetHeight() * 0.1667);
    int buttonX = (clientSize.GetWidth() - buttonSize.GetWidth()) / 2;
    int buttonY = (clientSize.GetHeight() - buttonSize.GetHeight()) / 2;
    button->SetSize(buttonSize);
    button->SetPosition(wxPoint(buttonX, buttonY));
    // Handle resize event if needed
    event.Skip(); // Allow default processing to continue
}