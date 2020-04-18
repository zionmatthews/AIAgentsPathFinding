#pragma once
#include "state.h"
class EnemyFleeState : public State
{
public:
	EnemyFleeState(Agent* target, float speed)
		: m_target(target), m_speed(speed) {}
	virtual ~EnemyFleeState() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	Agent*	m_target;
	float	m_speed;
};

