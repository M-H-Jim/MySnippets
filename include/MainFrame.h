#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "LeftPanel.h"
#include "MiddlePanel.h"
#include "RightPanel.h"


class MainFrame : public wxFrame {
    private:
        wxPanel *panel;
        
        wxSplitterWindow *mainSplitter;
        wxSplitterWindow *listEditorSplitter;
        
        LeftPanel *leftPanel;
        MiddlePanel *middlePanel;
        RightPanel *rightPanel;
        
        wxBoxSizer *mainSizer;
        wxBoxSizer *frameSizer;
        
    public:
        MainFrame (const wxString& title);
};




#endif // MAINFRAME_H
