#include "Task.h"
#include "MainFram.h"
#include <wx/wx.h>
#include <vector>
#include <string>


MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    CreateControls();
    BindEventHandlers();
    AddSavedTask();
}
void MainFrame::CreateControls()
{
    //create panel
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 24)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    headlineText = new wxStaticText(panel, wxID_ANY, "TO-DO List Application");
    headlineText->SetFont(headlineFont);
    mainSizer->Add(headlineText, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 20);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(0,35), wxTE_PROCESS_ENTER);
    addButton = new wxButton(panel, wxID_ANY, "Add ", wxDefaultPosition, wxSize(100,35));
    inputSizer->Add(inputField, 1, wxRIGHT, 10);
    inputSizer->Add(addButton, 0);
    mainSizer->Add(inputSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    checkListBox  = new wxCheckListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(0, 300));
    mainSizer->Add(checkListBox, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    clearButton = new wxButton(panel, wxID_ANY, "Clear", wxDefaultPosition, wxSize(100, 40));
    buttonSizer->Add(clearButton, 0, wxRIGHT, 10);
   
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 20);

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(panel);
}

void MainFrame::BindEventHandlers()
{
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
    inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnterPressed, this);
    checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);//bind close event
    Bind(wxEVT_SIZE, &MainFrame::OnResize, this);
}


void MainFrame::AddSavedTask()
{
    std::vector<Task> tasks = loadTasksFromFile("tasks.txt");
    for(const Task& task : tasks)//loop through all the loaded tasks
    {
        
        checkListBox->Insert(task.description, checkListBox->GetCount());
        checkListBox->Check(checkListBox->GetCount() - 1, task.done);
    }
}


void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
    AddTaskFromInput();
}

void MainFrame::OnInputEnterPressed(wxCommandEvent& evt)
{
    AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
    switch(evt.GetKeyCode()){
        case WXK_DELETE:
            DeleteSelectedTasks();
            break;
        case WXK_UP:
            MoveSelectedTask(-1);//move selected task up
            break;
        case WXK_DOWN:
            MoveSelectedTask(1);
            break;
    
    }
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& event)
{

    if(checkListBox->IsEmpty()){
        return; // No tasks to clear
    }
    
    wxMessageDialog confirmDialog(this,"Are you sure you want to clear all tasks?", 
        "Confirm Clear", wxYES_NO | wxCANCEL);
   
    int result = confirmDialog.ShowModal();

    if(result == wxID_YES){
        checkListBox->Clear(); // Clear all tasks
    }
    

}

void MainFrame::OnWindowClosed(wxCloseEvent& event)
{
    // You can add any cleanup code here if needed
    event.Skip(); // Allow the window to close
}


void MainFrame::AddTaskFromInput()
{
    //create a new task from the input field
    wxString description = inputField->GetValue();

    if(!description.IsEmpty()){
        checkListBox->Insert(description, checkListBox->GetCount());
        inputField->Clear();//clear the input field after adding the task

    }

    inputField->SetFocus(); //set focus back to the input field
}


void MainFrame::DeleteSelectedTasks()
{
    wxArrayInt selectedIndexes;
    int selectedCount = checkListBox->GetSelections(selectedIndexes);
    for (int i = selectedIndexes.GetCount() - 1; i >= 0; --i) {
        checkListBox->Delete(selectedIndexes[i]);
    }
}

void MainFrame::MoveSelectedTask(int offset)
{
    int selectedIndex = checkListBox->GetSelection();

    if(selectedIndex == wxNOT_FOUND){
        return; //no selection
    }

    int newIndex = selectedIndex + offset;

    if(newIndex >= 0 && newIndex < checkListBox->GetCount()){
        SwapTasks(selectedIndex, newIndex);
        checkListBox->SetSelection(newIndex, true);
    }
}

void MainFrame::SwapTasks(int i, int j)
{
    //task object
    Task taskI;
    taskI.description = checkListBox->GetString(i).ToStdString();
    taskI.done = checkListBox->IsChecked(i);

    Task taskJ;
    taskJ.description = checkListBox->GetString(j).ToStdString();
    taskJ.done = checkListBox->IsChecked(j);

    checkListBox->SetString(i, taskJ.description);
    checkListBox->Check(i, taskJ.done);

    checkListBox->SetString(j, taskI.description);
    checkListBox->Check(j, taskI.done);
}

void MainFrame::OnResize(wxSizeEvent& event)
{
    event.Skip();
}