#include "Paladin.h"
[STAThreadAttribute]
void Main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    PaladinConfigEditor::Paladin form;
    Application::Run(%form);
}
