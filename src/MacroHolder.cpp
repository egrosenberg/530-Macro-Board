#include "MacroHolder.h"

/**
 * Constructor
 *
 * @param ID, id of macro
 * @param *keys, pointer to vector of ints corresponding to VK_KEYCODE values
 */
MacroHolder::MacroHolder(int ID, std::vector <WORD> *keys)
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
bool MacroHolder::checkTrigger(int last)
{
    // if last isn't final key, return false. This way, we are sure that we meant to activate right this call.
    if (last != m_KeyBind->back())
    {
        return false;
    }

    bool active = true;
    // Verify all keys but last are held
    for (auto vkCode = m_KeyBind->begin(); vkCode != m_KeyBind->end(); ++vkCode)
    {
        if (!(GetAsyncKeyState(*vkCode) & 0x01))
        {
            active = false;
        }
        else
        {
            std::cout << *vkCode << std::endl;
        }
    }

    // Call Macro
    if (active)
    {
        m_OutputHandler->triggerMacro(m_ID);
    }

    return active;
}

