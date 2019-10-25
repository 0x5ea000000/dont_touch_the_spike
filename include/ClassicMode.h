#ifndef CLASSICMODE_H
#define CLASSICMODE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Rock.h"
#include "Item.h"
#include "Score.h"
#include "Bird.h"
#include "Background.h"
#include "Button.h"
#include "Spike.h"
#include "constant.h"
#include "MainMenu.h"
#include "time.h"
#include "random"

using namespace std;

class ClassicMode
{
public:
    ClassicMode();
    ~ClassicMode();
    void loadMedia(SDL_Renderer* renderer);

    void handleEvent(SDL_Event event, bool &end_loop, int &mode);
    void update(bool &end_loop, int& mode);
    void playSound();
    void render(SDL_Renderer* renderer, bool end_loop);

    int getScore();
    void reset();

protected:
    Background background;
    Bird bird;
    Spike spike;
    Item item;
    Rock rock;
    Score s_score;

    vector<Mix_Chunk*> sound;
    int score;
    int frame;
    bool is_hitting_wall;
    int status;
    bool playMusic;

private:

};

#endif // CLASSICMODE_H
