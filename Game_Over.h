#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Utils.h"
#include <iostream>

using namespace sf;
using namespace std;

class Game_Over
{
	private:
		Font font;
		Text titleText;
		Text playAgainText;
		int score;

	public:
		Game_Over(RenderWindow&);

		void Draw(RenderWindow& window);
		void setScore(int);
		bool PlayAgain(); // Check if Enter is pressed
};

