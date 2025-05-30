#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Main_Menu.h"
#include "Game_Over.h"

using namespace sf;
using namespace std;

enum class GameState {
    MENU = 0, PLAYING = 1, GAME_OVER = 2
};

struct Fruit {

    CircleShape fruit;
    Vector2i pos;

    Fruit() {
        pos = { 1, 1 };
        fruit = CircleShape(20.f);
        fruit.setFillColor(Color::Red);
        fruit.setPosition({ 1, 1 });
    }

    Fruit(Vector2i position) {
        pos = position;
        fruit = CircleShape(20.f);
        fruit.setFillColor(Color::Red);
        fruit.setPosition({ position.x * 40.f + 40.f, position.y * 40.f + 40.f });
    }

    void Draw(RenderWindow& window) {
        window.draw(fruit);
    }

    void SetPosition(Vector2i newPos) {
        pos = newPos;
        fruit.setPosition({ pos.x * 40.f + 40.f, pos.y * 40.f + 40.f });
    }
};

struct Snake_Body {
    RectangleShape rect;
    Vector2i pos;
    int vel;

    Snake_Body() : pos({ 0, 0 }), vel(1) {
        rect = RectangleShape({ 38.f, 38.f });
        rect.setFillColor(Color::Yellow);
        rect.setOutlineColor(Color::Black);
        rect.setOutlineThickness(1.f);
    }

    Snake_Body(Vector2i position, int velocity) {
        pos = position;
        vel = velocity;
        rect = RectangleShape({ 38.f, 38.f });
        rect.setFillColor(Color::Yellow);
        rect.setOutlineColor(Color::Black);
        rect.setOutlineThickness(1.f);
    }

    Vector2i Update(Vector2i prev) {
        Vector2i temp = pos;
        pos = prev;
        return temp;
    }

    void Draw(RenderWindow& window) {
        rect.setPosition({ pos.x * 40.f + 42.f, pos.y * 40.f + 42.f });
        window.draw(rect);
    }
};

struct Snake {

    RectangleShape snake_head;
    Vector2i pos;
    int vel, next_dir;
    bool canTurn;
    vector<Snake_Body> body;

    Snake(Vector2i position, int velocity) {
        pos = position;
        vel = velocity;
        canTurn = true;
        snake_head = RectangleShape({ 40.f, 40.f });
        snake_head.setFillColor(Color::Yellow);
        body = vector<Snake_Body>(0);
        next_dir = -1;
    }

    Snake(Vector2i position, int velocity, int parts) {
        pos = position;
        vel = velocity;
        canTurn = true;
        snake_head = RectangleShape({ 40.f, 40.f });
        snake_head.setFillColor(Color::Yellow);
        for (int i = 1; i <= parts; i++) {
            body.push_back(Snake_Body(position - Vector2i{i, 0}, velocity));
        }
        next_dir = -1;
    }

    Vector2i checkForOpen() {
        Vector2i random_sq;
        do {
            random_sq = { rand()%30, rand() % 16 };
        } while (isOccupied(random_sq));
        return random_sq;
    }

    bool isOccupied(Vector2i position) {
        if (pos == position)
            return true;
        for (const auto& part : body)
            if (position == part.pos)
                return true;
        return false;
    }

    void Update() {

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

    void Turn() {
        if ((vel + 2) % 4 != next_dir) {
            vel = next_dir;
            canTurn = false;
            next_dir = -1;
        }
    }

    void Draw(RenderWindow& window) {
        snake_head.setPosition({ pos.x * 40.f + 40.f, pos.y * 40.f + 40.f });
        window.draw(snake_head);
        for (Snake_Body& part : body) {
            part.Draw(window);
        }
    }

    void Grow() {
        body.emplace_back(Snake_Body({50, 50}, vel));
    }

    bool checkBodyCollision() {
        for (Snake_Body& part : body) {
            if (part.pos == pos)
                return true;
        }
        return false;
    }

};


void initializeGrid(vector<vector<RectangleShape>>& grid, RenderWindow& window) {

    for (int i = 1; i < 17; i++) {
        for (int j = 1; j < 31; j++) {
            RectangleShape square({ 40.f, 40.f });
            square.setPosition({ j*40.f, i*40.f });
            if ((i + j) % 2 == 0)
                square.setFillColor(Color(178, 200, 130));
            else
                square.setFillColor(Color(130, 180, 90));

            grid[i - 1].push_back(square);
        }
    }
}

void drawGrid(vector<vector<RectangleShape>> grid, RenderWindow& window) {

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 30; j++) {
            window.draw(grid[i][j]);
        }
    }
}

int main()
{
    // Window & Game state
    RenderWindow window(VideoMode({ 1280, 720 }), "Snake");
    Main_Menu menu(window);
    Game_Over game_over(window);
    GameState state = GameState::MENU;
    Clock snake_clock;
    
    // Snake and grid
    vector<vector<RectangleShape>> grid(16);
    initializeGrid(grid, window);
    
    Snake snake({ 10, 10 }, 1, 1);
    bool fruit_here = false;
    Fruit fruit;
    bool in_bounds = true;
    bool body_collision = false;


    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            // Main Menu
            if (state == GameState::MENU) {
                if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                    if (keyPressed->scancode == Keyboard::Scancode::Enter);
                    state = GameState::PLAYING;
                }
            }
            // Game
            else if (state == GameState::PLAYING) {
                if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                    switch (keyPressed->scancode) {
                    case Keyboard::Scancode::Up:    snake.next_dir = 0; break;
                    case Keyboard::Scancode::Right: snake.next_dir = 1; break;
                    case Keyboard::Scancode::Down:  snake.next_dir = 2; break;
                    case Keyboard::Scancode::Left:  snake.next_dir = 3; break;
                    default: break;
                    }
                }
            }
            else if (state == GameState::GAME_OVER) {
                if (game_over.PlayAgain()) {
                    snake = Snake({ 10, 10 }, 1, 1);
                    bool fruit_here = false;
                    bool in_bounds = true;
                    bool body_collision = false;
                    snake_clock.restart();
                    state = GameState::PLAYING;
                }
            }

        }

       // Main Menu
        if (state == GameState::MENU)
            menu.Draw(window);
        // Game
        else if (state == GameState::PLAYING) {
            if (!fruit_here) {
                Vector2i random_fruit_spawn = snake.checkForOpen();
                fruit = Fruit(random_fruit_spawn);
                fruit_here = true;
            }
            if (snake_clock.getElapsedTime() > seconds(0.2)) {
                snake.Update();
                snake_clock.restart();
            }
            if (snake.pos == fruit.pos) {
                fruit_here = false;
                fruit.SetPosition({ -1, -1 });
                snake.Grow();
            }
            if (snake.pos.x < 0 || snake.pos.y < 0 || snake.pos.x > 29 || snake.pos.y > 15) {
                in_bounds = false;
                game_over.setScore(snake.body.size());
                state = GameState::GAME_OVER;
            }
            if (snake.checkBodyCollision()) {
                body_collision = true;
                game_over.setScore(snake.body.size());
                state = GameState::GAME_OVER;
            }
            window.clear();
            drawGrid(grid, window);
            snake.Draw(window);
            fruit.Draw(window);
            window.display();
        }
        // Game Over
        else if (state == GameState::GAME_OVER) {
            game_over.Draw(window);
        }
    }

    window.close();

}