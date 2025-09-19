#include "MainFram.h"
#include "App.h"

// Implementation of App::OnInit
bool MyApp::OnInit()
{
    MainFrame* frame = new MainFrame("To-Do List Application");
    frame->SetClientSize(800, 600);
    frame->Center(); // center the window
    frame->Show();
    return true;
}

// Register the App class with wxWidgets
wxIMPLEMENT_APP(MyApp);