#include "MainFrame.h"


MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    MiddlePanel *p = new MiddlePanel(panel);
    
    wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
    s->Add(p, 1, wxEXPAND, 0);
    panel->SetSizer(s);
    
    
    
    
}
