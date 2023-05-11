#include <stdio.h>
#include <stdlib.h>

struct MemoryBlock {
    int size;
    int is_allocated;
};

int find_best_fit_block(struct MemoryBlock memory_blocks[], int num_blocks, int process_size) {
    int best_fit_index = -1;
    int best_fit_size = __INT_MAX__;

    for (int i = 0; i < num_blocks; i++) {
        if (!memory_blocks[i].is_allocated && memory_blocks[i].size >= process_size) {
            if (memory_blocks[i].size < best_fit_size) {
                best_fit_index = i;
                best_fit_size = memory_blocks[i].size;
            }
        }
    }

    return best_fit_index;
}

int main() {
    int num_blocks, num_processes;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    struct MemoryBlock memory_blocks[num_blocks];

    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &memory_blocks[i].size);
        memory_blocks[i].is_allocated = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int process_sizes[num_processes];

    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        scanf("%d", &process_sizes[i]);
    }

    // Allocate memory blocks to processes using best-fit algorithm

    printf("Memory blocks and process sizes:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: size=%d\n", i, memory_blocks[i].size);
    }
    for (int i = 0; i < num_processes; i++) {
        int best_fit_index = find_best_fit_block(memory_blocks, num_blocks, process_sizes[i]);
        if (best_fit_index != -1) {
            memory_blocks[best_fit_index].is_allocated = 1;
            printf("Process %d allocated to block %d with size %d\n", i, best_fit_index, memory_blocks[best_fit_index].size);
        } else {
            printf("Process %d could not be allocated to any block\n", i);
        }
    }

    return 0;
}

