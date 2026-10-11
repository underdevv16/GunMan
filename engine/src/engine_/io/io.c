#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../types.h"
#include "../utils.h"
#include "io.h"

// 20 Mib, but can be changed to a higher value depending on target platform
#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "Error reading file: %s. Errorno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough memory to read file: %s\n"

File io_file_read(const char *path) {
    File file = { .is_valid = false };

    /*
        Not using the fseek function to open files as it may cause errors/ undefined behaviours when dealing with binary files
    */

    // 1. Open the file for reading in binary format
    File *fp = fopen(path, "rb");       // Returns the file pointer
    if(ferror(fp)){
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    // 2. Allocate another chunk's worth of memory for the data buffer

    char *data = NULL;  // To hold the data from the file
    char *tmp;
    size_t used = 0;    // How many bytes have been read so far
    size_t size = 0;    // For the next size to be allocated
    size_t n;           // How many bytes were read on each iteration

    while (true){
        if(used + IO_READ_CHUNK_SIZE + 1 > size){
            size = used + IO_READ_CHUNK_SIZE + 1;

            if(size <= used){
                free(data);
                ERROR_RETURN(file, "Input file too large: %s\n", path);
            }

            tmp = realloc(data, size);
            if(!tmp){
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
            }

            data = tmp;
        }

        // 3. Reading data from the file using fread returns the amounts of bytes read.
        // If it is zero => We reached the end of the file so we break out. 
        // Otherwise, we just add the amount of bytes read and go again from the top.
        // We follow this process till the file is read, and check the errors again and resize the data buffer to the correct size.
        // A null terminator is added to the end.

        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
        if (n==0){
            break;
        }

        used += n;
    }

    if(ferror(fp)){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    tmp = realloc(data, used+1);
    if(!tmp){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
    }

    data = tmp;
    data[used] = 0;

    file.data = data;
    file.len = used;
    file.is_valid = true;

    return file;
}

int io_file_write(void *buffer, usize size, const char *path){
    return 0; // For now.
}