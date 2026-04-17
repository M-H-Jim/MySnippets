#include "RightPanel.h"

RightPanel::RightPanel(wxWindow *w)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
    snippetName = new wxTextCtrl(this, wxID_ANY, "this is a text");
    
    
    editor = new wxStyledTextCtrl(this, wxID_ANY);
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(snippetName, 0, wxEXPAND | wxALL, 5);
    topSizer->Add(editor, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(topSizer);
    
}
