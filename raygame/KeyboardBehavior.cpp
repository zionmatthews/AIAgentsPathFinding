#include "KeyboardBehavior.h"

void KeyboardBehavior::update(Agent * agent, float deltaTime)
{
	Vector2 direction = { 0.0f, 0.0f };

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))		    direction.y = -1;
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))		direction.y = 1;
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))		direction.x = -1;
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))		direction.x = 1;
	//Normalize in case of diagonal
	direction = direction.normalize();

	//Multiply the direction by the desired speed
	Vector2 force = direction * agent->getSpeed();

	//Subtract the agent's current velocity from the result to get the the force we need
	force = force - agent->getVelocity();

	agent->addForce(force * deltaTime);
}
