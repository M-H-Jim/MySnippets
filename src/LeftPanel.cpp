#include "LeftPanel.h"

LeftPanel::LeftPanel(wxWindow *sw)
: wxPanel(sw, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
    
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
    
    
    folderList->Append("Personal");
    folderList->Append("Work");
    folderList->Append("Ideas");
    folderList->Append("Archive");
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
    wxString name = folderList->GetString(selectedFolderIndex);
    
    wxLogMessage("Selected folder: %s", name);
}








