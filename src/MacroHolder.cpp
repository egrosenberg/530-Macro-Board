#include "MacroHolder.h"

/**
 * Constructor
 *
 * @param ID, id of macro
 * @param *keys, pointer to vector of ints corresponding to VK_KEYCODE values
 */
MacroHolder::MacroHolder(int ID, std::vector <int> *keys)
{
    m_ID = ID;
    m_IsActive = true;
    m_KeyBind = keys;

    m_OutputHandler = OutputHandler::getSingleton();
}

// delete member variables from mem
MacroHolder::~MacroHolder()
{
}

/**
 * Check if all keys are held. Call macro if is held
 *
 * @return true if all keys in m_KeyBind are held
 */
bool MacroHolder::checkTrigger()
{
    bool active = true;
    // Verify all keys are held
    for (int & vkCode : *m_KeyBind)
    {
        if (!(GetAsyncKeyState(vkCode) & 0x01))
        {
            active = false;
        }
    }

    // Call Macro
    if (active)
    {
        m_OutputHandler->triggerMacro(m_ID);
    }

    return active;
}

