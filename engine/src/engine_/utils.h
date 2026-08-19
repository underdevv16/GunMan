#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define ERROR_EXIT(...) fprintf(stderr, __VA_ARGS__)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R

#endif

// Here, macros (text substitution rule handled by the C preprocessor before the actual compilation happens) are used.