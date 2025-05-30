#pragma once

#include <SFML/Graphics.hpp>

inline void centerText(sf::Text& text, const sf::RenderWindow& window, float yPosition) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ window.getSize().x / 2.f, yPosition });
}