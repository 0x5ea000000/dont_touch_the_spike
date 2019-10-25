#ifndef BOT_H
#define BOT_H

#include <random>
#include <time.h>

#include "Player.h"
#include "Spike.h"

class Bot: public Player2
{
public:
    Bot();
    void predict(int &status, vector<Mix_Chunk*> sound,  Spike &spike);

protected:
    float PreDy;

private:


};

#endif // BOT_H
