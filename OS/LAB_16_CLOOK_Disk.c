#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to print the seek operations and movements of the disk head
void printSeekMovement(int *requests, int num_requests, int initial_position, int disk_size)
{
    int *sorted_requests = (int *)malloc(num_requests * sizeof(int));
    int current_position = initial_position;
    int total_seek_time = 0;

    // Copy and sort the requests in ascending order
    for (int i = 0; i < num_requests; i++)
    {
        sorted_requests[i] = requests[i];
    }
    // Simple bubble sort for demonstration; consider using a more efficient sort for larger inputs
    for (int i = 0; i < num_requests - 1; i++)
    {
        for (int j = i + 1; j < num_requests; j++)
        {
            if (sorted_requests[i] > sorted_requests[j])
            {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Print the disk head movement
    printf("\nDisk Head Movement:\n%d", current_position);
    for (int i = 0; i < num_requests; i++)
    {
        if (sorted_requests[i] >= current_position)
        {
            int seek_time = abs(sorted_requests[i] - current_position);
            total_seek_time += seek_time;

            for (int j = 1; j <= seek_time; j++)
                printf("*");

            printf("%d (Seek Time:%d)", sorted_requests[i], seek_time);
            current_position = sorted_requests[i];
        }
    }

    // Wrap around to the beginning of the sorted requests
    if (current_position != sorted_requests[num_requests - 1])
    {
        int seek_time = abs(sorted_requests[0] - current_position);
        total_seek_time += seek_time;

        for (int j = 1; j <= seek_time; j++)
            printf("*");

        printf("%d (Seek Time:%d)", sorted_requests[0], seek_time);
        current_position = sorted_requests[0];
    }

    printf("\n");
    printf("Total seek time using CLOOK scheduling: %d\n", total_seek_time);

    free(sorted_requests);
}

// Main function
int main()
{
    int num_requests, initial_position, disk_size;

    printf("\t*****CLOOK Disk Scheduling Algorithm*****\n");
    printf("\t\t**NISHAN DHAKAL**\n\n");

    printf("Enter the size of the disk (number of cylinders): ");
    scanf("%d", &disk_size);

    printf("Enter the initial position of the disk head (0-%d): ", disk_size - 1);
    scanf("%d", &initial_position);

    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);

    int *requests = (int *)malloc(num_requests * sizeof(int));

    printf("Enter the disk requests (0-%d):\n", disk_size - 1);
    for (int i = 0; i < num_requests; i++)
        scanf("%d", &requests[i]);

    printSeekMovement(requests, num_requests, initial_position, disk_size);

    // Free allocated memory
    free(requests);
    return 0;
}
