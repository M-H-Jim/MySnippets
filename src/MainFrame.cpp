#include "MainFrame.h"
#include "LeftPanel.h"

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    LeftPanel *p = new LeftPanel(panel);
    
    // binding
    this->Bind(EVT_FOLDER_SELECTED, &MainFrame::OnFolderSelected, this);
    
    
    
    
    
    
    
    
    wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
    s->Add(p, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}

void MainFrame::OnFolderSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    
    wxLogMessage("MainFrame got folder index: %d", index);
}

