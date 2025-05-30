#include "Snake.h"
#include <iostream>

// --------- Constructors ----------------
Snake::Snake(Vector2i position, int velocity) {
    pos = position;
    vel = velocity;
    canTurn = true;
    snake_head = RectangleShape({ 40.f, 40.f });
    snake_head.setFillColor(Color::Yellow);
    body = vector<Snake_Body>(0);
    next_dir = -1;
}

Snake::Snake(Vector2i position, int velocity, int parts) {
    pos = position;
    vel = velocity;
    canTurn = true;
    snake_head = RectangleShape({ 40.f, 40.f });
    snake_head.setFillColor(Color::Yellow);
    for (int i = 1; i <= parts; i++) {
        body.push_back(Snake_Body(position - Vector2i{ i, 0 }, velocity));
    }
    next_dir = -1;
}

Snake_Body::Snake_Body() : pos({ 0, 0 }), vel(1) {
    rect = RectangleShape({ 38.f, 38.f });
    rect.setFillColor(Color::Yellow);
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(1.f);
}

Snake_Body::Snake_Body(Vector2i position, int velocity) {
    pos = position;
    vel = velocity;
    rect = RectangleShape({ 38.f, 38.f });
    rect.setFillColor(Color::Yellow);
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
    case 1: pos.x++; break;;
        // South Vel
    case 2: pos.y++; break;
        // West Vel
    case 3: pos.x--; break;
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
    snake_head.setPosition({ pos.x * 40.f + 40.f, pos.y * 40.f + 40.f });
    window.draw(snake_head);
    for (Snake_Body& part : body) {
        part.Draw(window);
    }
}

void Snake::Grow() {
    body.emplace_back(Snake_Body({ 50, 50 }, vel));
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

