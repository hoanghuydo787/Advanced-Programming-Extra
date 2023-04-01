#include "Food.h"

Food::Food()
{
	Vector2f startPosition(400, 300);
	foodShape.setSize(Vector2f(20, 20));
	foodShape.setFillColor(Color::Red);
	foodShape.setPosition(startPosition);
	foodPosition = startPosition;
};

void Food::setPosition(Vector2f newPosition)
{
	foodShape.setPosition(newPosition);
	foodPosition = newPosition;
}

RectangleShape Food::getShape()
{
	return foodShape;
}