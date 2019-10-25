#include "BotMode.h"

BotMode::BotMode()
{
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
    winner = 0;
    delay_after_hit_wall = 0;
}

BotMode::~BotMode()
{
    sound.clear();
    sound.shrink_to_fit();
}
void BotMode::loadMedia(SDL_Renderer* renderer)
{
    background.loadMedia(renderer);
    player1.loadMedia(renderer);
    player2.loadMedia(renderer);
    spike.loadMedia(renderer);
    s_score.loadMedia(renderer);
    item.loadMedia(renderer);

    sound.push_back(Mix_LoadWAV("assets/audio/jump.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/point.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/dead.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/candy.wav"));
}

void BotMode::handleEvent(SDL_Event event, bool& end_loop, int &mode)
{
    if(status < DEATH)
    {
        player2.predict(status, sound, spike);
        while(SDL_PollEvent(&event))
        {
            player1.handleEvent(event, status, sound);
            switch(event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                break;
            }
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    status = DEATH;
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
    else if(status >= DEATH)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                break;
            }
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    status = DEATH;
                }
                else if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_d)
                {
                    mode = MENU;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
                mode = MENU;
            default:
            {
                break;
            }
            }
        }
    }
}

void BotMode::update(bool &end_loop, int &mode)
{
    player1.update(status, score, is_hitting_wall);
    player2.update(status, score, is_hitting_wall);
    spike.update(status, score, is_hitting_wall);

    for(int i = 0; i < spike.getSpikeNumber(); i++)
    {
        player1.setCollider(status);
        player2.setCollider(status);
        spike.setCollider(i, status);
        if(checkCollision(player1.getCollider(), spike.getCollider(), 0, 7) == true)
        {
            status = DEATH_1;
        }
        else if(checkCollision(player2.getCollider(), spike.getCollider(), 7, 14) == true)
        {
            status = DEATH_2;
        }

    }
    if(player1.getY(0) == 30 || player1.getY(0) == SCREEN_HEIGHT-70-48)
    {
        status = DEATH_1;
    }
    else if(player2.getY(0) == 30 || player2.getY(0) == SCREEN_HEIGHT-70-48)
    {
        status = DEATH_2;
    }

    if(status >= DEATH)
    {
        player1.pause();
        player2.pause();
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

void BotMode::playSound()
{
    player1.playSound(sound, is_hitting_wall);
    player2.playSound(sound, is_hitting_wall);
}

void BotMode::render(SDL_Renderer* renderer, bool end_loop)
{
    if(!end_loop)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        if(score%5 == 0)
        {
            int temp1 = 200+ rand()%50;
            int temp2 = 200+ rand()%50;
            int temp3 = 200+ rand()%50;
            background.setColor(0, temp1, temp2, temp3);
            background.setColor(1, temp1, temp2, temp3);
            spike.setColor(0, temp1, temp2, temp3);
        }
        if(score == 0)
        {
            background.setColor(0, 255, 255, 255);
            background.setColor(status -1, 255, 255, 255);
            spike.setColor(0, 255, 255, 255);
        }
        background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);
        if(status == GOING_RIGHT)
        {

            player1.render(frame/3, player1.getX(0), player1.getY(0), player1.getWidth(0), player1.getHeight(0), renderer, 0, NULL,SDL_FLIP_NONE);
            player2.render(frame/3+3, player2.getX(0), player2.getY(0), player2.getWidth(0), player2.getHeight(0), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);

            for (int i = 0; i< (spike.getSpikeNumber()); i++)
            {
                spike.render(0, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_HORIZONTAL);
                spike.render(0, SCREEN_WIDTH - spike.getWidth(0) +1 - spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
            }
        }
        else if(status == GOING_LEFT)
        {
            player1.render(frame/3, player1.getX(0), player1.getY(0), player1.getWidth(0), player1.getHeight(0), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);
            player2.render(frame/3+3, player2.getX(0), player2.getY(0), player2.getWidth(0), player2.getHeight(0), renderer, 0, NULL,SDL_FLIP_NONE);

            for (int i = 0; i< spike.getSpikeNumber(); i++)
            {
                spike.render(0, SCREEN_WIDTH - spike.getWidth(0) +2 - spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_HORIZONTAL);
                spike.render(0, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
            }
        }
        else if(status >= DEATH)
        {
            //render match result
            background.render(status - 1, (SCREEN_WIDTH-background.getWidth(status-1)*0.5)/2, (SCREEN_HEIGHT-background.getHeight(status-1))*0.5/2+100, background.getWidth(status-1)*0.5, background.getHeight(status-1)*0.5, renderer, 0, NULL, SDL_FLIP_NONE);

        }

        s_score.renderScore(renderer, score);
        frame++;
        if(frame/3 >= 3)
            frame = 0;

        SDL_RenderPresent(renderer);
        if (status >= DEATH)
        {
            SDL_Delay(1000);
        }
    }
}


void BotMode::reset()
{
    player1.reset();
    player2.reset();
    spike.reset();
    item.reset();
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
}
