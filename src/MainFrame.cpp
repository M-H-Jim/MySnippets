#include "MainFrame.h"
#include "RightPanel.h"

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title) {
    
    panel = new wxPanel(this);
    
    RightPanel *p = new RightPanel(panel);
    
    wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
    s->Add(p, 1, wxEXPAND);
    panel->SetSizer(s);
    
    
    
}
