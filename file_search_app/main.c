#include <stdio.h>
#include "../file_search_library/file_search.h" // Include the file search library header

int main() {
    int choice;
    char filename[256];

    // Menu loop to provide options
    do {
        printf("Choose option:\n");
        printf("1. Search for a file\n");
        printf("2. Exit\n");

        scanf("%d", &choice); // Read the user's choice

        switch (choice) {
            case 1:
                printf("Enter the file name and its extension for searching: ");
                scanf("%s", filename);

                start_file_search(filename); // Initiate the file search process
                break;
            case 2:
                printf("Exiting the program...\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please choose again.\n");
                break;
        }
    } while (1); // Loop indefinitely until the user chooses to exit
}