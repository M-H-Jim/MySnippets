#include "MainFrame.h"




MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    db = new Database("snippets.db");
    
    
    leftPanel = new LeftPanel(panel, db);
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    middlePanel = new MiddlePanel(panel, db);
    this->Bind(EVT_SNIPPET_SELECTED, &MainFrame::OnSnippetSelected, this);
    
    rightPanel = new RightPanel(panel, db);
    
    
    wxBoxSizer *s = new wxBoxSizer(wxHORIZONTAL);
    s->Add(leftPanel, 1, wxEXPAND, 0);
    s->Add(middlePanel, 1, wxEXPAND, 0);
    s->Add(rightPanel, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int snippetId = event.GetInt();
    rightPanel->LoadSnippetForTitle(snippetId);
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int folderId = event.GetInt();
    middlePanel->LoadSnippetsTitleForFolder(folderId);
}


