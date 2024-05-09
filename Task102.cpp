#include<stdio.h>

#include<SDL2/SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;

int SCREEN_HEIGHT = 640;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

bool gameStarting = false;

int radius = 30;

int centerx = SCREEN_WIDTH/2;

int centery = SCREEN_HEIGHT/2;

bool initialize_window()
{
    if(SDL_Init(SDL_INIT_VIDEO) !=  0)
    {
        printf("ERROR INITIALIZING SDL!");
        return false;
    }

    window=SDL_CreateWindow("Amit's Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH , SCREEN_HEIGHT, 0);
    
    if(!window) 
    {
         return false;
    }

    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer)
    {
        return false;
    }

    return true;
}

void setup()
{
    SDL_SetRenderDrawColor(renderer, 70, 80, 90, 255);

    SDL_RenderClear(renderer);

    SDL_Color color = {0,0,0,0};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

}

void drawSolidCircle(SDL_Renderer* renderer, int cenx, int ceny, int rad)
{
    for (int x = -rad; x <= rad; x++)
    {
        for (int y = -rad; y <= rad; y++) 
        {
            if (x * x + y * y <= rad * rad) 
            {
                SDL_RenderDrawPoint(renderer, cenx + x, ceny + y);
            }
        }
    }
}

void update()
{
    radius += 10;

    if(radius > 330)
    {
        radius = 30;
    }

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255, 200, 150, 255);

    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
}

void render()
{
    drawSolidCircle(renderer, centerx, centery, radius);

    SDL_RenderPresent(renderer);
}

void destroyWindow()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    gameStarting= initialize_window();

    while(gameStarting != false)
    {
        update();

        render();
    } 

   destroyWindow(); 
   return 0;
}