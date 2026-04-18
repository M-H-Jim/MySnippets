#include "MainFrame.h"


MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    middlePanel = new MiddlePanel(panel);
    
    wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
    s->Add(middlePanel, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    middlePanel->Bind(EVT_SNIPPET_SELECTED, &MainFrame::OnSnippetSelected, this);
    
    
}


void MainFrame::OnSnippetSelected(wxCommandEvent& event) {
    int index = event.GetInt();
    
    
    
}


