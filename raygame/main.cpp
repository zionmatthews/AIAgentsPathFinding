/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Agent.h"
#include "Behavior.h"
#include "ChaseBehavior.h"
#include "FleeBehavior.h"
#include "KeyboardBehavior.h"
#include "WanderBehavior.h"
#include "FSMBehavior.h"
#include "IdleState.h"
#include "WithinRangeCondition.h"
#include "EnemyAttackState.h"
#include "BooleanDecision.h"
#include "BehaviorDecision.h"
#include "PursuitBehavior.h"
#include "DecisionTreeBehavior.h"
#include "ScreenEdgeBehavior.h"
#include "pathfinding.h"
#include "EnemyFleeState.h"
#include "EnemyWanderState.h"
#include "Maze.h"
#include <iostream>

using namespace pathfinding;

enum tileType
{
	open,
	closed
};


int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 900;
	int screenHeight = 550;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	//Create the player
	Agent* player = new Agent();
	player->setPosition(Vector2{ 200.0f, 200.0f });
	player->setSpeed(500.0f);
	player->setColor(SKYBLUE);

	//Creates the keyboard behavior for player
	KeyboardBehavior* keyboardBehavior = new KeyboardBehavior();
	player->addBehavior(keyboardBehavior);
	
	//Create the enemy
	Agent* enemy = new Agent();
	enemy->setPosition(Vector2{ 600.0f, 350.0f });
	enemy->setSpeed(50.0f);
	enemy->setColor(PURPLE);
	
	//Create and add the enemy's FSM
	FSMBehavior* enemyFSM = new FSMBehavior();
	enemy->addBehavior(enemyFSM);
	//Create and add the wander state
	EnemyWanderState* wanderState = new EnemyWanderState(player, 100.0f);
	enemyFSM->addState(wanderState);
	//Create and add the attack state
	EnemyAttackState* attackState = new EnemyAttackState(player, 200.0f);
	enemyFSM->addState(attackState);
	//Create and add the condition
	Condition* withinRangeCondition = new WithinRangeCondition(player, 200.0f);
	enemyFSM->addCondition(withinRangeCondition);
	//Create and add the transition
	Transition* toAttackTransition = new Transition(attackState, withinRangeCondition);
	enemyFSM->addTransition(toAttackTransition);
	wanderState->addTransitions(toAttackTransition);
	//Set current state to wander 
	enemyFSM->setCurrentState(wanderState);

	//Create Enemy2
	Agent* enemy2 = new Agent();
	enemy2->setPosition(Vector2{ 600.0f, 300.0f });
	enemy2->setSpeed(50.0f);
	enemy2->setColor(PURPLE);

	//Create and add the enemy's FSM
	FSMBehavior* enemyFSM2 = new FSMBehavior();
	enemy2->addBehavior(enemyFSM2);
	//Create and add the wander state
	EnemyWanderState* wanderState2 = new EnemyWanderState(player, 100.0f);
	enemyFSM2->addState(wanderState2);
	//Create and add the attack state
	EnemyFleeState* fleeState = new EnemyFleeState(player, 200.0f);
	enemyFSM2->addState(fleeState);
	//Create and add the condition
	Condition* withinRangeCondition2 = new WithinRangeCondition(player, 200.0f);
	enemyFSM2->addCondition(withinRangeCondition2);
	//Create and add the transition
	Transition* toAttackTransition2 = new Transition(fleeState, withinRangeCondition2);
	enemyFSM2->addTransition(toAttackTransition2);
	wanderState2->addTransitions(toAttackTransition2);
	//Set current state to wander
	enemyFSM2->setCurrentState(wanderState2);
	

	Maze<tileType> maze({ 9, 6 }, { 100, 100 }, closed, BROWN);

	//Walls
	maze.createTile({ 0, 5 }, open, DARKBLUE);
	maze.createTile({ 0, 3 }, open, DARKBLUE);
	maze.createTile({ 0, 4 }, open, DARKBLUE);
	maze.createTile({ 0, 2 }, open, DARKBLUE);
	maze.createTile({ 0, 1 }, open, DARKBLUE);
	maze.createTile({ 0, 0 }, open, DARKBLUE);
	maze.createTile({ 1, 0 }, open, DARKBLUE);
	maze.createTile({ 2, 0 }, open, DARKBLUE);
	maze.createTile({ 3, 0 }, open, DARKBLUE);
	maze.createTile({ 4, 0 }, open, DARKBLUE);
	maze.createTile({ 5, 0 }, open, DARKBLUE);
	maze.createTile({ 6, 0 }, open, DARKBLUE);
	maze.createTile({ 7, 0 }, open, DARKBLUE);
	maze.createTile({ 8, 0 }, open, DARKBLUE);
	maze.createTile({ 8, 1 }, open, DARKBLUE);
	maze.createTile({ 8, 2 }, open, DARKBLUE);
	maze.createTile({ 8, 3 }, open, DARKBLUE);
	maze.createTile({ 8, 4 }, open, DARKBLUE);
	maze.createTile({ 8, 5 }, open, DARKBLUE);
	maze.createTile({ 7, 5 }, open, DARKBLUE);
	maze.createTile({ 6, 5 }, open, DARKBLUE);
	maze.createTile({ 5, 5 }, open, DARKBLUE);
	maze.createTile({ 4, 5 }, open, DARKBLUE);
	maze.createTile({ 3, 5 }, open, DARKBLUE);
	maze.createTile({ 2, 5 }, open, DARKBLUE);
	maze.createTile({ 1, 5 }, open, DARKBLUE);
	
	

	Tile<tileType> tile1 = maze.checkTile({ 100, 100 });
	Tile<tileType> tile2 = maze.getTile({ 1, 3 });

	std::cout << tile1.data << ", ";
	std::cout << tile2.data << std::endl;
	//Output: 0, 0

	//Nodes
	Node* a = new Node();
	a->position = Vector2{ 0, 0 };

	Node* b = new Node();
	b->position = Vector2{ 2, 0 };

	Node* c = new Node();
	c->position = Vector2{ 2, 1 };

	Node* d = new Node();
	d->position = Vector2{ 2, 2 };

	Node* e = new Node();
	e->position = Vector2{ 1, 3 };

	Node* f = new Node();
	f->position = Vector2{ 0, 2 };

	//Edges
	a->connections.push_back(Edge{ b, 2 });
	a->connections.push_back(Edge{ f, 5 });

	b->connections.push_back(Edge{ c, 3 });

	c->connections.push_back(Edge{ a, 3 });
	c->connections.push_back(Edge{ d, 1 });

	d->connections.push_back(Edge{ e, 4 });
	d->connections.push_back(Edge{ f, 4 });

	f->connections.push_back(Edge{ e, 6 });

	
	std::vector<Node*> shortestPath = AStarSearch(a, e);

	for (Node* node : shortestPath) {
		std::cout << node->gScore << std::endl;
	}
	



	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		player->update(GetFrameTime());
		enemy->update(GetFrameTime());
		enemy2->update(GetFrameTime());
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);	

		//Draw the tile map
		maze.draw();

		

		

		player->draw();
		enemy->draw();
		enemy2->draw();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}