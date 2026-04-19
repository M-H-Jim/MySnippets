#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <vector>

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>

#include "Database.h"


wxDECLARE_EVENT(EVT_FOLDER_SELECTED, wxCommandEvent);


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
        
};




#endif // LEFTPANEL_H
