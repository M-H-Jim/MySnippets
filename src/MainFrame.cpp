#include "MainFrame.h"



MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    leftPanel = new LeftPanel(panel);
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    middlePanel = new MiddlePanel(panel);
    this->Bind(EVT_SNIPPET_SELECTED, &MainFrame::OnSnippetSelected, this);

    
    wxBoxSizer *s = new wxBoxSizer(wxHORIZONTAL);
    s->Add(leftPanel, 1, wxEXPAND, 0);
    s->Add(middlePanel, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    
    
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    middlePanel->LoadSnippetsForFolder(index);
}


