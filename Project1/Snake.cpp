#include "Snake.h"

Snake::Snake()
{
	vsnake.push_back(SnakeSection(Vector2f(100, 100)));
	vsnake.push_back(SnakeSection(Vector2f(80, 100)));
	vsnake.push_back(SnakeSection(Vector2f(60, 100)));
}

void Snake::resetSnake()
{
	vsnake.clear();
	vsnake.push_back(SnakeSection(Vector2f(100, 100)));
	vsnake.push_back(SnakeSection(Vector2f(80, 100)));
	vsnake.push_back(SnakeSection(Vector2f(60, 100)));
	sectionToAdd = 0;
	direction = Direction::Right;
}

Snake::SnakeSection::SnakeSection(Vector2f startPosition)
{
	sectionShape.setSize(Vector2f(20, 20));
	sectionShape.setFillColor(Color::Green);
	sectionShape.setPosition(startPosition);
	setPosition(startPosition);
}

RectangleShape Snake::SnakeSection::getShape()
{
	return sectionShape;
}

void Snake::SnakeSection::setPosition(Vector2f newPosition)
{
	sectionPosition = newPosition;
	sectionShape.setPosition(newPosition);
}

Vector2f Snake::SnakeSection::getPosition()
{
	return sectionPosition;
}

void Snake::addSnakeSection()
{
	SnakeSection newSection = SnakeSection(vsnake[vsnake.size() - 1].getPosition());
	vsnake.emplace_back(newSection);
}