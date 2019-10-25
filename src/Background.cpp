#include "Background.h"

using namespace std;

Background::Background()
{
    x.push_back(0);
    y.push_back(0);
}

Background::~Background()
{
    x.clear();
    y.clear();
    width.clear();
    height.clear();
    texture.clear();

    x.shrink_to_fit();
    y.shrink_to_fit();
    width.shrink_to_fit();
    height.shrink_to_fit();
    texture.shrink_to_fit();
}

void Background::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/background.png", renderer);
    loadFromFile("assets/sprites/gameover.png", renderer);
    loadFromFile("assets/sprites/player2.png", renderer);
    loadFromFile("assets/sprites/player1.png", renderer);
    loadFromFile("assets/sprites/background-cave.png", renderer);
}
