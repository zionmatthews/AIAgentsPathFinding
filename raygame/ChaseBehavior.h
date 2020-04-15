#pragma once
#include "Behavior.h"

class ChaseBehavior : public Behavior
{
public:
	ChaseBehavior() {}
	virtual ~ChaseBehavior() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent* m_target = nullptr;
};

