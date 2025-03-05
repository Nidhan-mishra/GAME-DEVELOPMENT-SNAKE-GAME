#pragma once

#include <stack>
#include <memory>
#include "State.h"
class StateComp
{

private:
	std::stack<std::unique_ptr<State>> StateStackS;
	std::unique_ptr<State> m_newState;

	bool m_add;
	bool m_replace;
	bool m_remove;
	bool m_removeAll;

public:
 StateComp();
~StateComp();

 void Add(std::unique_ptr<State> toAdd, bool replace = false);
 void PopCurrent();
 void PopAll();
 void ProcessStateChange();
 std::unique_ptr<State>& GetCurrent();
 bool IsEmpty() const;

};



