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
    for (auto & key : *m_KeyBind)
    {
        std::cout << key << ' ';
    }
    std::cout << '\n';
}

// delete member variables from mem
MacroHolder::~MacroHolder()
{
}

/**
 * Check if all keys are held. Call macro if is held
 *
 * @param last, virtual-key code of most recent keypress
 * @param keybdState, pointer to array of bools containing keyboard state
 * @param aSize, UINT containing length of keybdState
 * @return true if all keys in m_KeyBind are held
 */
bool MacroHolder::checkTrigger(int last, bool **keybdState, UINT aSize)
{
    if (aSize != VK_LIST_SIZE)
    {
        std::cerr << "ERROR: Keyboard array size mismatch\n";
    }
    // if last isn't final key, return false. This way, we are sure that we meant to activate right this call.
    if (last != m_KeyBind->back())
    {
        return false;
    }

    bool active = true;
    // Verify all keys but last are held
    for (auto vkCode = m_KeyBind->begin(); vkCode != m_KeyBind->end(); ++vkCode)
    {
        bool status = (*keybdState)[*vkCode];
        if (!status)
        {
            active = false;
            std::cout << *vkCode << " not pressed " << status << "\n";
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

