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
#include <iostream>


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
	player->setPosition(Vector2{ 100.0f, 100.0f });
	player->setSpeed(500.0f);
	player->setColor(SKYBLUE);

	//Creates the keyboard behavior for player
	KeyboardBehavior* keyboardBehavior = new KeyboardBehavior();
	player->addBehavior(keyboardBehavior);

	//Create the enemy
	Agent* enemy = new Agent();
	enemy->setPosition(Vector2{ 500.0f, 500.0f });
	enemy->setSpeed(250.0f);
	enemy->setColor(PURPLE);
	/*ChaseBehavior* chase = new ChaseBehavior();
	chase->setTarget(player);
	enemy->addBehavior(chase);*/

	/*Agent* enemy2 = new Agent();
	enemy2->setPosition(Vector2{ 500.0f, 300.0f });
	enemy2->setSpeed(100.0f);
	enemy2->setColor(PURPLE);*/

	
	
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		player->update(GetFrameTime());
		enemy->update(GetFrameTime());
		/*enemy2->update(GetFrameTime());*/
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);	

		player->draw();
		enemy->draw();
		/*enemy2->draw();*/

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}