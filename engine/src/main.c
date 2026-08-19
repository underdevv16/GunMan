#include <stdio.h>
#include<stdbool.h>
#include<glad/glad.h>
#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>

#include "engine_/global.h"

int main(int argc, char *argv[]){

    render_init();

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

        render_begin();
        render_quad(
            (vec2){global.render.width * 0.5, global.render.height * 0.5},
            (vec2){50, 50},
            (vec4){1,1,1,1}
        );

        render_end();
    }

    puts("Hello there!");
    return 0;
}