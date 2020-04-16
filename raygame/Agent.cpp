#include "Agent.h"
#include "Behavior.h"

void Agent::update(float deltaTime) 
{
	//Set total force to zero
	//For each Behavior in the Behavior list
	for (auto i = m_behaviorList.begin(); i != m_behaviorList.end(); i ++) {
		//Ca;; the Behavior's update function
		(*i)->update(this, deltaTime);
	}
	//Add velocity times delta time to position
	m_position += m_velocity * deltaTime;
}

void Agent::draw() 
{
	DrawRectangle((int)m_position.x, (int)m_position.y, 10, 10, m_color);
}

void Agent::addBehavior(Behavior* behavior) 
{
	//Add the Behavior
	m_behaviorList.insert(m_behaviorList.end(), behavior);
}

void Agent::addForce(Vector2 force) 
{
	m_velocity += force;
}
