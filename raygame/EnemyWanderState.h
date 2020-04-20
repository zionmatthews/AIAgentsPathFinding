#pragma once
#include "State.h"
class EnemyWanderState : public State
{
public:
	EnemyWanderState(Agent* target, float speed)
		: m_target(target), m_speed(speed) {}
	virtual ~EnemyWanderState() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	Agent*	m_target;
	float	m_speed;
	float m_radius = 2000.0f;
	float m_offset = 0.0f;
	float m_jitter = 500.0f;
	Vector2 m_prevTarget = { 0.0f, 0.0f };
};

