#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Item.h"
#include "Score.h"
#include "Bird.h"
#include "Background.h"
#include "Button.h"
#include "Spike.h"
#include "constant.h"
#include "MainMenu.h"
#include "ClassicMode.h"
#include "HardMode.h"
#include "DuelMode.h"
#include "CaveMode.h"
#include "BotMode.h"

using namespace std;

class MainControl
{
public:
    MainControl();
    ~MainControl();
    void logSDLError(ostream& os, const string &msg, bool fatal = false);
    void initializeSDL(string window_title, const int&x, const int& y, const int& width, const int& height, const int& screen_option);
    void setMode();
    void close();

    void reset();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

    bool isEndLoop() const;

    static int getWidth();
    static int getHeight();

protected:
    static int WIDTH;
    static int HEIGHT;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool end_loop;
    int mode;
    int high_score;

    MainMenu main_menu;
    ClassicMode classic_mode;
    HardMode hard_mode;
    DuelMode duel_mode;
    CaveMode cave_mode;
    BotMode bot_mode;
};

#endif // MAINCONTROL_H
