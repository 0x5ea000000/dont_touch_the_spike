#include "Spike.h"
#include "time.h"
#include "random"

using namespace std;

Spike::Spike()
{
    spike_number = 0;
    collider.resize(14);
}

Spike::~Spike()
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

void Spike::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/spike.png", renderer);
    loadFromFile("assets/sprites/spike-cave.png", renderer);
}

void Spike::update(int &status, int &score, bool &is_hitting_wall)
{
    srand((int) time(0));
    if(is_hitting_wall == true) //when bird hit wall, generate randomly-positioned spikes
    {
        setSpikeNumber(score);
        x.clear();
        y.clear();
        if(status == GOING_RIGHT)
        {
            for(int i = 0; i < spike_number; i++)
            {
                x.push_back(SCREEN_WIDTH - width.at(0)-16);
                y.push_back(54 + rand() % (8) * (height.at(0)+8));
            }
        }
        else if(status == GOING_LEFT)
        {
            for(int i = 0; i < spike_number; i++)
            {
                x.push_back(18);
                y.push_back(54 + rand() % (8) * (height.at(0)+8));
            }
        }
    }
}

void Spike::setSpikeNumber(int &score)
{
    if (score <= 1)
        spike_number = 2;
    else if(score <= 6)
        spike_number = 3;
    else if (score <= 16)
        spike_number = 4;
    else if (score <= 30)
        spike_number = 5;
    else if (score <= 50)
        spike_number = 6;
    else if(score <= 80)
        spike_number = 7;
    else
        spike_number = 7;
}

/*Hard Mode*/
void Spike::moveSpike()
{
    for(int i = 0; i < spike_number; i++) //voi tat ca gai
    {
        switch_direction_counter++;
        if (switch_direction_counter > 15*getSpikeNumber())
        {
            y.at(i) -= 2;
            if(switch_direction_counter >= 30*getSpikeNumber())
                switch_direction_counter = 0;
        }
        else
        {
            y.at(i) += 2;
        }
    }
}

int Spike::getSpikeNumber()
{
    return spike_number;
}

void Spike::reset()
{
    spike_number = 0;
}

void Spike::setCollider(int &i, int &status)
{
    if(status == GOING_LEFT)
    {
        collider.at(0).x = x.at(i);
        collider.at(0).y = y.at(i)+4;
        collider.at(0).w = 4;
        collider.at(0).h = 6;

        collider.at(1).x = x.at(i);
        collider.at(1).y = y.at(i)+10;
        collider.at(1).w = 10;
        collider.at(1).h = 6;

        collider.at(2).x = x.at(i);
        collider.at(2).y = y.at(i)+16;
        collider.at(2).w = 16;
        collider.at(2).h = 6;

        collider.at(3).x = x.at(i);
        collider.at(3).y = y.at(i)+22;
        collider.at(3).w = 22;
        collider.at(3).h = 6;

        collider.at(4).x = x.at(i);
        collider.at(4).y = y.at(i)+28;
        collider.at(4).w = 16;
        collider.at(4).h = 6;

        collider.at(5).x = x.at(i);
        collider.at(5).y = y.at(i)+34;
        collider.at(5).w = 10;
        collider.at(5).h = 6;

        collider.at(6).x = x.at(i);
        collider.at(6).y = y.at(i)+40;
        collider.at(6).w = 4;
        collider.at(6).h = 6;


        collider.at(7).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(7).y = y.at(i)+4;
        collider.at(7).w = 4;
        collider.at(7).h = 6;

        collider.at(8).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(8).y = y.at(i)+10;
        collider.at(8).w = 10;
        collider.at(8).h = 6;

        collider.at(9).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(9).y = y.at(i)+16;
        collider.at(9).w = 16;
        collider.at(9).h = 6;

        collider.at(10).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(10).y = y.at(i)+22;
        collider.at(10).w = 22;
        collider.at(10).h = 6;

        collider.at(11).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(11).y = y.at(i)+28;
        collider.at(11).w = 16;
        collider.at(11).h = 6;

        collider.at(12).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(12).y = y.at(i)+34;
        collider.at(12).w = 10;
        collider.at(12).h = 6;

        collider.at(13).x = SCREEN_WIDTH - width.at(0)-17;
        collider.at(13).y = y.at(i)+40;
        collider.at(13).w = 4;
        collider.at(13).h = 6;
    }
    else if(status == GOING_RIGHT)
    {
        collider.at(0).x = x.at(i)+24-4;
        collider.at(0).y = y.at(i)+4;
        collider.at(0).w = 4;
        collider.at(0).h = 6;

        collider.at(1).x = x.at(i)+24-10;
        collider.at(1).y = y.at(i)+10;
        collider.at(1).w = 10;
        collider.at(1).h = 6;

        collider.at(2).x = x.at(i)+24-16;
        collider.at(2).y = y.at(i)+16;
        collider.at(2).w = 16;
        collider.at(2).h = 6;

        collider.at(3).x = x.at(i)+24-22;
        collider.at(3).y = y.at(i)+22;
        collider.at(3).w = 22;
        collider.at(3).h = 6;

        collider.at(4).x = x.at(i)+24-16;
        collider.at(4).y = y.at(i)+28;
        collider.at(4).w = 16;
        collider.at(4).h = 6;

        collider.at(5).x = x.at(i)+24-10;
        collider.at(5).y = y.at(i)+34;
        collider.at(5).w = 10;
        collider.at(5).h = 6;

        collider.at(6).x = x.at(i)+24-4;
        collider.at(6).y = y.at(i)+40;
        collider.at(6).w = 4;
        collider.at(6).h = 6;


        collider.at(7).x = 18;
        collider.at(7).y = y.at(i)+4;
        collider.at(7).w = 4;
        collider.at(7).h = 6;

        collider.at(8).x = 18;
        collider.at(8).y = y.at(i)+10;
        collider.at(8).w = 10;
        collider.at(8).h = 6;

        collider.at(9).x = 18;
        collider.at(9).y = y.at(i)+16;
        collider.at(9).w = 16;
        collider.at(9).h = 6;

        collider.at(10).x = 18;
        collider.at(10).y = y.at(i)+22;
        collider.at(10).w = 22;
        collider.at(10).h = 6;

        collider.at(11).x = 18;
        collider.at(11).y = y.at(i)+28;
        collider.at(11).w = 16;
        collider.at(11).h = 6;

        collider.at(12).x = 18;
        collider.at(12).y = y.at(i)+34;
        collider.at(12).w = 10;
        collider.at(12).h = 6;

        collider.at(13).x = 18;
        collider.at(13).y = y.at(i)+40;
        collider.at(13).w = 4;
        collider.at(13).h = 6;
    }
}
/* Cave mode */
void Spike::MoveInCave()
{
    for(int i = 0; i < spike_number; i++) //voi tat ca gai
    {
        y.at(i)-=2;
    }
}
