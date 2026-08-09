#include <stdio.h>
#include<stdbool.h>
#include<glad/glad.h>
#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>

int main(int argc, char *argv[]){

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);  // OpenGL profile type = Core
    SDL_GL_SetAttribute(SDL_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_MINOR_VERSION, 3);
    
    // Initialising SDL:
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not initiate SDL: %s \n", SDL_GetError());
        exit(1);
    }

    // Specifying a pointer to the SDL window
    SDL_Window *window = SDL_CreateWindow(
        "GunMan",                 // Title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,   // Centering the window using the macro provided by SDL
        800,                      // Width
        600,                      // Height
        SDL_WINDOW_OPENGL         // Flag to specify to SDL that OpenGL will be used 
    );

    if(!window){
        printf("Failed to create OpenGL window: %s \n", SDL_GetError());
        exit(1);
    }

    // Creating an OpenGL context:
    SDL_GL_CreateContext(window);
    
    // Glad loads all the pointers in the right places in the memory so that we can use them.
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        printf("Failed to load GL: %s \n", SDL_GetError());
        exit(1);
    } 

    // Putting some info on the terminal in case of successful OpenGL load

    puts("OpenGL Loaded!");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Creating a bool for storing quit event:
    // The quit event will come from the OS
    bool should_quit = false;

    while(!should_quit){
        SDL_Event event;

        // To get events from SDL, use the Poll Events function
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    should_quit = true;
                    break;
                default:
                    break;
            }
        }
    }

    puts("Hello there!");
    return 0;
}