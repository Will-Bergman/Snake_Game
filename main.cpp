#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

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
        rect = RectangleShape({ 40.f, 40.f });
        rect.setFillColor(Color::Yellow);
    }

    Snake_Body(Vector2i position, int velocity) {
        pos = position;
        vel = velocity;
        rect = RectangleShape({ 40.f, 40.f });
        rect.setFillColor(Color::Yellow);
    }

    Vector2i Update(Vector2i prev) {
        Vector2i temp = pos;
        pos = prev;
        return temp;
    }

    void Draw(RenderWindow& window) {
        rect.setPosition({ pos.x * 40.f + 40.f, pos.y * 40.f + 40.f });
        window.draw(rect);
    }
};

struct Snake {

    RectangleShape snake_head;
    Vector2i pos;
    int vel;
    bool canTurn;
    vector<Snake_Body> body;

    Snake(Vector2i position, int velocity) {
        pos = position;
        vel = velocity;
        canTurn = true;
        snake_head = RectangleShape({ 40.f, 40.f });
        snake_head.setFillColor(Color::Yellow);
        body = vector<Snake_Body>(0);
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

    void Turn(int dir) {
        if ((vel + 2) % 4 != dir) {
            vel = dir;
            canTurn = false;
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
        body.push_back(Snake_Body(body[body.size() - 1].pos, body[body.size() - 1].vel));
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
    // Window & time
    RenderWindow window(VideoMode({ 1280, 720 }), "Snake");
    Clock snake_clock;
    
    // Snake and grid
    vector<vector<RectangleShape>> grid(16);
    initializeGrid(grid, window);
    bool in_bounds = true;

    Snake snake({ 10, 10 }, 1, 10);
    bool fruit_here = false;
    Fruit fruit;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                if (keyPressed->scancode == Keyboard::Scancode::Up && snake.canTurn)
                    snake.Turn(0);
                else if (keyPressed->scancode == Keyboard::Scancode::Right && snake.canTurn)
                    snake.Turn(1);
                else if (keyPressed->scancode == Keyboard::Scancode::Down && snake.canTurn)
                    snake.Turn(2);
                else if (keyPressed->scancode == Keyboard::Scancode::Left && snake.canTurn)
                    snake.Turn(3);
            }
        }
       
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
            break;
        }

        window.clear();
        drawGrid(grid, window);
        snake.Draw(window);
        fruit.Draw(window);
        window.display();
    }

    cout << "Out of bounds" << "\n";
    window.close();

}