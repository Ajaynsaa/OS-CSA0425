#include <stdio.h>
#include <stdint.h>

#define DISK_BLOCK_SIZE 8192 // 8 KB
#define POINTER_SIZE 4 // Bytes

// Constants for the file system structure
#define DIRECT_BLOCKS 12
#define SINGLE_INDIRECT_BLOCKS (DISK_BLOCK_SIZE / POINTER_SIZE)
#define DOUBLE_INDIRECT_BLOCKS (DISK_BLOCK_SIZE / POINTER_SIZE * DISK_BLOCK_SIZE / POINTER_SIZE)
#define TRIPLE_INDIRECT_BLOCKS (DISK_BLOCK_SIZE / POINTER_SIZE * DISK_BLOCK_SIZE / POINTER_SIZE * DISK_BLOCK_SIZE / POINTER_SIZE)

// Function to calculate the maximum file size
uint64_t calculateMaxFileSize() {
    uint64_t maxFileSize = 0;

    // Calculate the maximum file size using the file system structure
    maxFileSize += DIRECT_BLOCKS * DISK_BLOCK_SIZE; // Direct blocks
    maxFileSize += SINGLE_INDIRECT_BLOCKS * DISK_BLOCK_SIZE; // Single indirect blocks
    maxFileSize += DOUBLE_INDIRECT_BLOCKS * DISK_BLOCK_SIZE * SINGLE_INDIRECT_BLOCKS; // Double indirect blocks
    maxFileSize += TRIPLE_INDIRECT_BLOCKS * DISK_BLOCK_SIZE * SINGLE_INDIRECT_BLOCKS * SINGLE_INDIRECT_BLOCKS; // Triple indirect blocks

    return maxFileSize;
}

int main() {
    uint64_t maxFileSize = calculateMaxFileSize();

    printf("Maximum file size: %lu bytes\n", maxFileSize);

    return 0;
}

