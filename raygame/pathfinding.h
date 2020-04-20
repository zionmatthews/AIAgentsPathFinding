#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace pathfinding
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		Vector2 position;

		float gScore = 0.0f;
		float hScore = 0.0f;
		float fScore = 0.0f;
		Node* previous;

		std::vector<Edge> connections;
	};

	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode)
	{
		//Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return std::vector<Node*>();
		}

		if (startNode == endNode)
		{
			std::vector<Node*> singleNodePath;
			singleNodePath.push_back(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//Create temporary lists for storing nodes
		std::vector<Node*> openList;
		std::vector<Node*> closedList;

		openList.push_back(startNode);

		while (!openList.empty())
		{
			//Set the current node to the first node in openList
			Node* currentNode = openList.front();
			//Remove currentNode from openList
			openList.erase(openList.begin());
			//Add currentNode to closedList
			closedList.push_back(currentNode);

			//Break if the destination is added to closedList
			if (currentNode == endNode)
			{
				break;
			}

			//For each Edge e in currentNode's connections
			for (Edge e : currentNode->connections)
			{
				//If the target node is in closedList, ignore it
				if (std::find(closedList.begin(), closedList.end(), e.target) != closedList.end())
				{
					continue;
				}

				//Temporarily calculate the target node's G score
				float gScore = currentNode->gScore + e.cost;
				//Temporarily calculate the target node's H score
				float hScore = currentNode->hScore + e.cost;
				//Temporarily calculate the target node's F score
				float fScore = currentNode->fScore + e.cost;

				//Update the target node if it is not in openList
				if (std::find(openList.begin(), openList.end(), e.target) == openList.end())
				{
					//Update the target node's G score from the temporary value
					e.target->gScore = gScore;
					//Update the target node's H score from the temporary value
					e.target->hScore = hScore;
					//Update the target node's F score from the temporary value
					e.target->fScore = fScore;

					//Set the target node's previous to currentNode
					e.target->previous = currentNode;

					//Find the earliest point that a node can be inserted
					auto insertionPos = openList.end();

					for (auto i = openList.begin(); i != openList.end(); i++)
					{
						if (e.target->fScore < (*i)->fScore)
						{
							insertionPos = i;
							break;
						}
					}

					//Insert the node at the appropiate position
					openList.insert(insertionPos, e.target);
				}

				//Otherwise the target node is in openList
				else
				{
					//Compare the new F score to the old one before updating
					if (currentNode->fScore + e.cost < e.target->fScore)
					{
						//Update the target node's G score from the temporary value
						e.target->gScore = gScore;
						//Update the target node's H score from the temporary value
						e.target->hScore = hScore;
						//Update the target node's F score from the temporary value
						e.target->fScore = fScore;

						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		std::vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			//Add the current node to the beginning of the path
			path.insert(path.begin(), currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}

		return path;
	}

	void drawNode(Node* node, bool selected = false)
	{
		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 100, YELLOW);

		//Draw the inner circle
		if (selected)
		{
			DrawCircle(node->position.x, node->position.y, 90, BROWN);
		}

		else
		{
			DrawCircle(node->position.x, node->position.y, 90, BLACK);
		}

		//Draw the text
		DrawText(buffer, node->position.x - 40, node->position.y - 40, 60, WHITE);
	}

	void drawGraph(Node* node, std::vector<Node*>* drawnList)
	{
		drawNode(node);
		drawnList->push_back(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);

			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			DrawText(buffer, costPos.x, costPos.y, 60, WHITE);

			//Draw the target node
			if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end())
			{
				drawGraph(e.target, drawnList);
			}
		}
	}
}