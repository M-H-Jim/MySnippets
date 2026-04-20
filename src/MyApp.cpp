#include "MyApp.h"


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    SetAppearance(Appearance::System);
    
    MainFrame *frame = new MainFrame("MySnippets");
    frame->SetClientSize(1200, 600);
    frame->Center();
    frame->Show(true);
    
    return true;
}
