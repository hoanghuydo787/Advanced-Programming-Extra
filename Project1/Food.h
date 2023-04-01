#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Food
{
	Vector2f foodPosition;
	RectangleShape foodShape;
public:
	Food();
	void setPosition(Vector2f);
	RectangleShape getShape();
};