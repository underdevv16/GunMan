#include <glad/glad.h>
#include <stdio.h>

#include "../utils.h"
#include "../io/io.h"
#include "render_internal.h"

// To load the vertex and fragment shaders, then compile and link them, and finally give an id we can refer to.
u32 render_shader_create(const char *path_vert, const char *path_frag){  
    int success;
    char log[512];

    File file_vertex = io_file_read(path_vert);     // Load the vertex shader
    if(!file_vertex.is_valid){
        ERROR_EXIT("Error reading shader: %s\n", path_vert);
    }

    u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);  // Create an id for the vertex shader
    glShaderSource(shader_vertex, 1, (const char *const *)&file_vertex, NULL); //Giving source to opengl
    glCompileShader(shader_vertex); // attempting to compile the shader
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader_vertex, 512, NULL, log);
        ERROR_EXIT("Error compiling the vertex shader: %s\n", log);
    }

    // Doing the same for fragment shader:
    File file_fragment = io_file_read(path_frag);     // Load the fragment shader
    if(!file_fragment.is_valid){
        ERROR_EXIT("Error reading shader: %s\n", path_frag);
    }

    u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);  // Create an id for the fragment shader
    glShaderSource(shader_fragment, 1, (const char *const *)&file_fragment, NULL); //Giving source to opengl
    glCompileShader(shader_fragment); // attempting to compile the shader
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader_fragment, 512, NULL, log);
        ERROR_EXIT("Error compiling the fragment shader: %s\n", log);
    }

    // Once all is well and both shaders are read, create an ID for the final link shader program:
    u32 shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_fragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader, 512, NULL, log);
        ERROR_EXIT("Error Linking shader: %s\n", log);
    }

    free(file_vertex.data);
    free(file_fragment.data);

    return shader;
}
