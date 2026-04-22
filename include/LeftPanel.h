#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <vector>

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>

#include "Database.h"


wxDECLARE_EVENT(EVT_FOLDER_SELECTED, wxCommandEvent);


namespace LeftPanelIDs {
    enum {
        ID_ADD_FOLDER = wxID_HIGHEST + 1,
        ID_RENAME_FOLDER,
        ID_DELETE_FOLDER
    };
}





struct Folder {
    int id;
    std::string name;
};


class LeftPanel : public wxPanel {
    private:
        
        Database *database;
        
        wxBoxSizer *topSizer;
        wxBoxSizer *folderHeaderSizer;
        
        wxStaticText *folderText;
        wxBitmapButton *addBtn;
        
        std::vector<Folder> folders;
        
        wxListBox *folderList;
        int selectedFolderIndex = -1;
        
        
    public:
        LeftPanel(wxWindow *w, Database *db);
        int GetSelectedFolderIndex() const;
    private:
        void OnFolderSelection(wxCommandEvent& event);
        void OnFolderDClick(wxCommandEvent& event);
        void OnAddBtnClicked(wxCommandEvent& event);
        void OnDeleteFolder(wxCommandEvent& event);
        
        void OnFolderRightClick(wxContextMenuEvent& event);
};




#endif // LEFTPANEL_H
