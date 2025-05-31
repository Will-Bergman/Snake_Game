#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using namespace sf;
using namespace std;

class Button
{
    private:
        Texture texture;
        Sprite sprite;
        Text label;
        Font font;

    public:
        Button(const string& imagePath, const string& fontPath, const string& text, Vector2f position, unsigned int charSize = 24);

        void setFont(const Font& f);
        void setText(const string& t);
        void centerText();
        void centerSprite();
        void setPosition(Vector2f pos);
        void setScale(Vector2f scale);
        void Draw(RenderWindow& window);
        bool isHovered(RenderWindow& window) const;
        bool isClicked(RenderWindow& window) const;
};

