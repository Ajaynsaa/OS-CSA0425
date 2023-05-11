#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_numbers(char* name, int start, int end, int increment) {
    printf("%s: ", name);
    for (int i = start; i <= end; i += increment) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
	
    for (int i = 1; i <= 4; i++) {
        if (fork== 0) { // Child process
            printf("Child process %d (pid %d) started\n", i, getpid());

            switch (i) {
                case 1:
                    print_numbers("Odd numbers", 1, 10, 2);
                    break;
                case 2:
                    print_numbers("Even numbers", 2, 10, 2);
                    break;
                case 3:
                    print_numbers("Multiples of 3", 3, 9, 3);
                    break;
                case 4:
                    print_numbers("Multiples of 5", 5, 10, 5);
                    break;
            }

            printf("Child process %d (pid %d) finished\n", i, getpid());
            exit(0);
        }
    }

    // Wait for all child processes to finish
    for (int i = 1; i <= 4; i++) {
        wait(NULL);
    }

    printf("All child processes have finished\n");

    return 0;
}

