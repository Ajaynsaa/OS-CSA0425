#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LEN 20

// Struct to hold information about a file
typedef struct {
    char name[MAX_FILENAME_LEN];
    int size;
} File;

// Struct to hold information about the directory
typedef struct {
    File files[MAX_FILES];
    int num_files;
} Directory;

// Function to add a new file to the directory
void add_file(Directory *dir) {
    // Make sure there is space for the new file
    if (dir->num_files >= MAX_FILES) {
        printf("Directory is full\n");
        return;
    }
    
    // Get the file name and size from the user
    char name[MAX_FILENAME_LEN];
    int size;
    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file size: ");
    scanf("%d", &size);
    
    // Create a new file struct and add it to the directory
    File new_file;
    strcpy(new_file.name, name);
    new_file.size = size;
    dir->files[dir->num_files] = new_file;
    dir->num_files++;
}

// Function to list all files in the directory
void list_files(Directory *dir) {
    if (dir->num_files == 0) {
        printf("Directory is empty\n");
        return;
    }
    printf("Files in directory:\n");
    for (int i = 0; i < dir->num_files; i++) {
        printf("%s (%d bytes)\n", dir->files[i].name, dir->files[i].size);
    }
}

int main() {
    Directory dir;
    dir.num_files = 0;
    
    // Menu loop
    int choice = 0;
    while (choice != 3) {
        printf("1. Add file\n");
        printf("2. List files\n");
        printf("3. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            // Add file
            // Make sure there is space for the new file
            if (dir.num_files >= MAX_FILES) {
                printf("Directory is full\n");
                continue;
            }
            
            // Get the file name and size from the user
            char name[MAX_FILENAME_LEN];
            int size;
            printf("Enter file name: ");
            scanf("%s", name);
            printf("Enter file size: ");
            scanf("%d", &size);
            
            // Create a new file struct and add it to the directory
            File new_file;
            strcpy(new_file.name, name);
            new_file.size = size;
            dir.files[dir.num_files] = new_file;
            dir.num_files++;
        }
        else if (choice == 2) {
            // List files
            if (dir.num_files == 0) {
                printf("Directory is empty\n");
            }
            else {
                printf("Files in directory:\n");
                for (int i = 0; i < dir.num_files; i++) {
                    printf("%s (%d bytes)\n", dir.files[i].name, dir.files[i].size);
                }
            }
        }
        else if (choice == 3) {
            // Quit
            printf("Goodbye\n");
        }
        else {
            // Invalid choice
            printf("Invalid choice\n");
        }
    }
    
    return 0;
}

