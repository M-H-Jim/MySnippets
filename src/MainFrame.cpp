#include "MainFrame.h"
#include "LeftPanel.h"

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    LeftPanel *p = new LeftPanel(panel);
    
    wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
    s->Add(p, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
}
