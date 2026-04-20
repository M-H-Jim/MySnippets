#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    mainSplitter = new wxSplitterWindow(panel, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE | wxSP_NOBORDER);
        
    listEditorSplitter = new wxSplitterWindow(mainSplitter, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE | 
        wxSP_NOBORDER);
    
    db = new Database("snippets.db");
    
    
    leftPanel = new LeftPanel(mainSplitter, db);
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    middlePanel = new MiddlePanel(listEditorSplitter, db);
    this->Bind(EVT_SNIPPET_SELECTED, &MainFrame::OnSnippetSelected, this);
    
    rightPanel = new RightPanel(listEditorSplitter, db);
    
    
    int width = 800;
    
    listEditorSplitter->SplitVertically(middlePanel, rightPanel, 0);
    mainSplitter->SplitVertically(leftPanel, listEditorSplitter, 0);
    mainSplitter->SetSashGravity(0.25);
    listEditorSplitter->SetSashGravity(0.5);
    
    
    mainSplitter->SetMinimumPaneSize(150);
    listEditorSplitter->SetMinimumPaneSize(150);
    
    leftPanel->SetBackgroundColour(*wxBLACK);
    middlePanel->SetBackgroundColour(*wxBLACK);
    
    
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(mainSplitter, 1, wxEXPAND);
    panel->SetSizer(mainSizer);
    
    
    
    frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(panel, 1, wxEXPAND);
    SetSizer(frameSizer);
    
    
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int snippetId = event.GetInt();
    rightPanel->LoadSnippetForTitle(snippetId);
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int folderId = event.GetInt();
    middlePanel->LoadSnippetsTitleForFolder(folderId);
}


