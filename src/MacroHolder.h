#ifndef _MACRO_HOLDER_H_
#define _MACRO_HOLDER_H_

#include "MacroBoard.h"

class MacroHolder
{
private:
    OutputHandler *m_OutputHandler;
    
    std::vector <WORD> *m_KeyBind;
    unsigned int m_ID;
    bool m_IsActive;

public:
    MacroHolder(int ID, std::vector <WORD> *keys);
    virtual ~MacroHolder();

    bool checkTrigger(int last, bool **keybdState, UINT aSize);

    void activate(){m_IsActive = true;}
    void deactivate(){m_IsActive = false;}
    bool checkStatus(){return m_IsActive;}
    int getID(){return m_ID;}
}; 


#endif
