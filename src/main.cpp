#include "main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    InputHandler *iHandle = InputHandler::getSingleton(hInstance);
    
    const char *path = DEFAULT_MACRO_PATH;
    MacroInterpreter *interpreter = new MacroInterpreter(path);


    MessageBox(NULL, "Press OK to stop logging.", "Information", MB_OK);

    delete iHandle;
    delete interpreter;
    return 0;
}

