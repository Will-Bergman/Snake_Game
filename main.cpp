#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Main_Menu.h"
#include "Game_Over.h"
#include "Snake.h"
#include "Fruit.h"

using namespace sf;
using namespace std;

enum class GameState {
    MENU = 0, PLAYING = 1, GAME_OVER = 2
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
    Clock game_clock, snake_clock, fps_clock, fruit_spawn_clock;

    // Game details
    Music hava;
    if (!hava.openFromFile("assets/audios/hava_nagila.mp3")) {
        std::cerr << "Failed to open music file\n";
    }
    Font pixel_font;
    pixel_font.openFromFile("./assets/fonts/pixel_font.ttf");
    Time previousTime = fps_clock.getElapsedTime();
    Text fpsText(pixel_font, "fps: 0", 20);
    fpsText.setPosition({ 25.f, 5.f });
    float frames = 0;
    float fps;

    
    // Snake and grid
    vector<vector<RectangleShape>> grid(16);
    initializeGrid(grid, window);
    
    Texture snake_head_texture;
    Texture fruit_texture;
    snake_head_texture.loadFromFile("assets/textures/snake_head2.png");
    fruit_texture.loadFromFile("assets/textures/pixel_coin.png");
    Snake snake({ 10, 10 }, 1, 1, snake_head_texture);
    bool fruit_here = false;
    vector<Fruit> fruits;
    bool in_bounds = true;
    bool body_collision = false;


    while (window.isOpen())
    {
        frames++;
        Time currentTime = fps_clock.getElapsedTime();
        if (currentTime.asSeconds() - previousTime.asSeconds() >= 1.0f) {
            fps = frames / (currentTime.asSeconds() - previousTime.asSeconds());
            previousTime = currentTime;
            frames = 0;

            std::stringstream ss;
            ss.precision(2);
            ss << "FPS: " << int(fps);
            fpsText.setString(ss.str());
        }
        // ----------------------------------------------
        // ---------------- Event Loop ------------------
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            // Main Menu
            if (state == GameState::MENU) {
                if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                    if (keyPressed->scancode == Keyboard::Scancode::Enter) {
                        state = GameState::PLAYING;
                        hava.play();
                    }
                }
                else if (menu.play_button.isClicked(window)) {
                    state = GameState::PLAYING;
                    hava.play();
                }
            }
            // Game
            else if (state == GameState::PLAYING) {
                if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                    switch (keyPressed->scancode) {
                    case Keyboard::Scancode::Up:    snake.changeNextDir(0); break;
                    case Keyboard::Scancode::Right: snake.changeNextDir(1); break;
                    case Keyboard::Scancode::Down:  snake.changeNextDir(2); break;
                    case Keyboard::Scancode::Left:  snake.changeNextDir(3); break;
                    default: break;
                    }
                }
            }
            else if (state == GameState::GAME_OVER) {
                if (game_over.PlayAgain()) {
                    snake = Snake({ 10, 10 }, 1, 1, snake_head_texture);
                    bool fruit_here = false;
                    bool in_bounds = true;
                    bool body_collision = false;
                    snake_clock.restart();
                    state = GameState::PLAYING;
                }
            }

        }
        // ----------------------------------------------
        // Main Menu
        if (state == GameState::MENU) {
            menu.MoveTitle(game_clock);
            menu.Draw(window);
        }
        // Game
        else if (state == GameState::PLAYING) {
            if (fruit_spawn_clock.getElapsedTime().asSeconds() > 2.f) {
                Vector2i new_pos = snake.checkForOpen();
                Fruit new_fruit(fruit_texture);
                new_fruit.SetPosition(new_pos);
                fruits.push_back(new_fruit);
                fruit_spawn_clock.restart();
            }

            if (snake_clock.getElapsedTime().asSeconds() > 0.2) {
                snake.Update();
                snake_clock.restart();
            }
            for (Fruit& fruit : fruits) {
                if (snake.getPosition() == fruit.getPosition()) {
                    fruit_here = false;
                    fruit.SetPosition({ -1, -1 });
                    snake.Grow();
                }
            }
            if (snake.getPosition().x < 0 || snake.getPosition().y < 0 || snake.getPosition().x > 29 || snake.getPosition().y > 15) {
                in_bounds = false;
                game_over.setScore(snake.getBody().size());
                state = GameState::GAME_OVER;
            }
            if (snake.checkBodyCollision()) {
                body_collision = true;
                game_over.setScore(snake.getBody().size());
                state = GameState::GAME_OVER;
            }
            window.clear();
            drawGrid(grid, window);
            snake.Draw(window);
            for (Fruit& fruit : fruits) {
                fruit.Draw(window);
            }
            window.draw(fpsText);
            window.display();
        }
        // Game Over
        else if (state == GameState::GAME_OVER) {
            game_over.Draw(window);
        }
    }

    window.close();
    return 0;
}