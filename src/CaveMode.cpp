#include "CaveMode.h"

using namespace std;

CaveMode::CaveMode()
{
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
    depth = 0;
}

CaveMode::~CaveMode()
{

    sound.clear();
    sound.shrink_to_fit();
}

void CaveMode::update(bool &end_loop, int &mode)
{
    depth+=0.02;
    bird.update(status, score, is_hitting_wall);
    spike.update(status, score, is_hitting_wall);
    spike.MoveInCave();
//    item.update(status, is_hitting_wall);
//    item.itemAnimation();
//    item.checkIfEaten(bird, score, sound);
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
    if(is_hitting_wall == true)
    {
        bird.setInvincible(false);
    }

    if(bird.getY(0) <= 30 || bird.getY(0) >= SCREEN_HEIGHT-48-70)
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

void CaveMode::render(SDL_Renderer* renderer, bool end_loop)
{
    if(!end_loop)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        if(status == GOING_RIGHT)
        {
            bird.render(frame/3+6, bird.getX(0), bird.getY(0), bird.getWidth(7), bird.getHeight(7), renderer, 0, NULL,SDL_FLIP_NONE);
            bird.render(10, bird.getX(0)+40, bird.getY(0)-98, bird.getWidth(10), bird.getHeight(10), renderer, 0, NULL,SDL_FLIP_NONE);

            background.render(4, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

//            if(!item.getItemState())
//                item.render(item.getItemType(), item.getX(0), item.getY(0), item.getWidth(0), item.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE); //if item hasn't been eaten

            for (int i = 0; i< (spike.getSpikeNumber()); i++)
            {
                spike.render(1, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else if(status == GOING_LEFT)
        {
            bird.render(frame/3+6, bird.getX(0), bird.getY(0), bird.getWidth(7), bird.getHeight(7), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);
            bird.render(10, bird.getX(0)-200, bird.getY(0)-100, bird.getWidth(10), bird.getHeight(10), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);

            background.render(4, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

//            if(!item.getItemState())
//                item.render(item.getItemType(), item.getX(0), item.getY(0), item.getWidth(0), item.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE); //if item hasn't been eaten
            for (int i = 0; i< spike.getSpikeNumber(); i++)
            {
                spike.render(1, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
            }
        }
        else if(status >= DEATH)
        {
            background.render(4, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);
            background.render(1, (SCREEN_WIDTH-background.getWidth(1))/2, (SCREEN_HEIGHT-background.getHeight(1))/2-50, background.getWidth(1), background.getHeight(1), renderer, 0, NULL, SDL_FLIP_NONE);
        }
        s_score.renderScoreCave(renderer, depth);
        frame++;
        if(frame/3 >= 3)
            frame = 0;

        SDL_RenderPresent(renderer);
        if (status >= DEATH)
        {
            SDL_Delay(1500);
        }
    }
}

void CaveMode::reset()
{
    bird.reset();
    spike.reset();
    rock.reset();
    item.reset();
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
    depth = 0;
}
