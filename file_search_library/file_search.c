#include "file_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_THREADS 8

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static bool stop_search = false;
static bool search_message_displayed = false;

// Function to recursively search for a file in a directory
int search_in_directory(const char *dir_path, const char *filename) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("Error opening directory");
        return 0;
    }

    // Display search message only once
    if (!search_message_displayed) {
        printf("Search may take some time...\n");
        search_message_displayed = true;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (stop_search) {
            break;
        }

        // Skip current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            if (errno == ENOENT || errno == EACCES) {
                // Skip inaccessible directories or directories that don't exist
                continue;
            } else {
                perror("Error getting file status");
                break;
            }
        }

        if (S_ISDIR(file_stat.st_mode)) {
            // Recursively search in subdirectories
            search_in_directory(full_path, filename);
        } else if (strcmp(entry->d_name, filename) == 0) {
            // File found, lock mutex and set stop_search flag
            pthread_mutex_lock(&mutex);
            printf("File found: %s\n", full_path);
            stop_search = true;
            pthread_mutex_unlock(&mutex);
        }
    }

    // If file not found, display error message and set stop_search flag
    if (!stop_search) {
        printf("File \"%s\" not found.\n", filename);
        stop_search = true;
    }
    closedir(dir);

    return 0;
}

// Function to start the file search process
int start_file_search(const char *filename) {
    pthread_t threads[MAX_THREADS];
    search_message_displayed = false;
    search_in_directory("C:\\", filename);

    return 0;
}