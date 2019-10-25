#include "Item.h"

using namespace std;

Item::Item()
{
    item_type = CANDY;
    hasBeenEaten = true;
    activate_effect = false;
    k = 0; //var for item animation
    x.push_back(0);
    y.push_back(0);
    collider.resize(1);
}

Item::~Item()
{
    x.clear();
    y.clear();
}

void Item::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/candy-32.png", renderer);
    loadFromFile("assets/sprites/energy-drink-32.png", renderer);
    loadFromFile("assets/sprites/candy-high-32.png", renderer);
    loadFromFile("assets/sprites/candy-rare-32.png", renderer);
}

void Item::update(int& status, const bool& is_hitting_wall)
{
    if (hasBeenEaten == true && is_hitting_wall == true) //if bird eat item and hit wall, render item on opposite wall
    {
        srand((int) time(0));
        x.clear();
        y.clear();
        if (status == GOING_LEFT)
        {
            x.push_back(50+rand()%30 *9); //vi tri x cua keo
            y.push_back(100+rand()%40  *9);
        }
        else
        {
            x.push_back(SCREEN_WIDTH - 50 - width.at(0));
            y.push_back(80+rand()%40 *9);
        }
        hasBeenEaten = false;
    }
}

void Item::checkIfEaten(Bird& bird, int& score, vector <Mix_Chunk*> &sound)
{
    srand((int) time(0));
    if (x.size() != 0 && y.size() != 0)
    {
        setCollider();
        if(checkCollision(bird.getCollider(), getCollider()) == true)
        {
            hasBeenEaten = true; //stop rendering item

            if (activate_effect == true) //put in here to do once
            {
                activateEffect(score, bird);
                activate_effect = false;
                playSound(sound);
                if(score <= 25)
                    item_type = rand() % (texture.size()-2);
                else if(score <= 40)
                    item_type = rand() % (texture.size()-1); //randomly choose an item type;
                else
                    item_type = rand() % texture.size();
            }

        }
        else //if bird not collide with item
        {
            activate_effect = true;
        }
    }

}

bool Item::getItemState()
{
    return hasBeenEaten;
}

void Item::itemAnimation() //move candy up and down
{
    if (x.size() != 0 && y.size() != 0)
    {
        k++;
        if (k > 30) //travel distance
        {
            y.at(0) -= 0.2; //speed
            if(k >= 2*30)
                k = 0;
        }
        else
        {
            y.at(0) += 0.2;
        }
    }
}

void Item::activateEffect(int& score, Bird &bird) //need to use other class properties
{
    switch(item_type)
    {
    case CANDY: //need access to score
    {
        score++;
        break;
    }
    case ENERGY_DRINK:
    {
        bird.setInvincible(true);
        break;
    }
    case CANDY_HIGH:
    {
        score+=2;
        break;
    }
    case CANDY_RARE:
        score+=3;
        break;
    }
}

int Item::getItemType()
{

    return item_type;
}

void Item::playSound(vector <Mix_Chunk*> &sound)
{
    if(hasBeenEaten == true)
    {
        Mix_PlayChannel(-1, sound.at(3), 0);
    }
}

void Item::setCollider()
{
    collider.at(0).x = x.at(0) + 10;
    collider.at(0).y = y.at(0) + 5;
    collider.at(0).w = 25;
    collider.at(0).h = 25;
}

void Item::reset()
{
    item_type = CANDY;
    hasBeenEaten = true;
    activate_effect = false;
    k = 0; //var for item animation
    x.push_back(0);
    y.push_back(0);
}
