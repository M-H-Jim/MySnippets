#include "MiddlePanel.h"

MiddlePanel::MiddlePanel(wxWindow *w)
: wxPanel(w, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    
    searchCtrl = new wxSearchCtrl(this, wxID_ANY, "", wxDefaultPosition,
        wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    searchCtrl->ShowSearchButton(true);
    searchCtrl->ShowCancelButton(true);
    
    addBtn = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_PLUS));
    
    
    searchHeaderSizer = new wxBoxSizer(wxHORIZONTAL);
    searchHeaderSizer->Add(searchCtrl, 1, wxEXPAND | wxALL, 6);
    searchHeaderSizer->Add(addBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 6);
    
    
    topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(searchHeaderSizer, 0, wxEXPAND | wxALL, 8);
    this->SetSizer(topSizer);
    
    
}
