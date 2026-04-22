#include "LeftPanel.h"

wxDEFINE_EVENT(EVT_FOLDER_SELECTED, wxCommandEvent);



LeftPanel::LeftPanel(wxWindow *w, Database *db)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER), 
  database(db) {
    
    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL, false, "Cascadia Code");
    
    
    folderText = new wxStaticText(this, wxID_ANY, "Folder");
    folderText->SetFont(font);
    
    
    
    addBtn = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_PLUS));
    addBtn->SetBackgroundColour(wxColour(35, 35, 35));
    
    folderHeaderSizer = new wxBoxSizer(wxHORIZONTAL);
    folderHeaderSizer->Add(folderText, 1, wxEXPAND | wxALL, 6);
    folderHeaderSizer->Add(addBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 6);
    
    //experimental------------------------
    folderList = new wxListBox(this, wxID_ANY);
    folderList->SetFont(font);
    
    folderList->SetBackgroundColour(wxColour(35, 35, 35));
    folderList->SetForegroundColour(wxColour(220, 220, 220));
    
    
    //sql enters
    
    const char *sql = "SELECT id, name FROM folders;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char *name = (const char *)sqlite3_column_text(stmt, 1);
            folderList->Append(name);
            folders.push_back({id, name});
        }
    }
    
    sqlite3_finalize(stmt);
    
    
    
    
    
    
    
    
    // sql ends
    
    
    
    
    
    
    
    // ------------------------------
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(folderHeaderSizer, 0, wxEXPAND | wxALL, 8);
    topSizer->Add(folderList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    this->SetSizer(topSizer);
    
    
    
    
    
    
    
    // Bindings ~~~~~~~~~~~~~~~~~~~~~~~~
    
    folderList->Bind(wxEVT_LISTBOX, &LeftPanel::OnFolderSelection, this);
    folderList->Bind(wxEVT_LISTBOX_DCLICK, &LeftPanel::OnFolderDClick, this);
    
    folderList->Bind(wxEVT_CONTEXT_MENU, &LeftPanel::OnFolderRightClick, this);
    
    addBtn->Bind(wxEVT_BUTTON, &LeftPanel::OnAddBtnClicked, this);
    
    
    folderList->Bind(wxEVT_RIGHT_DOWN, [this](wxMouseEvent& event) {
        int item = folderList->HitTest(event.GetPosition());
        if (item != wxNOT_FOUND) {
            folderList->SetSelection(item);
        }
        event.Skip();
    });
    
    
    Bind(wxEVT_MENU, &LeftPanel::OnAddBtnClicked, this, LeftPanelIDs::ID_ADD_FOLDER);
    Bind(wxEVT_MENU, &LeftPanel::OnFolderDClick, this, LeftPanelIDs::ID_RENAME_FOLDER);
    Bind(wxEVT_MENU, &LeftPanel::OnDeleteFolder, this, LeftPanelIDs::ID_DELETE_FOLDER);
    
    
    
    
    // Bindings ~~~~~~~~~~~~~~~~~~~~~~~~
     
}

int LeftPanel::GetSelectedFolderIndex() const {
    return selectedFolderIndex;
}

void LeftPanel::OnFolderSelection(wxCommandEvent& event) {
    selectedFolderIndex = event.GetSelection();
    
    if (selectedFolderIndex == wxNOT_FOUND ||
        selectedFolderIndex >= (int)folders.size()) {
            return;
      }
    
    wxCommandEvent evt(EVT_FOLDER_SELECTED);
    evt.SetInt(folders[selectedFolderIndex].id);
    
    wxPostEvent(this, evt);
    
}

void LeftPanel::OnFolderDClick(wxCommandEvent& event) {
    int index = folderList->GetSelection();
    if (index == wxNOT_FOUND ||
        index >= (int)folders.size()) {
            return;
    }
    wxString currentName = folderList->GetString(index);
    
    wxTextEntryDialog dialog(this, "Rename folder:", "Rename", currentName);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString newName = dialog.GetValue();
        if (newName.IsEmpty()) {
            return;
        }
        
        int id = folders[index].id;
        
        sqlite3_stmt *stmt;
        const char *sql = "UPDATE folders SET name = ? WHERE id = ?;";
        
        if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, newName.mb_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, id);
            if(sqlite3_step(stmt) == SQLITE_DONE) {
                sqlite3_finalize(stmt);
                folders[index].name = newName.ToStdString();
                folderList->SetString(index, newName);
            }
            else {
                sqlite3_finalize(stmt);
                wxMessageBox("Failed to update database!");
            }
        }
        
    }
}



void LeftPanel::OnAddBtnClicked(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter new folder name:", "New Folder");
    if (dialog.ShowModal() == wxID_OK) {
        wxString folderName = dialog.GetValue();
        if (!folderName.IsEmpty()) {
            folderList->Append(folderName);
            
            sqlite3_stmt *stmt;
            const char *sql = "INSERT INTO folders (name) VALUES (?);";
            sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, folderName.mb_str(), -1, SQLITE_TRANSIENT);
            if(sqlite3_step(stmt) == SQLITE_DONE) {
                sqlite3_finalize(stmt);
                int newId = sqlite3_last_insert_rowid(database->Get());
                folders.push_back({newId, folderName.ToStdString()});
            }
            else {
                sqlite3_finalize(stmt);
                wxMessageBox("Failed to add new folder");
            }
        }
    }
}

void LeftPanel::OnDeleteFolder(wxCommandEvent& event) {
    int index = folderList->GetSelection();
    if (index == wxNOT_FOUND ||
        index >= (int)folders.size()) {
        return;
    }
    
    
    int res = wxMessageBox(
        "Are you sure you want to delete this folder?\nAll it's snippets will also be deleted FOREVER.",
        "confirm Delete",
        wxYES_NO | wxICON_WARNING
    );
    
    if (res != wxYES) {
        return;
    }
    
    int id = folders[index].id;
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM folders WHERE id = ?;";
    
    if (sqlite3_prepare_v2(database->Get(), sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if(sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            folderList->Delete(index);
            folders.erase(folders.begin() + index);
        }
        else {
            sqlite3_finalize(stmt);
            wxMessageBox("Failed to delete folder");
        }
    }
}

void LeftPanel::OnFolderRightClick(wxContextMenuEvent& event) {
    
    int index = folderList->GetSelection();
    if (index < 0 || index >= (int)folders.size()) {
        return;
    }
    
    
    wxMenu menu;
    menu.Append(LeftPanelIDs::ID_ADD_FOLDER, "New Folder");
    menu.Append(LeftPanelIDs::ID_RENAME_FOLDER, "Rename");
    menu.Append(LeftPanelIDs::ID_DELETE_FOLDER, "Delete");
    
    
    PopupMenu(&menu);
}








