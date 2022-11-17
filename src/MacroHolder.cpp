#include "MacroHolder.h"

/**
 * Constructor
 *
 * @param ID, id of macro
 * @param *keys, array of inputs as int values
 */
MacroHolder::MacroHolder(int ID, int *keys)
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
 * @param **keysHeld, pointer to array of bools containing input
 * @return true if all keys in m_KeyBind are held
 */
bool MacroHolder::checkTrigger(bool **keysHeld)
{
    return false;
}

