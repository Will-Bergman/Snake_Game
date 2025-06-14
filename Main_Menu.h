#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Utils.h"
#include "Button.h"
#include <iostream>

using namespace sf;
using namespace std;

class Main_Menu
{
	private:
		Font font;
		Text titleText;
		Vector2f baseTitlePos;
	
	public:
		Button play_button;
		Main_Menu(RenderWindow&);

		void MoveTitle(Clock);
		void Draw(RenderWindow& window);
		bool ShouldStart(); // Check if Enter is pressed

};

