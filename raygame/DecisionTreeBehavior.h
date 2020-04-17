#pragma once
#include "Behavior.h"
#include "Decision.h"

class DecisionTreeBehavior : public Behavior
{
public:
	DecisionTreeBehavior(Decision* decision) : m_rootDecision(decision) {}
	virtual ~DecisionTreeBehavior() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	Decision* m_rootDecision;
};