#include "Wall.h"

WallSection::WallSection(Vector2f startPosition)
{
	wallSectionShape.setSize(Vector2f(20, 20));
	wallSectionShape.setFillColor(Color::Blue);
	wallSectionShape.setPosition(startPosition);
	wallSectionPosition = startPosition;
};

void WallSection::setPosition(Vector2f newPosition)
{
	wallSectionShape.setPosition(newPosition);
	wallSectionPosition = newPosition;
}

RectangleShape WallSection::getShape()
{
	return wallSectionShape;
}