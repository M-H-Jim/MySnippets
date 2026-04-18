#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "MiddlePanel.h"


class MainFrame : public wxFrame {
    private:
        wxPanel *panel;
        MiddlePanel *middlePanel;
    public:
        MainFrame (const wxString& title);
        void OnSnippetSelected(wxCommandEvent& event);
};




#endif // MAINFRAME_H
