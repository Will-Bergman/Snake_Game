#include "Main_Menu.h"
#include <iostream>

Main_Menu::Main_Menu(RenderWindow& window) : 
    titleText(font, "SNAKE", 72), 
    startText(font, "Press Enter to Start", 40) {

    if (!font.openFromFile("assets/fonts/pixel_font.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    // Title text setup
    titleText.setFillColor(Color::White);
    centerText(titleText, window, 150.f);

    // Start text setup
    startText.setFillColor(Color::White);
    centerText(startText, window, 300.f);
}

void Main_Menu::Draw(RenderWindow& window) {
    window.clear();
    window.draw(titleText);
    window.draw(startText);
    window.display();
}

bool Main_Menu::ShouldStart() {
    return Keyboard::isKeyPressed(Keyboard::Key::Enter);
}