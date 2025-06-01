#pragma once

#include <SFML/Graphics.hpp>

inline void centerText(sf::Text& text, const sf::RenderWindow& window, float yPosition) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ window.getSize().x / 2.f, yPosition });
}

inline sf::Color HSVtoRGB(float hue, float saturation = 1.0f, float value = 1.0f) {
    int h = static_cast<int>(hue * 6);
    float f = hue * 6 - h;
    float p = value * (1 - saturation);
    float q = value * (1 - f * saturation);
    float t = value * (1 - (1 - f) * saturation);

    float r = 0, g = 0, b = 0;
    switch (h % 6) {
    case 0: r = value, g = t, b = p; break;
    case 1: r = q, g = value, b = p; break;
    case 2: r = p, g = value, b = t; break;
    case 3: r = p, g = q, b = value; break;
    case 4: r = t, g = p, b = value; break;
    case 5: r = value, g = p, b = q; break;
    }

    return sf::Color(static_cast<uint8_t>(r * 255), static_cast<uint8_t>(g * 255), static_cast<uint8_t>(b * 255));
}
