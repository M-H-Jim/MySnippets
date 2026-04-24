#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>

#include "Database.h"

class RightPanel : public wxPanel {
    private:
        wxBoxSizer *topSizer;
        
        //~ wxTextCtrl *snippetName;
        wxStyledTextCtrl *editor;
        
        Database *database;
        
        int currentSnippetId = -1;
        
    public:
        RightPanel(wxWindow *w, Database *db);
        wxStyledTextCtrl* GetEditor();
        void LoadSnippetForTitle(int snippetId);
        void SetCurrentSnippetId(int Id);
        int GetCurrentSnippetId();
};






#endif // RIGHTPANEL_H
