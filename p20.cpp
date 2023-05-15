#include <stdio.h>
#include <stdlib.h>

#define NUM_PARTITIONS 6

int partitions[NUM_PARTITIONS] = {300, 600, 350, 200, 750, 125};
int allocated[NUM_PARTITIONS] = {0};

void worst_fit(int process_size) {
  int i, j, max_index = -1, max_size = -1;

  for (i = 0; i < NUM_PARTITIONS; i++) {
    if (allocated[i] == 0 && partitions[i] >= process_size) {
      if (partitions[i] > max_size) {
        max_size = partitions[i];
        max_index = i;
      }
    }
  }

  if (max_index == -1) {
    printf("Cannot allocate %d KB\n", process_size);
  } else {
    allocated[max_index] = 1;
    printf("Allocated %d KB to process of size %d KB\n", partitions[max_index], process_size);
  }
}

int main() {
  worst_fit(115);
  worst_fit(500);
  worst_fit(358);
  worst_fit(200);
  worst_fit(375);

  return 0;
}
