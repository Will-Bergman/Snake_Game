#include "Button.h"
#include <iostream>
#include <filesystem>

Button::Button(const string& imagePath, const string& fontPath, const string& text, Vector2f position, unsigned int charSize) :
	texture(filesystem::path(imagePath)),
	sprite(texture),
	font(filesystem::path(fontPath)),
	label(font, text, charSize) {
	if (texture.getSize().x == 0 || texture.getSize().y == 0) {
		std::cerr << "Error: Texture failed to load or is empty.\n";
	}
	if (!font.openFromFile(fontPath)) {
		std::cerr << "Error: Failed to load font from '" << fontPath << "'\n";
	}
	sprite.setPosition(position);
	sprite.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
	sprite.setScale({ 0.5f, 0.5f });
	label.setFillColor(Color::White);
	centerText();
	centerSprite();
}

void Button::setFont(const Font& f) {
	font = f;
	label.setFont(font);
}

void Button::setText(const string& t) {
	label.setString(t);
	centerText();
	centerSprite();
}

void Button::centerSprite() {
	FloatRect spriteBounds = sprite.getLocalBounds();
	sprite.setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.f,
		spriteBounds.position.y + spriteBounds.size.y / 2.f });
	label.setPosition(sprite.getPosition());
}

void Button::centerText() {
	FloatRect textBounds = label.getLocalBounds();
	label.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
		textBounds.position.y + textBounds.size.y / 2.f });
}

void Button::setPosition(Vector2f pos) {
	sprite.setPosition(pos);
	centerSprite();
}

void Button::setScale(Vector2f scale) {
	sprite.setScale(scale);
	centerSprite();
}

void Button::Draw(RenderWindow& window) {
	window.draw(sprite);
	window.draw(label);
}

bool Button::isHovered(RenderWindow& window) const {
	Vector2f mouseWorldPos = window.mapPixelToCoords(Mouse::getPosition(window));
	return sprite.getGlobalBounds().contains(mouseWorldPos);
}

bool Button::isClicked(RenderWindow& window) const {
	return isHovered(window) && Mouse::isButtonPressed(Mouse::Button::Left);
}