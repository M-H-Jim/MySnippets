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
    
    
    snippetList->SetBackgroundColour(wxColour(35, 35, 35));
    snippetList->SetForegroundColour(wxColour(220, 220, 220));
    
    //----------------------
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(searchHeaderSizer, 0, wxEXPAND | wxALL, 8);
    topSizer->Add(snippetList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    this->SetSizer(topSizer);
    
    
    
    // Binding----------------------------------------
    
    
    snippetList->Bind(wxEVT_LISTBOX, &MiddlePanel::OnSnippetSelection, this);
    snippetList->Bind(wxEVT_LISTBOX_DCLICK, &MiddlePanel::OnSnippetDClick, this);
    
    snippetList->Bind(wxEVT_CONTEXT_MENU, &MiddlePanel::OnSnippetRightClick, this);
    
    
    addBtn->Bind(wxEVT_BUTTON, &MiddlePanel::OnAddBtnClicked, this);
    
    
    snippetList->Bind(wxEVT_RIGHT_DOWN, [this](wxMouseEvent& event) {
        int item = snippetList->HitTest(event.GetPosition());
        if (item != wxNOT_FOUND) {
            snippetList->SetSelection(item);
        }
        event.Skip();
    });
    
    
    Bind(wxEVT_MENU, &MiddlePanel::OnAddBtnClicked, this,MiddlePanelIDs::ID_ADD_SNIPPET);
    Bind(wxEVT_MENU, &MiddlePanel::OnSnippetDClick, this, MiddlePanelIDs::ID_RENAME_SNIPPET);
    Bind(wxEVT_MENU, &MiddlePanel::OnDeleteSnippet, this, MiddlePanelIDs::ID_DELETE_SNIPPET);
    
    
    
    
    // Binding~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    
}


void MiddlePanel::OnAddBtnClicked(wxCommandEvent& event) {
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


void MiddlePanel::OnSnippetDClick(wxCommandEvent& event) {
    int index = snippetList->GetSelection();
    if (index == wxNOT_FOUND ||
        index >= (int)snippets.size()) {
            return;
    }
    wxString currentName = snippetList->GetString(index);
    
    wxTextEntryDialog dialog(this, "Rename snippet:", "Rename", currentName);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString newName = dialog.GetValue();
        if (newName.IsEmpty()) {
            return;
        }
        
        int id = snippets[index].id;
        
        sqlite3_stmt *stmt;
        const char *sql = "UPDATE snippets SET title = ? WHERE id = ?;";
        
        if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, newName.mb_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, id);
            if(sqlite3_step(stmt) == SQLITE_DONE) {
                sqlite3_finalize(stmt);
                snippets[index].title = newName.ToStdString();
                snippetList->SetString(index, newName);
            }
            else {
                sqlite3_finalize(stmt);
                wxMessageBox("Failed to update database!");
            }
        }
        
    }
}


void MiddlePanel::OnDeleteSnippet(wxCommandEvent& event) {
    int index = snippetList->GetSelection();
    if (index == wxNOT_FOUND ||
        index >= (int)snippets.size()) {
        return;
    }
    
    
    int res = wxMessageBox(
        "Are you sure you want to delete snippet?",
        "confirm Delete",
        wxYES_NO | wxICON_WARNING
    );
    
    if (res != wxYES) {
        return;
    }
    
    int id = snippets[index].id; // currently under mouse
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM snippets WHERE id = ?;";
    
    if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if(sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            snippetList->Delete(index);
            snippets.erase(snippets.begin() + index);
            
            wxCommandEvent evt(wxEVT_MENU);
            evt.SetInt(id);
            wxPostEvent(this, evt);
        }
        else {
            sqlite3_finalize(stmt);
            wxMessageBox("Failed to delete snippet");
        }
    }
}








void MiddlePanel::OnSnippetRightClick(wxContextMenuEvent& event) {
    int index = snippetList->GetSelection();
    if (index < 0 || index >= (int)snippets.size()) {
        return;
    }
    
    wxMenu menu;
    menu.Append(MiddlePanelIDs::ID_ADD_SNIPPET, "New Snippet");
    menu.Append(MiddlePanelIDs::ID_RENAME_SNIPPET, "Rename");
    menu.Append(MiddlePanelIDs::ID_DELETE_SNIPPET, "Delete");
    
    
    PopupMenu(&menu);
    
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
    std::cout << "selectindex: " << selectedSnippetIndex << std::endl;
    
    if (selectedSnippetIndex < 0 || selectedSnippetIndex >= snippets.size()) {
        return;
    }
    
    wxCommandEvent evt(EVT_SNIPPET_SELECTED);
    evt.SetInt(snippets[selectedSnippetIndex].id);
    std::cout << "assign: " << evt.GetInt() << std::endl;
    wxPostEvent(this, evt);
    
}





