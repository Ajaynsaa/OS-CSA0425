#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 100
int main() {
    int requests[MAX_REQUESTS];
    int num_requests, head_position, total_head_movement = 0;
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);
    
    printf("Enter the disk requests sequence:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head_position);
    
    // Calculate the total head movement
    for (int i = 0; i < num_requests; i++) {
        total_head_movement += abs(requests[i] - head_position);
        head_position = requests[i];
    }
    
    printf("Average head movement: %.2f\n", (float)total_head_movement / num_requests);
    
    return 0;
}

