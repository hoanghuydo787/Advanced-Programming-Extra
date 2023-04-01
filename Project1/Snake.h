#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

using namespace std;
using namespace sf;

enum class Direction { Up, Down, Left, Right };

class Snake
{
	class SnakeSection
	{
		Vector2f sectionPosition;
		RectangleShape sectionShape;
	public:
		SnakeSection(Vector2f);
		void setPosition(Vector2f);
		Vector2f getPosition();
		RectangleShape getShape();
	};
	// a snake conludes of vector of snake sections
	vector<SnakeSection> vsnake;
	int sectionToAdd = 0;
	// snake current direction
	Direction direction = Direction::Right;
	Snake();
	void addSnakeSection();
	void resetSnake();
	friend class Engine;
};