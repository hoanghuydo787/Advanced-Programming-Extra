#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <deque>
#include <random>
#include "Snake.h"
#include "Food.h"
#include "Wall.h"

using namespace std;
using namespace sf;

enum class GameState { Running, Paused, GameOver };

class Engine
{
	RenderWindow window;
	deque<Direction> directionQueue;
	Time timeElapsedSinceLastMove = Time::Zero;
	int speed = 2;
	Snake snake;
	Food apple;
	vector<WallSection> baseWall;
	GameState currentGameState;
	//GameState lastGameState;
	random_device rd;
	mt19937 mt = mt19937(rd());
public:
	
	Engine();
	void run();
	void input();
	void update();
	void updateSnakePosition(Direction);
	void draw();
	void addDirection(Direction);
	void moveFood();
	void togglePauseState();
	void startGame();
};