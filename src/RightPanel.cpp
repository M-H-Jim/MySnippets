#include "RightPanel.h"

RightPanel::RightPanel(wxWindow *w, Database *db)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER), 
  database(db) {
    
    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
    false, "Cascadia Code");
    
    //~ snippetName = new wxTextCtrl(this, wxID_ANY, "this is a text",
    //~ wxDefaultPosition, wxSize(-1, 35));
    //~ snippetName->SetFont(font);
    
    editor = new wxStyledTextCtrl(this, wxID_ANY);
    editor->StyleSetFont(wxSTC_STYLE_DEFAULT, font);
    editor->SetText("using namespace std");
    
    // set different colour styles
    editor->StyleClearAll();
    
    
    // temp lexer
    editor->SetLexer(wxSTC_LEX_CPP);
    
    
    
    
    
    editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(220, 220, 220));
    editor->SetSelBackground(true, wxColour(60, 60, 60));
    editor->SetSelForeground(true, wxColour(255, 255, 255));
    
    
    
    //-----------------------------------------------
    
    // Keywords
    editor->StyleSetForeground(wxSTC_C_WORD, wxColour(80, 160, 255));
    editor->StyleSetBold(wxSTC_C_WORD, true);

    // Strings
    editor->StyleSetForeground(wxSTC_C_STRING, wxColour(220, 120, 120));
    editor->StyleSetForeground(wxSTC_C_CHARACTER, wxColour(220, 120, 120));

    // Comments
    editor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(0, 180, 0));
    editor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(0, 180, 0));
    editor->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(0, 140, 0));

    // Numbers
    editor->StyleSetForeground(wxSTC_C_NUMBER, wxColour(255, 200, 0));

    // Preprocessor
    editor->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(200, 200, 0));

    // Operators
    editor->StyleSetForeground(wxSTC_C_OPERATOR, wxColour(180, 180, 180));

    // Default text
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(220, 220, 220));
    
    //-----------------------------------------------

    
    
    
    // caret stuff
    editor->SetCaretForeground(wxColour(255, 255, 255));
    editor->SetCaretWidth(2);
    editor->SetCaretLineVisible(true);
    editor->SetCaretLineBackground(wxColour(40, 40, 40));
    
    // line number stuff
    editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    editor->SetMarginWidth(0, 30);
    editor->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(150, 150, 150));
    editor->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(50, 50, 50));
    editor->SetEdgeMode(wxSTC_EDGE_NONE);
    
    
    
    editor->Bind(wxEVT_STC_ZOOM, [=](wxStyledTextEvent&) {
        int lineCount = editor->GetLineCount();
        int digits = 1;
        while (lineCount >= 10) {
            lineCount /= 10;
            digits++;
        }
        wxString sample(digits, '9');
        int width = editor->TextWidth(wxSTC_STYLE_LINENUMBER, sample);
        editor->SetMarginWidth(0, width + 10);
    });
    
    
    
    
    
    
    
    
    editor->SetUseHorizontalScrollBar(false);
    editor->SetWrapMode(wxSTC_WRAP_WORD);
    editor->SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_END);
    editor->SetWrapVisualFlagsLocation(wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT);
    
    
    
    editor->SetScrollWidthTracking(true);
    editor->SetEndAtLastLine(false);
    
    
    
    
    // indent stuff
    editor->SetUseTabs(false);
    editor->SetTabWidth(4);
    editor->SetIndent(4);
    
    
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    //~ topSizer->Add(snippetName, 0, wxEXPAND | wxALL, 8);
    topSizer->Add(editor, 1, wxEXPAND | wxALL, 8);
    this->SetSizer(topSizer);
    
}


wxStyledTextCtrl* RightPanel::GetEditor() {
    return editor;
}

void RightPanel::LoadSnippetForTitle(int snippetId) {
    const char *sql = "SELECT content FROM snippets WHERE id = ?";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, snippetId);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *content = (const char *)sqlite3_column_text(stmt, 0);
            editor->SetText(content);
            editor->EmptyUndoBuffer();
            editor->SetSavePoint();
        }
    }
    
    sqlite3_finalize(stmt);
}












