#include "Button.h"

using namespace std;

Button::Button()
{
    current_status = 0;
    hitting_button = false;
}

Button::~Button()
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

void Button::loadMedia(SDL_Renderer* renderer)
{

}

void Button::setPosition(int temp_x, int temp_y)
{
    x.push_back(temp_x);
    y.push_back(temp_y);
}

void Button::handleEvent(SDL_Event event)
{
    //If mouse event happened
    if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int current_x, current_y;
        SDL_GetMouseState( &current_x, &current_y );
        //Mouse is left of the button
        if( current_x < x.at(0) )
        {
            current_status = 0;
        }
        //Mouse is right of the button
        else if( current_x > x.at(0) + width.at(0) )
        {
            current_status = 0;
        }
        //Mouse above the button
        else if( current_y < y.at(0) )
        {
            current_status = 0;
        }
        //Mouse below the button
        else if( current_y > y.at(0) + height.at(0) )
        {
            current_status = 0;
        }
        else
        {
            current_status = 1;
        }
        //Mouse is outside button
        if( current_status == 0 )
        {
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( event.type )
            {
                case SDL_MOUSEMOTION:
                break;

                case SDL_MOUSEBUTTONDOWN:
                break;

                case SDL_MOUSEBUTTONUP:
                hitting_button = true;
                break;
            }
        }
    }
}

bool Button::isHittingButton()
{
    return hitting_button;
}


void Button::reset()
{
    current_status = 0;
    hitting_button = false;
}
