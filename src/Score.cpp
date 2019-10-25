#include "Score.h"

using namespace std;

Score::Score()
{

}

Score::~Score()
{

}

void Score::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/0.png", renderer);
    loadFromFile("assets/sprites/1.png", renderer);
    loadFromFile("assets/sprites/2.png", renderer);
    loadFromFile("assets/sprites/3.png", renderer);
    loadFromFile("assets/sprites/4.png", renderer);
    loadFromFile("assets/sprites/5.png", renderer);
    loadFromFile("assets/sprites/6.png", renderer);
    loadFromFile("assets/sprites/7.png", renderer);
    loadFromFile("assets/sprites/8.png", renderer);
    loadFromFile("assets/sprites/9.png", renderer);
    loadFromFile("assets/sprites/m.png", renderer);
}

void Score::renderScore(SDL_Renderer* renderer, int score)
{
    score_string = to_string(score);        // convert score to string
    for(unsigned int i = 0; i < score_string.length(); i++)
    {
        render(score_string.at(i)-48, (SCREEN_WIDTH-24*score_string.length()-10*(score_string.length()-1))/2 + i*24, 50,getWidth(score_string.at(i)-48) , getHeight(score_string.at(i)-48), renderer, 0, NULL, SDL_FLIP_NONE);
    }
}

void Score::renderScoreCave(SDL_Renderer* renderer, int score)
{
    score_string = to_string(score);        // convert score to string
    score_string.push_back(':');
    for(unsigned int i = 0; i < score_string.length(); i++)
    {
        render(score_string.at(i)-48, (SCREEN_WIDTH-24*score_string.length()-10*(score_string.length()-1))/2 + i*24, 50,getWidth(score_string.at(i)-48) , getHeight(score_string.at(i)-48), renderer, 0, NULL, SDL_FLIP_NONE);
    }

}
