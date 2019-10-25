#ifndef DUELMODE_H
#define DUELMODE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Player.h"
#include "ClassicMode.h"

class DuelMode : public ClassicMode
{
public:
    DuelMode();
    ~DuelMode();
    void loadMedia(SDL_Renderer* renderer);

    void handleEvent(SDL_Event event, bool &end_loop, int &mode);
    void update(bool &end_loop, int& mode);
    void playSound();
    void render(SDL_Renderer* renderer, bool end_loop);

    void reset();

protected:
    Player1 player1;
    Player2 player2;

    int winner;
    int delay_after_hit_wall;
};

#endif // DUELMODE_H
