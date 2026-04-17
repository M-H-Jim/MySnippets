#ifndef MIDDLEPANEL_H
#define MIDDLEPANEL_H

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>

class MiddlePanel : public wxPanel {
    private:
        wxBoxSizer *topSizer;
        wxBoxSizer *searchHeaderSizer;
        
        wxSearchCtrl *searchCtrl;
        wxBitmapButton *addBtn;
        
    public:
        MiddlePanel(wxWindow *w);
};

#endif // MIDDLEPANEL_H
