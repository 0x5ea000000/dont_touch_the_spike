#include "Bird.h"

using namespace std;

Bird::Bird()
{
    x.push_back(SCREEN_WIDTH/2.0-26);
    y.push_back(SCREEN_HEIGHT/2.0-76);
    dx = 0;
    dy = 0;
    ddx = 0.05;
    ddy = 0.3;
    change_press_dx = 2;
    change_press_dy = -7.5;
    is_key_pressed = false;
    //fix loi dap tuong
    invincible = false;
    //set per pixel collider
    collider.resize(3);
}

Bird::~Bird()
{
    x.clear();
    y.clear();
    width.clear();
    height.clear();
    texture.clear();

    x.shrink_to_fit();
    y.shrink_to_fit();
    width.shrink_to_fit();
    height.shrink_to_fit();
    texture.shrink_to_fit();
}

void Bird::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/bird-red-downflap.png", renderer);
    loadFromFile("assets/sprites/bird-red-midflap.png", renderer);
    loadFromFile("assets/sprites/bird-red-upflap.png", renderer);

    loadFromFile("assets/sprites/bird-blue-downflap.png", renderer);
    loadFromFile("assets/sprites/bird-blue-midflap.png", renderer);
    loadFromFile("assets/sprites/bird-blue-upflap.png", renderer);

    loadFromFile("assets/sprites/bird-in-cave-downflap.png", renderer);
    loadFromFile("assets/sprites/bird-in-cave-downflap.png", renderer);
    loadFromFile("assets/sprites/bird-in-cave-upflap.png", renderer);

    loadFromFile("assets/sprites/shield.png", renderer);
    loadFromFile("assets/sprites/light-in-cave.png", renderer);
}

void Bird::handleEvent(SDL_Event event, int &status, vector<Mix_Chunk*> sound)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
    {
        if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
        {
            if(status == GOING_RIGHT)
            {
                dx = change_press_dx; //change in velocity when press SPACE
                dy = change_press_dy;
            }
            else if(status == GOING_LEFT)
            {
                dx = (-1)*change_press_dx;
                dy = change_press_dy;
            }
            is_key_pressed = true;
        }
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
        if(status == GOING_RIGHT)
        {
            dx = change_press_dx; //change in velocity when press SPACE
            dy = change_press_dy;
        }
        else if(status == GOING_LEFT)
        {
            dx = (-1)*change_press_dx;
            dy = change_press_dy;
        }
        is_key_pressed = true; //for playing sound effect
        break;
    }
    }
}

void Bird::update(int &status, int &score, bool &is_hitting_wall)
{
    if(status == GOING_RIGHT)
    {
        dx += ddx; //cho de dieu chinh van toc cua cac con chim khac nhau
        dy += ddy;
    }
    else if(status == GOING_LEFT)
    {
        dx -= ddx;
        dy += ddy;
    }

    x.at(0) += dx;
    y.at(0) += dy;
    if(x.at(0) > SCREEN_WIDTH-48-20)
    {
        x.at(0) = SCREEN_WIDTH-48-20;
        dx *= -1; //fix de chim dap tuong tu nhien hon
        dy *= 0.9;
        status = GOING_LEFT;
        is_hitting_wall = true; //for playing sound effect
        score++;

    }
    else if(x.at(0) < 18)
    {
        x.at(0) = 18;
        dx *= -1;
        dy *= 0.9;
        status = GOING_RIGHT;
        is_hitting_wall = true;
        score++;
    }
    else
    {
        is_hitting_wall = false;
    }

    if(y.at(0) >= SCREEN_HEIGHT-70-48)
    {
        y.at(0) = SCREEN_HEIGHT-70-48;
    }
    if(y.at(0) <= 30)
    {
        y.at(0) = 30;
    }

}

void Bird::playSound(vector <Mix_Chunk*> sound, bool & is_hitting_wall)
{
    if(is_key_pressed == true)
    {
        Mix_PlayChannel( -1, sound.at(0), 0 );
        is_key_pressed = false;
    }
    if(is_hitting_wall == true)
    {
        Mix_PlayChannel(-1, sound.at(1), 0);
    }
}

void Bird::pause()
{
    x.at(0) = 18;
    y.at(0) = 24+24; //what is thissss
    dx = 0;
    dy = 0;
    ddx = 0;
    ddy = 0;
    change_press_dx = 0;
    change_press_dy = 0;

}

void Bird::reset()
{
    x.at(0)=(SCREEN_WIDTH/2.0-26);
    y.at(0)=(SCREEN_HEIGHT/2.0-76);
    dx = 0;
    dy = 0;
    ddx = 0.05;
    ddy = 0.3;
    change_press_dx = 2;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

float Bird::getDx()
{
    return dx;
}

float Bird::getDy()
{
    return dy;
}

void Bird::setCollider(int &status)
{
    if(status == GOING_LEFT)
    {
        collider.at(0).x = x.at(0)+10;
        collider.at(0).y = y.at(0)+7;
        collider.at(0).w = 33;
        collider.at(0).h = 12;

        collider.at(1).x = x.at(0);
        collider.at(1).y = y.at(0)+19;
        collider.at(1).w = 48;
        collider.at(1).h = 12;

        collider.at(2).x = x.at(0)+10;
        collider.at(2).y = y.at(0)+31;
        collider.at(2).w = 33;
        collider.at(2).h = 12;
    }
    else if(status == GOING_RIGHT)
    {
        collider.at(0).x = x.at(0)+7;
        collider.at(0).y = y.at(0)+7;
        collider.at(0).w = 33;
        collider.at(0).h = 12;

        collider.at(1).x = x.at(0);
        collider.at(1).y = y.at(0)+19;
        collider.at(1).w = 48;
        collider.at(1).h = 12;

        collider.at(2).x = x.at(0)+7;
        collider.at(2).y = y.at(0)+31;
        collider.at(2).w = 33;
        collider.at(2).h = 12;
    }

}

/*Hard Mode*/
void Bird::hardBird()
{
    x.at(0)=(SCREEN_WIDTH/2.0-26);
    y.at(0)=(SCREEN_HEIGHT/2.0-76);
    dx = 0;
    dy = 0;
    ddx = 0.1;
    ddy = 0.3;
    change_press_dx = 4;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

bool Bird::isInvincible()
{
    return invincible;
}

void Bird::setInvincible(const bool &temp)
{
    invincible = temp;
}
