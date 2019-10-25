#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Texture.h"
#include "constant.h"

using namespace std;

class Score: public Texture
{
public:
    Score();
    ~Score();
    void loadMedia(SDL_Renderer* renderer);

    void renderScore(SDL_Renderer* renderer, int score);
    void renderScoreCave(SDL_Renderer* renderer, int score);

protected:
    string score_string;

private:

};

#endif // SCORE_H
