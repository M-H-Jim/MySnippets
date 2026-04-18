#include "MyApp.h"


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    SetAppearance(Appearance::System);
    
    Database db("snippets.db");
    db.PrintFolders();
    
    MainFrame *frame = new MainFrame("MySnippets");
    frame->SetClientSize(1200, 600);
    frame->Center();
    frame->Show(true);
    
    return true;
}
