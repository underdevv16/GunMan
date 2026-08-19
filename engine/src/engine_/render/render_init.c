#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../utils.h"
#include "../global.h"

#include "render.h"
#include "render_internal.h"

SDL_Window *render_init_window(u32 width, u32 height){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);  // OpenGL profile type = Core
    SDL_GL_SetAttribute(SDL_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_MINOR_VERSION, 3);
    
    // Initialising SDL:
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        ERROR_EXIT("Could not initiate SDL: %s \n", SDL_GetError());
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
        ERROR_EXIT("Failed to create OpenGL window: %s \n", SDL_GetError());
    }

    // Creating an OpenGL context:
    SDL_GL_CreateContext(window);
    
    // Glad loads all the pointers in the right places in the memory so that we can use them.
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        ERROR_EXIT("Failed to load GL: %s \n", SDL_GetError());
    } 

    // Putting some info on the terminal in case of successful OpenGL load

    puts("OpenGL Loaded!");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    
    return window;
}


void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo){

    //   x      y   z  u  v      -> Coordinates ({x, y & z} for normal positioning, and {u,v} for mapping a texture on top.)  
    f32 vertices[] = {
         0.5,  0.5, 0, 0, 0,
         0.5, -0.5, 0, 0, 1,
        -0.5, -0.5, 0, 1, 1,
        -0.5,  0.5, 0, 1, 0
    };

    u32 indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Generating vertex arrays and buffers to store the data:
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // For position coordinates {x, y, z}
    // 0 => Attribute index (here 0 and 1)
    // 3 => Number of elements (here 3 -> x, y and z)
    // GL_FLOAT => Type
    // GL_FALSE => Whether OpenGL needs to normalize the float
    // 5 * sizeof(f32) => Stride**
    // NULL => Represents offset. Null means no offset, and for U-Vs, offset is 3 * sizeof(f32), as we need to bypass x, y and z.
    // We need to cast the offset to a void pointer.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
    glEnableVertexAttribArray(0);

    // For texture coordinates {u, v}
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glad_glEnableVertexAttribArray(1);

    // Finally, unbind the VAO:
    glBindVertexArray(0);
}



// VAOs -> like a preset which basically tell OpenGL when we bind this preset, we want it to point to this data and use it.
// The data is whatever the vbo and/or ebo buffers we specify, as VBOs and EBOs are just arrays of data.
// Since OpenGL is a state machine, it can only access the currently bound arrays and buffers. Therefore, to update data in a particular
// buffer, it must be bound.
// The vertices array go into the vbo, and indices array into the ebo.
// Then, we just need to tell OpenGL how to read the data we just put in the buffer. This can be done using: glVertexAttribPointer function.

// Stride** -> How many elements we need to move from the first x to get to the next x. 