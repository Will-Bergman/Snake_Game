#include "Main_Menu.h"
#include <iostream>

Main_Menu::Main_Menu(RenderWindow& window) : 
    titleText(font, "SNAKE", 144),
    play_button("assets/textures/play_button.png", 
        "assets/fonts/pixel_font.ttf", "PLAY", 
        Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 32) {

    if (!font.openFromFile("assets/fonts/pixel_font.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    // Title text setup
    titleText.setFillColor(Color::White);
    centerText(titleText, window, 150.f);
    baseTitlePos = titleText.getPosition();
}

void Main_Menu::Draw(RenderWindow& window) {
    window.clear();
    window.draw(titleText);
    play_button.Draw(window);
    window.display();
}

void Main_Menu::MoveTitle(Clock clock) {
    float time = clock.getElapsedTime().asSeconds();
    float offset = 25.f * sin(time * 2.f);
    titleText.setPosition({ baseTitlePos.x, baseTitlePos.y + offset });
}

bool Main_Menu::ShouldStart() {
    return Keyboard::isKeyPressed(Keyboard::Key::Enter);
}