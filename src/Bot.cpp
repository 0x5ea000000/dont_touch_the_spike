#include "Bot.h"

using namespace std;

Bot::Bot()
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

void Bot::predict(int &status, vector<Mix_Chunk*> sound, Spike &spike)
{
    bool jump = false;
//    srand((int) time(0));
//    if(1)
//    {
//        jump = true;
//    }
    for(int i = 0; i < spike.getSpikeNumber(); i++)
    {
        if(((y.at(0) >= spike.getY(i)-40) &&(y.at(0) <= spike.getY(i)+24))&&(x.at(0)>=60) && (x.at(0)<=SCREEN_WIDTH-60))
        {
            jump = true;
        }
        else if(((y.at(0) >= spike.getY(i)+24) &&(y.at(0) <= spike.getY(i)+80))&&(x.at(0)>=150) && (x.at(0)<=SCREEN_WIDTH-150))
        {
            jump = false;
        }
    }
    if(y.at(0) >= SCREEN_HEIGHT-200)
    {
        jump = true;
    }
    if((jump == true) && (y.at(0)>=150))
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
}
