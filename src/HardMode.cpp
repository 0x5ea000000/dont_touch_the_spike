#include "HardMode.h"

using namespace std;
HardMode::HardMode()
{
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    frame = 0;
    bird.hardBird(); //change bird speed, ...
}

HardMode::~HardMode()
{
    sound.clear();
    sound.shrink_to_fit();
}

void HardMode::update(bool &end_loop, int &mode)
{
    bird.update(status, score, is_hitting_wall);
    spike.update(status, score, is_hitting_wall);
    spike.moveSpike(); //move the spike up and down, increase the difficulty
    rock.update(score, is_hitting_wall);
    item.update(status, is_hitting_wall);
    item.itemAnimation();
    item.checkIfEaten(bird, score, sound);
    for(int i = 0; i < spike.getSpikeNumber(); i++)
    {
        bird.setCollider(status);
        spike.setCollider(i, status);
        if(checkCollision(bird.getCollider(), spike.getCollider(), 0, 7) == true)
        {
            if(bird.isInvincible() == false)
            {
                status =  DEATH;
            }
        }
    }
    for(int i = 0; i < rock.getRockNumber(); i++)
    {
        bird.setCollider(status);
        rock.setCollider(i);
        if(checkCollision(bird.getCollider(), rock.getCollider()) == true)
        {
            status =  DEATH;
        }
    }

    if(is_hitting_wall == true)
    {
        bird.setInvincible(false);
    }

    if(bird.getY(0) == 30 || bird.getY(0) == SCREEN_HEIGHT-48-70)
    {
        status = DEATH;
    }
    if(status == DEATH)
    {
        bird.pause();
        if (playMusic == false)
        {
            Mix_PlayChannel( -1, sound.at(2), 0 ); //only play once
            playMusic = true;
        }
    }
    else
    {
        playMusic = false;
    }
}

void HardMode::reset()
{
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    frame = 0;
    bird.hardBird();
    spike.reset();
    item.reset();
    rock.reset();
}
