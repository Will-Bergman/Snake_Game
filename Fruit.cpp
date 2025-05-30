#include "Fruit.h"

Fruit::Fruit() {
    pos = { 1, 1 };
    fruit = CircleShape(20.f);
    fruit.setFillColor(Color::Red);
    fruit.setPosition({ 1, 1 });
}

Fruit::Fruit(Vector2i position) {
    pos = position;
    fruit = CircleShape(20.f);
    fruit.setFillColor(Color::Red);
    fruit.setPosition({ position.x * 40.f + 40.f, position.y * 40.f + 40.f });
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