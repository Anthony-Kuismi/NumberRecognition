#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

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
void printArray1D(double *arr, int size);
void clearArray1D(double *arr, int size);
void printArray2D(double *arr, int width, int height);
void clearArray2D(double *arr, int width, int height);

const int INPWIDTH = 24, INPHEIGHT = 32, LAYER2NEURONS = 16, LAYER3NEURONS = 16, OUTPUTNUERONS = 10, PIXELWIDTH = 20;
double input[INPHEIGHT*INPWIDTH],w1[LAYER2NEURONS][INPHEIGHT*INPWIDTH],w2[LAYER3NEURONS][LAYER2NEURONS],w3[OUTPUTNUERONS][LAYER3NEURONS];
double a2[LAYER2NEURONS],a3[LAYER3NEURONS],b2[LAYER2NEURONS],b3[LAYER3NEURONS];

int main(int argc, char** argv){
    init();
    return 0;
}

void init(){
    rect.x = 0;
    rect.y = 0;
    rect.h = PIXELWIDTH*INPHEIGHT;
    rect.w = PIXELWIDTH*INPWIDTH;
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
//clears the input
void clear(){
    clearArray1D(input,INPWIDTH*INPHEIGHT);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_RenderPresent(renderer);
}
//Draws a square at the mouse position
void drawAtMouse(){
    int mx,my;
    Uint32 buttons;
    SDL_PumpEvents();
    buttons = SDL_GetMouseState(&mx,&my);
    if ((buttons & SDL_BUTTON_LMASK) != 0) {
        //turns mouse click into a 10x10 pixel
        SDL_Rect r;
        int xConversion = mx/PIXELWIDTH;
        int yConversion = my/PIXELWIDTH;
        r.h = PIXELWIDTH;
        r.w = PIXELWIDTH;
        r.x = PIXELWIDTH*xConversion;
        r.y = PIXELWIDTH*yConversion;
        if(mx < rect.w && my < rect.h){
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            SDL_RenderFillRect(renderer,&r);
            SDL_RenderPresent(renderer);
            //adds mouseclick to input.
            input[INPWIDTH*yConversion+xConversion] = 1;
        }
    }
}
//solves and finds the output
void solve(){
    //computeNextLayer(*w1,INPWIDTH*INPHEIGHT,INPWIDTH*INPHEIGHT ,*input,LAYER2NEURONS, b2,LAYER2NEURONS, a3,LAYER2NEURONS);
    printArray1D(input,INPWIDTH*INPHEIGHT);
}
//takes in a the weights, activation amounts of previous neurons, and the biases.
void computeNextLayer(double *weights,int weightsWidth,int weightsHeight, double *activations, int activationsSize, double *biases,int biasSize, double *nextLayer, int nextLayerSize){
    //take the sigmoid of the vector multiplation of the weights and the activation and add the bias
    
}
//clears a 2D array
void clearArray2D(double *arr, int width, int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j <width; j++){
            *((arr+i*width)+j) = 0;
        }
    }
}
//clears a 1d array
void clearArray1D(double *arr, int size){
    for(int i = 0; i < size; i++){
        arr[i] = 0;
    }
}
//prints 2D array
void printArray2D(double *arr, int width, int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j <width; j++){
            cout << *((arr+i*width)+j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
//prints 1D array
void printArray1D(double *arr, int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl << endl;
}

