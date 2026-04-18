#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>

class RightPanel : public wxPanel {
    private:
        wxBoxSizer *topSizer;
        
        wxTextCtrl *snippetName;
        wxStyledTextCtrl *editor;
        
        
        
    public:
        RightPanel(wxWindow *w);
        wxStyledTextCtrl* GetEditor();
};






#endif // RIGHTPANEL_H
