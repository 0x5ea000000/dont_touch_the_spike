#ifndef CAVEMODE_H
#define CAVEMODE_H

#include "ClassicMode.h"

using namespace std;

class CaveMode: public ClassicMode
{
public:
    CaveMode();
    ~CaveMode();

    void update(bool &end_loop, int &mode);
    void render(SDL_Renderer* renderer, bool end_loop);
    void reset();
protected:
    float depth;
private:

};

#endif // CAVEMODE_H
