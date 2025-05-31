#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using namespace sf;
using namespace std;

class Fruit
{
	private:
		Vector2i pos;
		Sprite fruit;

	public:
		Fruit(Texture&);
		Fruit(Vector2i, Texture&);

		Vector2i getPosition();
		void Draw(RenderWindow&);
		void SetPosition(Vector2i);

};

