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
    
    public:
        LeftPanel(wxWindow *sw);
};




#endif // LEFTPANEL_H
