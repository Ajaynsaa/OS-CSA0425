#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_DIRS 10
#define MAX_FILES 10

struct file {
    char name[20];
};

struct directory {
    char name[20];
    struct file files[MAX_FILES];
    int num_files;
};

struct user {
    char name[20];
    struct directory dirs[MAX_DIRS];
    int num_dirs;
};

int main() {
    struct user users[MAX_USERS];
    int num_users = 0;

    // Create users
    strcpy(users[0].name, "user1");
    users[0].num_dirs = 0;
    num_users++;

    strcpy(users[1].name, "user2");
    users[1].num_dirs = 0;
    num_users++;

    // Create directories for user1
    struct directory dir11;
    strcpy(dir11.name, "dir11");
    dir11.num_files = 0;

    struct directory dir12;
    strcpy(dir12.name, "dir12");
    dir12.num_files = 0;

    users[0].dirs[0] = dir11;
    users[0].num_dirs++;
    users[0].dirs[1] = dir12;
    users[0].num_dirs++;

    // Create directories for user2
    struct directory dir21;
    strcpy(dir21.name, "dir21");
    dir21.num_files = 0;

    struct directory dir22;
    strcpy(dir22.name, "dir22");
    dir22.num_files = 0;

    users[1].dirs[0] = dir21;
    users[1].num_dirs++;
    users[1].dirs[1] = dir22;
    users[1].num_dirs++;

    // Add files to directories
    struct file file111;
    strcpy(file111.name, "file111");
    users[0].dirs[0].files[0] = file111;
    users[0].dirs[0].num_files++;

    struct file file122;
    strcpy(file122.name, "file122");
    users[0].dirs[1].files[0] = file122;
    users[0].dirs[1].num_files++;

    struct file file211;
    strcpy(file211.name, "file211");
    users[1].dirs[0].files[0] = file211;
    users[1].dirs[0].num_files++;

    struct file file222;
    strcpy(file222.name, "file222");
    users[1].dirs[1].files[0] = file222;
    users[1].dirs[1].num_files++;

    // Print directory structure
    for (int i = 0; i < num_users; i++) {
        printf("%s\n", users[i].name);
        for (int j = 0; j < users[i].num_dirs; j++) {
            printf("- %s\n", users[i].dirs[j].name);
            for (int k = 0; k < users[i].dirs[j].num_files; k++) {
                printf("-- %s\n", users[i].dirs[j].files[k].name);
            }
        }
    }

    return 0;
}
