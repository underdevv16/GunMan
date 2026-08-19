#ifndef GLOBAL_H
#define GLOBAL_H

#include "render/render.h"

typedef struct global{
    Render_State render;
} Global;

extern Global global;

#endif

// Currently, this is an extern variable => Declared here, but no memory assigned yet.