#include "main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // Get our InputHandler
    InputHandler *iHandle = InputHandler::getSingleton(hInstance);

    std::vector <int> *keys = new std::vector<int>();
    keys->push_back(VK_LCONTROL);
    keys->push_back(VK_LMENU);
    keys->push_back(0x42);

    iHandle->addMacro(0, keys);

    MessageBox(NULL, "Ignore this.", "test", MB_OK);

    delete iHandle;
 
    return 0;
}

