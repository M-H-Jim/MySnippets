#include "MainFrame.h"



MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    leftPanel = new LeftPanel(panel);
    
    // binding
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    middlePanel = new MiddlePanel(panel);

    
    wxBoxSizer *s = new wxBoxSizer(wxHORIZONTAL);
    s->Add(leftPanel, 1, wxEXPAND, 0);
    s->Add(middlePanel, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    middlePanel->LoadSnippetsForFolder(index);
}

