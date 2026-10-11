#include "glad/glad.h"

#include "../global.h"
#include "render.h"
#include "render_internal.h"

static Render_State_Internal state = {0};  // Stores any state that we need to share inside the render module.

void render_init(void) {
    global.render.width = 800;
    global.render.height = 600;
    global.render.window = render_init_window(global.render.width, global.render.height);

    render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
    // Calling the new init functions with required pointers:
    render_init_shaders(&state);
    render_init_color_texture(&state.texture_color);
}


void render_begin(void) {
    glClearColor(0.08, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


void render_end(void) {  // Calls an SDL function
    SDL_GL_SwapWindow(global.render.window);
}


void render_quad(vec2 pos, vec2 size, vec4 color) {

    // Using shader program now and transforming the quad:
    glUseProgram(state.shader_default);

    // Create a model, then reset it to an Identity matrix.
    mat4x4 model;
    mat4x4_identity(model);

    // Remove the quad using translate, and scale it using scale_aniso
    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    // Send the model and color data to shader using uniforms:
    glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glad_glGetUniformLocation(state.shader_default, "color"), 1, color);

    // -------------------------------------------------------- Prior to shader, just for rendering the quad
    glBindVertexArray(state.vao_quad);

    // Binding the texture that we created and removing polygonMode call:
    glBindTexture(GL_TEXTURE_2D, state.texture_color);    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);  // Tells OpenGL to draw something made of Triangles.

    glBindVertexArray(0);
}


// There are 3 buffers that make up everything that we seen drawn - color, depth and stencil buffers.