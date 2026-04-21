#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    //~ wxColour bgMain(30, 30, 30);
    //~ wxColour bgPanel(40, 40, 40);
    
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
    
    listEditorSplitter->SplitVertically(middlePanel, rightPanel);
    mainSplitter->SplitVertically(leftPanel, listEditorSplitter);
    
    CallAfter([=]()
    {
        mainSplitter->SetSashPosition(180);
        listEditorSplitter->SetSashPosition(220);
    });
    
    mainSplitter->SetSashGravity(0.25);
    listEditorSplitter->SetSashGravity(0.5);
    
    
    
    
    
    
    
    mainSplitter->SetMinimumPaneSize(169);
    listEditorSplitter->SetMinimumPaneSize(150);
    
    
    leftPanel->SetBackgroundColour(wxColour(35,35,35));
    middlePanel->SetBackgroundColour(wxColour(40,40,40));
    rightPanel->SetBackgroundColour(wxColour(45, 45, 45));
        
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(mainSplitter, 1, wxEXPAND | wxALL, 6);
    panel->SetSizer(mainSizer);
    
    
    
    frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(panel, 1, wxEXPAND | wxALL, 6);
    SetSizer(frameSizer);
    
    CreateStatusBar();
    SetStatusText("Welcome to MySnippets!");
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int snippetId = event.GetInt();
    rightPanel->LoadSnippetForTitle(snippetId);
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int folderId = event.GetInt();
    middlePanel->LoadSnippetsTitleForFolder(folderId);
}


