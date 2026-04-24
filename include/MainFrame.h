#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "LeftPanel.h"
#include "MiddlePanel.h"
#include "RightPanel.h"

#include "Database.h"


class MainFrame : public wxFrame {
    private:
        wxPanel *panel;
        
        
        wxSplitterWindow *mainSplitter;
        wxSplitterWindow *listEditorSplitter;
        
        Database *db;
        
        LeftPanel *leftPanel;
        MiddlePanel *middlePanel;
        RightPanel *rightPanel;
        
        wxBoxSizer *mainSizer;
        wxBoxSizer *frameSizer;
        
    public:
        MainFrame (const wxString& title);
    private:
        void OnFolderSelected(wxCommandEvent& event);
        void OnSnippetSelected(wxCommandEvent& event);
        void OnSnippetDeleted(wxCommandEvent& event);
};




#endif // MAINFRAME_H
