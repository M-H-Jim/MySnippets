#ifndef MIDDLEPANEL_H
#define MIDDLEPANEL_H


#include <vector>

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>

#include "Database.h"

wxDECLARE_EVENT(EVT_SNIPPET_SELECTED, wxCommandEvent);



namespace MiddlePanelIDs {
    enum {
        ID_ADD_SNIPPET = wxID_HIGHEST + 10,
        ID_RENAME_SNIPPET,
        ID_DELETE_SNIPPET
    };
}






struct Snippet {
    int id;
    std::string title;
};



class MiddlePanel : public wxPanel {
    private:
        
        Database *database;
        
        wxBoxSizer *topSizer;
        wxBoxSizer *searchHeaderSizer;
        
        wxSearchCtrl *searchCtrl;
        wxBitmapButton *addBtn;
        
        std::vector<Snippet> snippets;
        
        wxListBox *snippetList;
        int selectedSnippetIndex = -1;
        
        int currentFolderId = -1;
        
    public:
        MiddlePanel(wxWindow *w, Database *db);
        void LoadSnippetsTitleForFolder(int folderId);
        int GetSelectedSnippetId();
    private:
        void OnSnippetSelection(wxCommandEvent& event);
        void OnAddBtnClicked(wxCommandEvent& event);
        
        void OnSnippetRightClick(wxContextMenuEvent& event);
        void OnSnippetDClick(wxCommandEvent& event);
        void OnDeleteSnippet(wxCommandEvent& event);
};

#endif // MIDDLEPANEL_H
