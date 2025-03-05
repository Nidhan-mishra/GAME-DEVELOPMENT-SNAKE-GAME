#include "StateComp.h"

StateComp::StateComp() : m_add(false), m_replace(false), m_remove(false), m_removeAll(false)
{
}

StateComp::~StateComp()
{
}

void StateComp::Add(std::unique_ptr<State> toAdd, bool replace)
{
    m_add = true;
    m_newState = std::move(toAdd);

    m_replace = replace;
}

void StateComp::PopCurrent()
{
    m_remove = true;
}

void StateComp::PopAll()
{
    m_removeAll = true;
    m_remove = false;
}

void StateComp::ProcessStateChange()
{
    if (m_removeAll)
    {
        while (!StateStackS.empty())
        {
            StateStackS.pop();
        }
        m_removeAll = false;
    }
    else if (m_remove && (!StateStackS.empty()))
    {
        StateStackS.pop();

        if (!StateStackS.empty())
        {
            StateStackS.top()->Start();
        }

        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && (!StateStackS.empty()))
        {
            StateStackS.pop();
            m_replace = false;
        }

        if (!StateStackS.empty())
        {
            StateStackS.top()->Pause();
        }

        StateStackS.push(std::move(m_newState));
        StateStackS.top()->Init();
        StateStackS.top()->Start();
        m_add = false;
    }
}

std::unique_ptr<State>& StateComp::GetCurrent()
{
    return StateStackS.top();
}

bool StateComp::IsEmpty() const
{
    return StateStackS.empty();
}
