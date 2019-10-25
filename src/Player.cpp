#include "Player.h"

//Note: status is DuelMode properties, not Player properties, so the naming can be misleading.
//Note: Stop using ddx. For the birds to reach walls at the same time, velocity need to be constant.
Player1::Player1()
{
    x.push_back(SCREEN_WIDTH/2.0);
    y.push_back(SCREEN_HEIGHT/2.0 + 50);
    dx = 0;
    dy = 0;
    ddx = 0;
    ddy = 0.3;
    change_press_dx = 0;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

void Player1::handleEvent(SDL_Event event, int &status, vector<Mix_Chunk*> sound)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
    {
        if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
        {
            if(status == GOING_RIGHT)
            {
                //dx = change_press_dx; //change in velocity when press SPACE
                dy = change_press_dy;
                ddy = 0.3; //for future use: wait until press SPACE to play
            }
            else if(status == GOING_LEFT)
            {
                //dx = (-1)*change_press_dx;
                dy = change_press_dy;
                ddy = 0.3;
            }
            is_key_pressed = true;
        }
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
        if(status == GOING_RIGHT)
        {
            //dx = change_press_dx; //change in velocity when press SPACE
            dy = change_press_dy;
            ddy = 0.3; //for future use: wait until press SPACE to play
        }
        else if(status == GOING_LEFT)
        {
            //dx = (-1)*change_press_dx;
            dy = change_press_dy;
            ddy = 0.3;
        }
        is_key_pressed = true;
        break;
    }
    }
}

void Player1::reset()
{
    x.at(0)=(SCREEN_WIDTH/2.0-26);
    y.at(0)=(SCREEN_HEIGHT/2.0-76);
    dx = 3;
    dy = 0;
    ddx = 0;
    ddy = 0.3;
    change_press_dx = 0;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

Player2::Player2()
{
    x.push_back(SCREEN_WIDTH/2.0);
    y.push_back(SCREEN_HEIGHT/2.0 - 50);
    dx = 0;
    dy = 0;
    ddx = 0;
    ddy = 0.3;
    change_press_dx = 0;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

void Player2::handleEvent(SDL_Event event, int &status, vector<Mix_Chunk*> sound)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
    {
        if(event.key.keysym.sym == SDLK_RETURN && event.key.repeat == 0)
        {
            if(status == GOING_RIGHT)
            {
                //dx = (-1)*change_press_dx; //change in velocity when press SPACE
                dy = change_press_dy;
                ddy = 0.3;
            }
            else if(status == GOING_LEFT)
            {
                //dx = change_press_dx;
                dy = change_press_dy;
                ddy = 0.3;
            }
            is_key_pressed = true;
        }
        break;
    }
    }
}

void Player2::reset()
{
    x.at(0)=(SCREEN_WIDTH/2.0-26);
    y.at(0)=(SCREEN_HEIGHT/2.0-90);
    dx = -3;
    dy = 0;
    ddx = 0;
    ddy = 0.3;
    change_press_dx = 0;
    change_press_dy = -7.5;
    //is_key_pressed = false;
}

void Player2::update(int &status, int &score, bool &is_hitting_wall)
{
//  Player2 stop using is_hitting_wall and score to prevent error.
    if(status == GOING_RIGHT)
    {
        //dx -= ddx;
        dy += ddy;
    }
    else if(status == GOING_LEFT)
    {
        //dx += ddx;
        dy += ddy;
    }

    x.at(0) += dx;
    y.at(0) += dy;
    if(x.at(0) > SCREEN_WIDTH-48-20)
    {
        x.at(0) = SCREEN_WIDTH-48-20;
        dx *= -1; //fix de chim dap tuong tu nhien hon
        dy *= 0.9;
        //status = GOING_LEFT;
        //is_hitting_wall = true; //for playing sound effect
        //score++;

    }
    else if(x.at(0) < 18)
    {
        x.at(0) = 18;
        dx *= -1;
        dy *= 0.9;
        //status = GOING_RIGHT;
        //is_hitting_wall = true;
        //score++;
    }
    else
    {
        //is_hitting_wall = false;
    }

    if(y.at(0) > SCREEN_HEIGHT-70-48)
    {
        y.at(0) = SCREEN_HEIGHT-70-48;
        status = DEATH;
    }
    if(y.at(0) < 24)
    {
        y.at(0) = 24;
        status = DEATH;
    }

}
