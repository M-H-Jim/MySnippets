#include "RightPanel.h"

RightPanel::RightPanel(wxWindow *w)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
    false, "Cascadia Code");
    
    snippetName = new wxTextCtrl(this, wxID_ANY, "this is a text",
    wxDefaultPosition, wxSize(-1, 35));
    snippetName->SetFont(font);
    
    editor = new wxStyledTextCtrl(this, wxID_ANY);
    editor->StyleSetFont(wxSTC_STYLE_DEFAULT, font);
    editor->SetText("using namespace std");
    
    // set different colour styles
    editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(220, 220, 220));
    editor->StyleClearAll();
    editor->SetSelBackground(true, wxColour(60, 60, 60));
    editor->SetSelForeground(true, wxColour(255, 255, 255));
    
    // caret stuff
    editor->SetCaretForeground(wxColour(255, 255, 255));
    editor->SetCaretWidth(2);
    editor->SetCaretLineVisible(true);
    editor->SetCaretLineBackground(wxColour(40, 40, 40));
    
    // line number stuff
    editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    editor->SetMarginWidth(0, 40);
    editor->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(150, 150, 150));
    editor->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(50, 50, 50));
    editor->SetEdgeMode(wxSTC_EDGE_NONE);
    
    
    editor->SetUseHorizontalScrollBar(false);
    editor->SetWrapMode(wxSTC_WRAP_WORD);
    editor->SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_END);
    editor->SetWrapVisualFlagsLocation(wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT);
    
    
    
    
    
    
    editor->SetScrollWidthTracking(true);
    editor->SetEndAtLastLine(false);
    
    
    
    
    
    editor->SetUseTabs(false);
    editor->SetTabWidth(4);
    editor->SetIndent(4);
    
    
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(snippetName, 0, wxEXPAND | wxALL, 0);
    topSizer->Add(editor, 1, wxEXPAND | wxALL, 0);
    this->SetSizer(topSizer);
    
}
