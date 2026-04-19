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
    
    
    // Bindings ~~~~~~~~~~~~~~~~~~~~~~~~
     
}

int LeftPanel::GetSelectedFolderIndex() const {
    return selectedFolderIndex;
}

void LeftPanel::OnFolderSelection(wxCommandEvent& event) {
    selectedFolderIndex = event.GetSelection();
    
    wxCommandEvent evt(EVT_FOLDER_SELECTED);
    evt.SetInt(folders[selectedFolderIndex].id);
    
    wxPostEvent(this, evt);
    
}








