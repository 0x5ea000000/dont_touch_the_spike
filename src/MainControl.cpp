#include "MainControl.h"
#include <fstream>
using namespace std;

int MainControl::WIDTH;
int MainControl::HEIGHT;

MainControl::MainControl()
{
    window = NULL;
    renderer = NULL;
    end_loop = false;
    mode = MENU;
    high_score = 0;
}

MainControl::~MainControl()
{

}

void MainControl::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void MainControl::initializeSDL(string window_title, const int&x, const int& y, const int& width, const int& height, const int& screen_option)
{

    WIDTH = width;
    HEIGHT = height;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(window_title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        logSDLError(cout, "SDL_CreateWindow", true);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        logSDLError(cout, "SDL_CreateRenderer", true);
    }

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        logSDLError(cout, "IMG_Init", true);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logSDLError(cout, "Mix_OpenAudio", true);
    }

    main_menu.loadMedia(renderer);
    classic_mode.loadMedia(renderer);
    hard_mode.loadMedia(renderer);
    duel_mode.loadMedia(renderer);
    cave_mode.loadMedia(renderer);
    bot_mode.loadMedia(renderer);
}

void MainControl::setMode()
{
    ifstream infile ("data.txt");
    if( infile.is_open() )
    {
        infile >> high_score;
    }
    else
    {
        high_score = 0;
    }
    infile.close();
    switch(mode)
    {
    case MENU:
    {
        main_menu.reset();
        while(!end_loop)
        {
            main_menu.setHighScore(high_score);
            main_menu.handleEvent(event, end_loop, mode);
            main_menu.update(end_loop, mode);
            if(mode != MENU)
                break;
            main_menu.render(renderer, end_loop);
        }
        break;
    }
    case CLASSIC:
    {
        classic_mode.reset();
        while(!end_loop)
        {
            classic_mode.handleEvent(event, end_loop, mode);
            classic_mode.update(end_loop, mode);
            classic_mode.playSound();
            if(mode != CLASSIC)
            {
                reset();
                break;
            }
            classic_mode.render(renderer, end_loop);
            if(high_score < classic_mode.getScore())
            {
                high_score = classic_mode.getScore();
            }
        }
        break;
    }
    case HARD:
    {
        hard_mode.reset();
        while(!end_loop)
        {
            hard_mode.handleEvent(event, end_loop, mode);
            hard_mode.update(end_loop, mode);
            hard_mode.playSound();
            if(mode != HARD)
            {
                reset();
                break;
            }
            hard_mode.render(renderer, end_loop);
            if(high_score < hard_mode.getScore())
            {
                high_score = hard_mode.getScore();
            }
        }
        break;
    }
    case DUEL:
    {
        duel_mode.reset();
        while(!end_loop)
        {
            duel_mode.handleEvent(event, end_loop, mode);
            duel_mode.update(end_loop, mode);
            duel_mode.playSound();
            if(mode != DUEL)
            {
                reset();
                break;
            }
            duel_mode.render(renderer, end_loop);
        }
        break;
    }
    case CAVE:
    {
        cave_mode.reset();
        while(!end_loop)
        {
            cave_mode.handleEvent(event, end_loop, mode);
            cave_mode.update(end_loop, mode);
            cave_mode.playSound();
            if(mode != CAVE)
            {
                reset();
                break;
            }
            cave_mode.render(renderer, end_loop);
        }
        break;
    }
    case BOT:
    {
        bot_mode.reset();
        while(!end_loop)
        {
            bot_mode.handleEvent(event, end_loop, mode);
            bot_mode.update(end_loop, mode);
            bot_mode.playSound();
            if(mode != BOT)
            {
                reset();
                break;
            }
            bot_mode.render(renderer, end_loop);
        }
        break;
    }
    }
    ofstream outfile("data.txt");
    if(outfile.is_open())
    {
        outfile << high_score;
    }
    outfile.close();
}

void MainControl::reset()
{
    mode  = MENU;
}

void MainControl::close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Window* MainControl::getWindow() const
{
    return window;
}

SDL_Renderer* MainControl::getRenderer()const
{
    return renderer;
}

bool MainControl::isEndLoop() const
{
    return end_loop;
}

int MainControl::getWidth()
{
    return WIDTH;
}

int MainControl::getHeight()
{
    return HEIGHT;
}
