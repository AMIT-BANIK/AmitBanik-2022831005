#include<stdio.h>

#include<SDL2/SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;

int SCREEN_HEIGHT = 480;

SDL_Window* window=NULL;

SDL_Renderer* renderer=NULL;

bool gameStarting=false;

int radius1 = 80;

int centerx1 = -radius1;

int centery1 = SCREEN_HEIGHT/2;

int radius2 = 20;

int centerx2 = SCREEN_WIDTH/2;

int centery2 = radius2;

bool initialize_window()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
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
void process_input()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
         if(event.type == SDL_KEYDOWN)//to move circle pressing keys
         {
           if(SDLK_RIGHT==event.key.keysym.sym)
           {
            centerx2 += 5;
           }

            else if(SDLK_LEFT==event.key.keysym.sym)
            {
                centerx2 -= 5;
            }

            else if(SDLK_UP==event.key.keysym.sym)
            {
                centery2-=5;
            }
            else if(SDLK_DOWN==event.key.keysym.sym)
            {
                centery2 += 5;
            }
         }

        else if (event.type == SDL_QUIT)
        {
            gameStarting = false;
        }
    }
}

void drawSolidCircle(SDL_Renderer* renderer, int cenx1, int ceny1, int radius1)
{
    for (int x = -radius1; x <= radius1; x++)
    {
        for (int y = -radius1; y <= radius1; y++) 
        {
            if (x * x + y * y <= radius1 * radius1) 
            {
                SDL_RenderDrawPoint(renderer, cenx1 + x, ceny1 + y);
            }
        }
    }
}

void update()
{
    centerx1 +=2;

    if(centerx1 - radius1 >= SCREEN_WIDTH)

    centerx1 = -radius1;

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 200, 150, 255);

    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
}
void render()
{
    drawSolidCircle(renderer, centerx1, centery1, radius1);

    SDL_RenderPresent(renderer);

    drawSolidCircle(renderer, centerx2, centery2, radius2);

    SDL_RenderPresent(renderer);
}
void collision()
{
    
    int displacement = sqrt((centerx1-centerx2) * (centerx1 - centerx2) + (centery1-centery2) * (centery1-centery2));
    if(displacement <= radius1 + radius2)
    {
    SDL_Rect r;
    r.x = 0;

    r.y = 0;

    r.w = SCREEN_WIDTH;

    r.h = SCREEN_HEIGHT;

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0,100, 50, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 200, 150, 25, 255);

    SDL_RenderDrawRect(renderer,&r);

    SDL_RenderPresent(renderer);
    }
}

void destroyWindow()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    gameStarting=initialize_window();

    while(gameStarting!=false)
    { 
        process_input();

        update();

        render();
        
        collision();
    } 

   destroyWindow();
   return 0;
}