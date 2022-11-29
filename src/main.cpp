#include "main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    InputHandler *iHandle = InputHandler::getSingleton(hInstance);
    
    const char *path = (lpCmdLine[0] == NULL) ? DEFAULT_MACRO_PATH : lpCmdLine;
    MacroInterpreter *interpreter = new MacroInterpreter(path);


    MessageBox(NULL, "Press ok to stop", "macros", MB_OK);

    delete iHandle;
    delete interpreter;
    return 0;
}

