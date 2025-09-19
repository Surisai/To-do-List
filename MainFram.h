#pragma once
#include <wx/wx.h>
#include "Task.h"


class MainFrame : public wxFrame{

    public:
    MainFrame(const wxString& title);
    private:

        void CreateControls();//create the UI controls
        void BindEventHandlers();//bind event handlers to the controls
        void AddSavedTask();//add tasks loaded from file to the checklistbox


        void OnAddButtonClicked(wxCommandEvent& event);   //event handler for add button click    
        void OnInputEnterPressed(wxCommandEvent& event);//event handler for enter key press in input field
        void OnListKeyDown(wxKeyEvent& evt);
        void OnClearButtonClicked(wxCommandEvent& event);
        void OnWindowClosed(wxCloseEvent& event);
        void OnResize(wxSizeEvent& event);

        void DeleteSelectedTasks();//function to delete selected tasks
        void AddTaskFromInput();
        void MoveSelectedTask(int offset);//function to move selected task up or down
        void SwapTasks(int i, int j);

        wxPanel* panel;
        wxStaticText* headlineText;
        wxTextCtrl* inputField; 
        wxButton* addButton;
        wxCheckListBox* checkListBox;
        wxButton* clearButton;
        




};