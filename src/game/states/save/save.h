#ifndef GF2D_SAVE_H
#define GF2D_SAVE_H

#include <memory.h>
#include <sys/stat.h>

#define SAVE_FOLDER "./saves/"

/**
 * Find the name of a file in the saves folder
 * @param file_name - The file name we want to save
 * @param save_file_name - The destination of the completed game
 */
static inline void save_folder_name(const char *file_name, char save_file_name[512]) {

    // Make sure save folder exists
    struct stat st = {0};

    if (stat(SAVE_FOLDER, &st) == -1) {
        mkdir(SAVE_FOLDER, 0700);
    }


    // Add the save folder prefix
    strcpy(save_file_name, SAVE_FOLDER);

    // Skip any bad file data
    while (file_name[0] == '.' || file_name[0] == '/')
        file_name++;

    strcat(save_file_name, file_name);
}

#endif
