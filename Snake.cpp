#include "Snake.h"
#include <iostream>

// --------- Constructors ----------------
Snake::Snake(Vector2i position, int velocity, Texture& texture) : 
    snake_head(texture) {
    snake_head.setScale({40.f / texture.getSize().x, 40.f / texture.getSize().y});
    snake_head.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f});
    pos = position; 
    vel = velocity;
    canTurn = true;
    body = vector<Snake_Body>(0);
    next_dir = -1;
}

Snake::Snake(Vector2i position, int velocity, int parts, Texture& texture) : 
    snake_head(texture) {
    snake_head.setScale({ 80.f / texture.getSize().x, 80.f / texture.getSize().y });
    snake_head.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
    pos = position;
    vel = velocity;
    canTurn = true;
    for (int i = 1; i <= parts; i++) {
        if(i % 2 == 0)
            body.emplace_back(position - Vector2i{ i, 0 }, velocity, Color::Blue);
        else
            body.emplace_back(position - Vector2i{ i, 0 }, velocity, Color::White);
    }
    next_dir = -1;
}

Snake_Body::Snake_Body() : pos({ 0, 0 }), vel(1) {
    rect = RectangleShape({ 38.f, 38.f });
    rect.setFillColor(Color::White);
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(1.f);
}

Snake_Body::Snake_Body(Vector2i position, int velocity, Color color) {
    pos = position;
    vel = velocity;
    rect = RectangleShape({ 38.f, 38.f });
    rect.setFillColor(color);
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(1.f);
}
// ----------------------------------------
// ---------- Functions -------------------

// Snake -----------------
const std::vector<Snake_Body>& Snake::getBody() const {
    return body;
}

std::vector<Snake_Body>& Snake::getBody() {
    return body;
}

Vector2i Snake::checkForOpen() {
    Vector2i random_sq;
    do {
        random_sq = { rand() % 30, rand() % 16 };
    } while (isOccupied(random_sq));
    return random_sq;
}

Vector2i Snake::getPosition() {
    return pos;
}

int Snake::getNextDir() {
    return next_dir;
}

bool Snake::isOccupied(Vector2i position) {
    if (pos == position)
        return true;
    for (auto& part : body)
        if (position == part.getPosition())
            return true;
    return false;
}

void Snake::changeNextDir(int next) {
    next_dir = next;
}

void Snake::Update() {

    if (canTurn && next_dir != -1) {
        Turn();
    }

    Vector2i prev_part = pos;
    switch (vel) {
        // North Vel
    case 0: pos.y--; break;
        // East Vel
    case 1:
        pos.x++;
        if (snake_head.getScale().x < 0) {
            Vector2f scale = snake_head.getScale();
            snake_head.setScale({ -scale.x, scale.y });  // Make it face right
        }
        break;
        // South Vel
    case 2: pos.y++; break;
        // West Vel
    case 3:
        pos.x--;
        if (snake_head.getScale().x > 0) {
            Vector2f scale = snake_head.getScale();
            snake_head.setScale({ -scale.x, scale.y });  // Make it face left
        }
        break;
    }
    canTurn = true;
    for (Snake_Body& part : body) {
        prev_part = part.Update(prev_part);
    }
}

void Snake::Turn() {
    if ((vel + 2) % 4 != next_dir) {
        vel = next_dir;
        canTurn = false;
        next_dir = -1;
    }
}

void Snake::Draw(RenderWindow& window) {
    for (Snake_Body& part : body) {
        part.Draw(window);
    }
    snake_head.setPosition({ pos.x * 40.f + 60.f, pos.y * 40.f + 60.f });
    window.draw(snake_head);
}

void Snake::Grow() {
    if(body.size() % 2 == 0)
        body.emplace_back(Vector2i{ 50, 50 }, vel, Color::White);
    else {
        body.emplace_back(Vector2i{ 50, 50 }, vel, Color::Blue);
    }
}

bool Snake::checkBodyCollision() {
    for (Snake_Body& part : body) {
        if (part.getPosition() == pos)
            return true;
    }
    return false;
}

// Snake_Body -------------

Vector2i Snake_Body::Update(Vector2i prev) {
    Vector2i temp = pos;
    pos = prev;
    return temp;
}

Vector2i Snake_Body::getPosition() const {
    return pos;
}

void Snake_Body::Draw(RenderWindow& window) {
    rect.setPosition({ pos.x * 40.f + 42.f, pos.y * 40.f + 42.f });
    window.draw(rect);
}

