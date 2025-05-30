#include "Game_Over.h"
#include <iostream>

Game_Over::Game_Over(RenderWindow& window) :
	titleText(font, "You Lost! Total Score: 0", 72),
	playAgainText(font, "Press Enter to Play Again", 40) {

	if (!font.openFromFile("assets/fonts/pixel_font.ttf")) {
		std::cerr << "Failed to load font!\n";
	}

	// Title text setup
	titleText.setFillColor(Color::White);
	centerText(titleText, window, 150.f);

	// Play again text
	playAgainText.setFillColor(Color::White);
	centerText(playAgainText, window, 300.f);

}

void Game_Over::Draw(RenderWindow& window) {
	window.clear();
	window.draw(titleText);
	window.draw(playAgainText);
	window.display();
}

void Game_Over::setScore(int score) {
	titleText.setString("You Lost! Total Score: " + std::to_string(score));
}

bool Game_Over::PlayAgain() {
	return Keyboard::isKeyPressed(Keyboard::Key::Enter);
}
