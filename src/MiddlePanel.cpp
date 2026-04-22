#include "MiddlePanel.h"

wxDEFINE_EVENT(EVT_SNIPPET_SELECTED, wxCommandEvent);

MiddlePanel::MiddlePanel(wxWindow *w, Database *db)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER), 
  database(db) {
    
    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL, false, "Cascadia Code");
    
    
    
    searchCtrl = new wxSearchCtrl(this, wxID_ANY, "", wxDefaultPosition,
        wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    searchCtrl->ShowSearchButton(true);
    searchCtrl->ShowCancelButton(true);
    searchCtrl->SetFont(font);
    
    
    addBtn = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_PLUS));
    addBtn->SetBackgroundColour(wxColour(35, 35, 35));
    
    
    
    searchHeaderSizer = new wxBoxSizer(wxHORIZONTAL);
    searchHeaderSizer->Add(searchCtrl, 1, wxEXPAND | wxALL, 6);
    searchHeaderSizer->Add(addBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 6);
    
    // experimental------------
    snippetList = new wxListBox(this, wxID_ANY);
    snippetList->SetFont(font);
    
    snippetList->Bind(wxEVT_LISTBOX, &MiddlePanel::OnSnippetSelection, this);
    
    snippetList->SetBackgroundColour(wxColour(35, 35, 35));
    snippetList->SetForegroundColour(wxColour(220, 220, 220));
    
    //----------------------
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(searchHeaderSizer, 0, wxEXPAND | wxALL, 8);
    topSizer->Add(snippetList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    this->SetSizer(topSizer);
    
    
    
    // Binding----------------------------------------
    
    addBtn->Bind(wxEVT_BUTTON, &MiddlePanel::OnAddSnippet, this);
    
    
    
    // Binding~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    
}


void MiddlePanel::OnAddSnippet(wxCommandEvent& event) {
    if (currentFolderId == -1) {
        return;
    }
    
    wxTextEntryDialog dialog(this, "Enter snippet name:", "New Snippet");
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString title = dialog.GetValue();
        
        const char *sql = "INSERT INTO snippets (folder_id, title, content) VALUES (?, ?, '')";
        sqlite3_stmt *stmt;
        
        if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, currentFolderId);
            sqlite3_bind_text(stmt, 2, title.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);
        LoadSnippetsTitleForFolder(currentFolderId);
    }
}




void MiddlePanel::LoadSnippetsTitleForFolder(int folderId) {
    
    currentFolderId = folderId;
    
    snippetList->Clear();
    snippets.clear();
    
    const char *sql = "SELECT id, title FROM snippets WHERE folder_id = ?";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, folderId);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char *title = (const char *)sqlite3_column_text(stmt, 1);
            snippetList->Append(title);
            snippets.push_back({id, title});
        }
    }
    sqlite3_finalize(stmt);
}

void MiddlePanel::OnSnippetSelection(wxCommandEvent& event) {
    selectedSnippetIndex = event.GetSelection();
    
    if (selectedSnippetIndex < 0 || selectedSnippetIndex >= snippets.size()) {
        return;
    }
    
    wxCommandEvent evt(EVT_SNIPPET_SELECTED);
    evt.SetInt(snippets[selectedSnippetIndex].id);
    
    wxPostEvent(this, evt);
    
}









