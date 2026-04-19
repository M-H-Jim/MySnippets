#ifndef MIDDLEPANEL_H
#define MIDDLEPANEL_H

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>

#include "Database.h"

wxDECLARE_EVENT(EVT_SNIPPET_SELECTED, wxCommandEvent);



class MiddlePanel : public wxPanel {
    private:
        
        Database *database;
        
        wxBoxSizer *topSizer;
        wxBoxSizer *searchHeaderSizer;
        
        wxSearchCtrl *searchCtrl;
        wxBitmapButton *addBtn;
        
        wxListBox *snippetList;
        int selectedSnippetIndex = -1;
        
    public:
        MiddlePanel(wxWindow *w, Database *db);
        void LoadSnippetsForFolder(int folderId);
    private:
        void OnSnippetSelection(wxCommandEvent& event);
};

#endif // MIDDLEPANEL_H
