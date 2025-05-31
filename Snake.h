#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using namespace sf;
using namespace std;

class Snake_Body {
private:
    RectangleShape rect;
    Vector2i pos;
    int vel;

public:
    //Constructors
    Snake_Body();
    Snake_Body(Vector2i, int, Color);

    //Functions
    Vector2i Update(Vector2i);
    Vector2i getPosition() const;
    void Draw(RenderWindow&);
};


class Snake
{
    private:
        Sprite snake_head;
        Vector2i pos;
        int vel, next_dir;
        bool canTurn;
        vector<Snake_Body> body;

    public:
        //Constructors
        Snake(Vector2i, int, Texture&);
        Snake(Vector2i, int, int, Texture&);

        //Functions
        const vector<Snake_Body>& getBody() const;
        vector<Snake_Body>& getBody();
        Vector2i checkForOpen();
        Vector2i getPosition();
        int getNextDir();
        bool isOccupied(Vector2i);
        bool checkBodyCollision();
        void changeNextDir(int);
        void Update();
        void Turn();
        void Grow();
        void Draw(RenderWindow&);
};
