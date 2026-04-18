#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>

class LeftPanel : public wxPanel {
    private:
        wxBoxSizer *topSizer;
        wxBoxSizer *folderHeaderSizer;
        
        wxStaticText *folderText;
        wxBitmapButton *addBtn;
        
        wxListBox *folderList;
        int selectedFolderIndex = -1;
        
    
    public:
        LeftPanel(wxWindow *sw);
        int GetSelectedFolderIndex() const;
    private:
        void OnFolderSelection(wxCommandEvent& event);
        
};




#endif // LEFTPANEL_H
