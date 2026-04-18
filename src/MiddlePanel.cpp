#include "MiddlePanel.h"

wxDEFINE_EVENT(EVT_SNIPPET_SELECTED, wxCommandEvent);

MiddlePanel::MiddlePanel(wxWindow *w)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
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
    
    
    snippetList->Append("Personal");
    snippetList->Append("Work");
    snippetList->Append("Ideas");
    snippetList->Append("Archive");
    
    //----------------------
    
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(searchHeaderSizer, 0, wxEXPAND | wxALL, 8);
    topSizer->Add(snippetList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    this->SetSizer(topSizer);
    
    
}


void MiddlePanel::LoadSnippetsForFolder(int folderIndex) {
    snippetList->Clear();
    
    if (folderIndex == 0) {
        snippetList->Append("Personal Snippet 1");
        snippetList->Append("Personal Snippet 2");
    }
    else if (folderIndex == 1) {
        snippetList->Append("Work API Code");
        snippetList->Append("Database Query");
    }
    else if (folderIndex == 2) {
        snippetList->Append("Cool Idea 1");
        snippetList->Append("Startup Concept");
    }
    else {
        snippetList->Append("Old Stuff");
    }
    
}

void MiddlePanel::OnSnippetSelection(wxCommandEvent& event) {
    selectedSnippetIndex = event.GetSelection();
    
    wxCommandEvent evt(EVT_SNIPPET_SELECTED);
    evt.SetInt(selectedSnippetIndex);
    
    wxPostEvent(this, evt);
    wxLogMessage("%d", selectedSnippetIndex);
    
}








