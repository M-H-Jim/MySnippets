#include "LeftPanel.h"

LeftPanel::LeftPanel(wxWindow *w)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
    folderText = new wxStaticText(this, wxID_ANY, "Folder");
    
    // Make the text Bold and bigger
    wxFont boldFont = folderText->GetFont();
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    boldFont.SetPointSize(14);
    folderText->SetFont(boldFont);
    
    addBtn = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_PLUS));
    
    
    folderHeaderSizer = new wxBoxSizer(wxHORIZONTAL);
    folderHeaderSizer->Add(folderText, 1, wxEXPAND | wxALL, 6);
    folderHeaderSizer->Add(addBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 6);
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(folderHeaderSizer, 0, wxEXPAND | wxALL, 8);
    this->SetSizer(topSizer);
    
    
}
