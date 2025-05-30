#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using namespace sf;
using namespace std;

class Fruit
{
	private:
		CircleShape fruit;
		Vector2i pos;

	public:
		Fruit();
		Fruit(Vector2i);

		Vector2i getPosition();
		void Draw(RenderWindow&);
		void SetPosition(Vector2i);

};

