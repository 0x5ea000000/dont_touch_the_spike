#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

//đây là base class cho mấy cái class kia
class Texture
{
public:
    void logSDLError(ostream& os, const string &msg, bool fatal);                               //hàm báo lỗi
    void free(SDL_Texture*);                                                                    //hàm giải phóng tài nguyên
    void loadFromFile(string path, SDL_Renderer*);                                              //hàm load file ảnh

    void render(int, int, int, int, int, SDL_Renderer*, double, SDL_Point*, SDL_RendererFlip);  //hàm render (dùng đc trong mọi điều kiện)
    void setColor(const int &i, Uint8 red, Uint8 green, Uint8 blue);

    int getWidth(int i);
    int getHeight(int i);
    float getX(int i);
    float getY(int i);
    vector <SDL_Rect> getCollider();

protected:
    vector <int> width, height;
    vector <float> x, y;
    vector <SDL_Texture*> texture;
    vector <SDL_Rect> collider;

private:

};

bool checkCollision(const vector <SDL_Rect> &a, const vector <SDL_Rect> &b);
bool checkCollision(const vector <SDL_Rect> &a, const vector <SDL_Rect> &b, const int &cap_bot, const int & cap_top);

#endif // TEXTURE_H
