#ifndef SPIKE_H
#define SPIKE_H

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

class Spike: public Texture
{
public:
    Spike();
    ~Spike();
    void loadMedia(SDL_Renderer* renderer);

    void update(int &status, int &score, bool &is_hitting_wall);

    float getDx(int i);
    float getDy(int i);
    int getSpikeNumber();

    void setSpikeNumber(int &score);
    void setCollider(int &, int &);
    void reset();

    void moveSpike();                   //hard mode
    void MoveInCave();
protected:
    int spike_number;
    int switch_direction_counter; //for moving the spikes

private:

};

#endif // SPIKE_H
