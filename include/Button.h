#ifndef BUTTON_H
#define BUTTON_H

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

class Button: public Texture
{
public:
    Button();
    ~Button();
    void loadMedia(SDL_Renderer* renderer);       //load all object media

    void handleEvent(SDL_Event event);

    void setPosition(int x, int y);

    void reset();

    bool isHittingButton();

protected:
    int current_status;
    bool hitting_button;

private:

};

#endif // BUTTON_H
