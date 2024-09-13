#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Function to find the request with the shortest seek time
int findShortestSeek(int *requests, bool *completed, int num_requests, int current_position)
{
    int min_seek_time = 1e9; // Initialize to a very high value
    int index = -1;

    // Find the closest request
    for (int i = 0; i < num_requests; i++)
    {
        if (!completed[i])
        {
            int seek_time = abs(requests[i] - current_position);
            if (seek_time < min_seek_time)
            {
                min_seek_time = seek_time;
                index = i;
            }
        }
    }
    return index;
}

// Function to print the seek operations and movements of the disk head
void printSeekMovement(int *requests, int num_requests, int initial_position)
{
    int current_position = initial_position;
    bool completed[num_requests]; // To track if a request has been completed
    for (int i = 0; i < num_requests; i++)
        completed[i] = false;

    printf("\nDisk Head Movement:\n%d", current_position);

    // Process all requests
    for (int i = 0; i < num_requests; i++)
    {
        int index = findShortestSeek(requests, completed, num_requests, current_position);
        int next_position = requests[index];
        int seek_time = abs(next_position - current_position);

        // Print dashes for the distance traveled
        for (int j = 1; j <= seek_time; j++)
            printf("*");

        // Print the request position and seek time
        printf("%d (Seek Time:%d)", next_position, seek_time);

        // Update the current position and mark the request as completed
        current_position = next_position;
        completed[index] = true;
    }
    printf("\n");
}

// Function to calculate the total seek time for the given requests
int calculateTotalSeekTime(int *requests, int num_requests, int initial_position)
{
    int total_seek_time = 0;
    int current_position = initial_position;
    bool completed[num_requests]; // To track if a request has been completed
    for (int i = 0; i < num_requests; i++)
        completed[i] = false;

    // Calculate the seek time for each request
    for (int i = 0; i < num_requests; i++)
    {
        int index = findShortestSeek(requests, completed, num_requests, current_position);
        total_seek_time += abs(requests[index] - current_position);
        current_position = requests[index];
        completed[index] = true;
    }
    return total_seek_time;
}

int main()
{
    int num_requests, initial_position, disk_size;

    printf("\t*****SSTF Disk Scheduling Algorithm*****\n");
    printf("\t\t**NISHAN DHAKAL**\n\n");

    // Input disk size
    printf("Enter the size of the disk (number of cylinders): ");
    scanf("%d", &disk_size);

    // Input initial position of the disk head
    printf("Enter the initial position of the disk head (0-%d): ", disk_size - 1);
    scanf("%d", &initial_position);

    // Input number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);

    // Allocate memory for disk requests
    int *requests = (int *)malloc(num_requests * sizeof(int));

    // Input disk requests
    printf("Enter the disk requests (0-%d):\n", disk_size - 1);
    for (int i = 0; i < num_requests; i++)
        scanf("%d", &requests[i]);

    // Print the seek operations and total seek time
    printSeekMovement(requests, num_requests, initial_position);
    printf("\nTotal seek time using SSTF scheduling: %d\n", calculateTotalSeekTime(requests, num_requests, initial_position));

    // Free allocated memory
    free(requests);
    return 0;
}
