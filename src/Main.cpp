#include <SDL.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720
//bounds of drawing area
SDL_Rect rect;

using namespace std;
bool running,lmb;

SDL_Window *window;
SDL_Renderer *renderer;

void init();
void mainLoop();
void clear();
void drawAtMouse();
void solve();

double input[32][24];

int main(int argc, char** argv){
    init();
    return 0;
}

void init(){
    rect.x = 0;
    rect.y = 0;
    rect.h = 320;
    rect.w = 240;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Number Recognition", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    running = true;
    clear();
    mainLoop();
}

void mainLoop(){
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    int c = event.key.keysym.scancode;
                    if (c == SDL_SCANCODE_C){
                        clear();
                    }else if(c == SDL_SCANCODE_E){
                        solve();
                    }
                    break;
            }
        }
        drawAtMouse();
    }
}

void clear(){
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 24; j++){
            input[i][j] = 0;
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_RenderPresent(renderer);
}

void drawAtMouse(){
    int mx,my;
    Uint32 buttons;
    SDL_PumpEvents();
    buttons = SDL_GetMouseState(&mx,&my);
    if ((buttons & SDL_BUTTON_LMASK) != 0) {
        //turns mouse click into a 10x10 pixel
        SDL_Rect r;
        r.h = 10;
        r.w = 10;
        r.x = 10*(mx/10);
        r.y = 10*(my/10);
        if(mx < rect.w && my < rect.h){
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            SDL_RenderFillRect(renderer,&r);
            SDL_RenderPresent(renderer);
            input[my/10][mx/10] = 1;
        }
    }
}

void solve(){
    //print out the array of pixels
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 24; j++){
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}