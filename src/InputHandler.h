#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "MacroBoard.h"
#include <iostream>
#include <algorithm>

class InputHandler
{
private:
    static InputHandler *m_SingletonInstance;
    
    bool *m_KeyHeld;
    std::vector <MacroHolder> *m_MacroHolders;
    HHOOK m_keyPressHook;

    static LRESULT CALLBACK staticKeyHook(int nCode, WPARAM wParam, LPARAM lParam);
    LRESULT keyHook(int nCode, WPARAM wParam, LPARAM lParam);
public:
    InputHandler(HINSTANCE hInstance);
    virtual ~InputHandler();

    static InputHandler *getSingleton(HINSTANCE hInstance = NULL);

    int addMacro(int ID, INPUT **inputs);
    void releaseHook(int ID);
};

#endif
