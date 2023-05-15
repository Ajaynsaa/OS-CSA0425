#include <stdio.h>
#include <stdlib.h>

// Function to sort the array in ascending order
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the index of the disk location to start serving
int findIndex(int arr[], int n, int head) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > head) {
            return i;
        }
    }
    return n;
}

// Function to calculate the total head movement
int calculateHeadMovement(int arr[], int n, int head, int direction) {
    int totalMovement = 0;
    int index = findIndex(arr, n, head);

    // If direction is left, traverse from right to left
    if (direction == -1) {
        for (int i = index - 1; i >= 0; i--) {
            totalMovement += abs(arr[i] - head);
            head = arr[i];
        }
        // Add head movements to the leftmost and then move to the rightmost
        totalMovement += head + (arr[0] - 0);
        head = 0;

        // Traverse from left to right
        for (int i = 1; i < index; i++) {
            totalMovement += abs(arr[i] - head);
            head = arr[i];
        }
    }
    // If direction is right, traverse from left to right
    else if (direction == 1) {
        for (int i = index; i < n; i++) {
            totalMovement += abs(arr[i] - head);
            head = arr[i];
        }
        // Add head movements to the rightmost and then move to the leftmost
        totalMovement += (199 - head) + (199 - arr[n - 1]);
        head = 199;

        // Traverse from right to left
        for (int i = n - 2; i >= index; i--) {
            totalMovement += abs(arr[i] - head);
            head = arr[i];
        }
    }

    return totalMovement;
}

int main() {
    int n, head, direction;
    int *requests;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    requests = (int *)malloc(n * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (1 for right, -1 for left): ");
    scanf("%d", &direction);

    // Sort the requests
    sort(requests, n);

    // Calculate the total head movement
    int totalMovement = calculateHeadMovement(requests, n, head, direction);

    // Calculate the average head movement
    float averageMovement = (float)totalMovement / n;

    printf("Total head movement: %d\n", totalMovement);
    printf("Average head movement: %d\n",averageMovement);
    return 0;
}

