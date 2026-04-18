#include "MainFrame.h"




MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    leftPanel = new LeftPanel(panel);
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    middlePanel = new MiddlePanel(panel);
    this->Bind(EVT_SNIPPET_SELECTED, &MainFrame::OnSnippetSelected, this);
    
    rightPanel = new RightPanel(panel);
    
    
    wxBoxSizer *s = new wxBoxSizer(wxHORIZONTAL);
    s->Add(leftPanel, 1, wxEXPAND, 0);
    s->Add(middlePanel, 1, wxEXPAND, 0);
    s->Add(rightPanel, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    if (index == 0) {
        rightPanel->GetEditor()->SetText("int main() {\n return 0\n}");
    }
    else if (index == 1) {
        rightPanel->GetEditor()->SetText("SELECT * FROM users;");
    }
    else {
        rightPanel->GetEditor()->SetText("It works!!!!!!!");
    }
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    middlePanel->LoadSnippetsForFolder(index);
}


