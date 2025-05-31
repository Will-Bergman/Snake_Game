#include "Fruit.h"

Fruit::Fruit(Texture& texture) :
    fruit(texture) {
    pos = { 1, 1 };
    fruit.setScale({ 40.f / texture.getSize().x, 40.f / texture.getSize().y });
    fruit.setPosition({ -1, -1 });
}

Fruit::Fruit(Vector2i position, Texture& texture) : 
    fruit(texture) {
    pos = position;
    fruit.setPosition({ position.x * 40.f + 34.f, position.y * 40.f + 30.f });
    fruit.setScale({ 60.f / texture.getSize().x, 60.f / texture.getSize().y });
}

Vector2i Fruit::getPosition() {
    return pos;
}

void Fruit::Draw(RenderWindow& window) {
    window.draw(fruit);
}

void Fruit::SetPosition(Vector2i newPos) {
    pos = newPos;
    fruit.setPosition({ pos.x * 40.f + 40.f, pos.y * 40.f + 40.f });
}