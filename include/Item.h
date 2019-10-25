#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Bird.h"
#include "Texture.h"
#include "constant.h"
#include "time.h"
#include "random"


class Item: public Texture
{
public:
    Item();
    ~Item();
    void loadMedia(SDL_Renderer* renderer);

    void update(int &status, const bool&);
    void checkIfEaten(Bird& bird, int&,vector <Mix_Chunk*> &); //check if item is eaten
    void itemAnimation(); //item move up and down
    void activateEffect(int&, Bird &bird); //for each type of item, activate effect accordingly
    void playSound(vector <Mix_Chunk*> &sound);

    void setCollider();

    bool getItemState(); //return hasBeenEaten
    int getItemType();
    void reset();

protected:
    int item_type; //candy, energy drink, shield, ...
    bool hasBeenEaten = false;
    bool activate_effect;
    int k; //animation counter

private:

};

#endif // ITEM_H_INCLUDED
