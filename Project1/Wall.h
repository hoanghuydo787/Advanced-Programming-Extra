#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class WallSection
{
	Vector2f wallSectionPosition;
	RectangleShape wallSectionShape;
public:
	WallSection(Vector2f);
	void setPosition(Vector2f);
	RectangleShape getShape();
};