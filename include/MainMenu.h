#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Bird.h"
#include "Background.h"
#include "Button.h"
#include "Spike.h"
#include "constant.h"
#include "Score.h"
using namespace std;

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();
    void loadMedia(SDL_Renderer* renderer);

    void handleEvent(SDL_Event event, bool &end_loop, int &mode);
    void update(bool &end_loop, int &mode);
    void render(SDL_Renderer* renderer, bool end_loop);

    void setHighScore(int score);
    void reset();

protected:
    Background background;
    vector <Button> button;

    vector <Mix_Chunk*> sound;
    int frame;
    int high_score;
    Score s_high_score;

private:

};

#endif // MAINMENU_H
