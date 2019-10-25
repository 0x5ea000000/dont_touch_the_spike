#include "ClassicMode.h"

using namespace std;

ClassicMode::ClassicMode()
{
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
}

ClassicMode::~ClassicMode()
{

    sound.clear();
    sound.shrink_to_fit();
}

void ClassicMode::loadMedia(SDL_Renderer* renderer)
{
    background.loadMedia(renderer);
    bird.loadMedia(renderer);
    spike.loadMedia(renderer);
    s_score.loadMedia(renderer);
    item.loadMedia(renderer);
    rock.loadMedia(renderer);

    sound.push_back(Mix_LoadWAV("assets/audio/jump.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/point.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/dead.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/candy.wav"));

}

void ClassicMode::handleEvent(SDL_Event event, bool& end_loop, int &mode)
{
    if(status != DEATH)
    {
        while(SDL_PollEvent(&event))
        {
            bird.handleEvent(event, status, sound);
            switch(event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                break;
            }
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
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
    else if(status == DEATH)
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
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    status = DEATH;
                }
                else if(event.key.keysym.sym==SDLK_SPACE)
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

void ClassicMode::update(bool &end_loop, int &mode)
{
    bird.update(status, score, is_hitting_wall);
    spike.update(status, score, is_hitting_wall);
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

void ClassicMode::playSound()
{
    bird.playSound(sound, is_hitting_wall);
}

void ClassicMode::render(SDL_Renderer* renderer, bool end_loop)
{
    srand((int) time(0));
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
            rock.setColor(0, temp1, temp2, temp3);
        }
        if(score == 0)
        {
            background.setColor(0, 255, 255, 255);
            background.setColor(1, 255, 255, 255);
            spike.setColor(0, 255, 255, 255);
            rock.setColor(0, 255, 255, 255);
        }
        if(status == GOING_RIGHT)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

            if(bird.isInvincible() == true)
            {
                bird.render(9, bird.getX(0)-12, bird.getY(0)-15, bird.getWidth(9), bird.getHeight(9), renderer, 0, NULL,SDL_FLIP_NONE);
            }

            bird.render(frame/3, bird.getX(0), bird.getY(0), bird.getWidth(0), bird.getHeight(0), renderer, 0, NULL,SDL_FLIP_NONE);

            if(!item.getItemState())
            {
                item.render(item.getItemType(), item.getX(0), item.getY(0), item.getWidth(item.getItemType()), item.getHeight(item.getItemType()), renderer, 0, NULL, SDL_FLIP_NONE); //if item hasn't been eaten
            }
            for (int i = 0; i< (spike.getSpikeNumber()); i++)
            {
                spike.render(0, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_HORIZONTAL);
            }
            for(int i = 0; i < rock.getRockNumber(); i++)
            {
                rock.render(0, rock.getX(i), rock.getY(i), rock.getWidth(0), rock.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);

            }
        }
        else if(status == GOING_LEFT)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

            if(bird.isInvincible() == true)
            {
                bird.render(9, bird.getX(0)-12, bird.getY(0)-15, bird.getWidth(9), bird.getHeight(9), renderer, 0, NULL,SDL_FLIP_NONE);
            }
            bird.render(frame/3, bird.getX(0), bird.getY(0), bird.getWidth(0), bird.getHeight(0), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);

            if(!item.getItemState())
            {
                item.render(item.getItemType(), item.getX(0), item.getY(0), item.getWidth(item.getItemType()), item.getHeight(item.getItemType()), renderer, 0, NULL, SDL_FLIP_NONE); //if item hasn't been eaten
            }

            for (int i = 0; i< spike.getSpikeNumber(); i++)
            {
                spike.render(0, spike.getX(i), spike.getY(i), spike.getWidth(0), spike.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
            }
            for(int i = 0; i < rock.getRockNumber(); i++)
            {
                rock.render(0, rock.getX(i), rock.getY(i), rock.getWidth(0), rock.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);

            }
        }
        else if(status >= DEATH)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);
            background.render(1, (SCREEN_WIDTH-background.getWidth(1))/2, (SCREEN_HEIGHT-background.getHeight(1))/2-50, background.getWidth(1), background.getHeight(1), renderer, 0, NULL, SDL_FLIP_NONE);
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

int ClassicMode::getScore()
{
    return score;
}

void ClassicMode::reset()
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
}
