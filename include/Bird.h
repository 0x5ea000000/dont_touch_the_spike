#ifndef BIRD_H
#define BIRD_H

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

class Bird: public Texture
{
public:
    Bird();
    ~Bird();
    void hardBird();
    void loadMedia(SDL_Renderer* renderer);                                     //load all object media

    void handleEvent(SDL_Event event, int &status, vector<Mix_Chunk*>);         //get event
    void update(int &status, int &score, bool &is_hitting_wall);                  //update bird position
    void playSound(vector<Mix_Chunk*>, bool &);                                 //play sound

    void setCollider(int &);
    void setInvincible(const bool&);
    void pause();
    void reset();

    bool isInvincible();
    float getDx();
    float getDy();

protected:
    float dx, dy;                           //to change bird properties more easily
    float ddx, ddy;                         //gravity
    float change_press_dx, change_press_dy; //change of velocity when press SPACE
    bool is_key_pressed;
    bool invincible;

private:

};

#endif // BIRD_H
