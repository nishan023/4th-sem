
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printSeekMovement(int *req, int num_req, int head, int disk_size, int dir)
{
    printf("\nDisk Head Movement:\n%d", head);
    int i = (dir == 1) ? 0 : num_req - 1, step = (dir == 1) ? 1 : -1, end = (dir == 1) ? disk_size - 1 : 0;

    for (; i >= 0 && i < num_req; i += step)
    {
        if ((dir == 1 && req[i] >= head) || (dir == 0 && req[i] <= head))
        {
            printf("%.*s%d (Seek Time:%d)", abs(req[i] - head), "**************************************", req[i], abs(req[i] - head));
            head = req[i];
        }
    }
    printf("%.*s%d (Seek Time:%d)%.*s0 (Seek Time:%d)", abs(end - head), "**************************************", end, abs(end - head), abs(end), "**************************************", abs(end));

    head = 0;
    for (i = (dir == 1) ? 0 : num_req - 1; i >= 0 && i < num_req; i += step)
    {
        if ((dir == 1 && req[i] < head) || (dir == 0 && req[i] > head))
        {
            printf("%.*s%d (Seek Time:%d)", abs(req[i] - head), "**************************************", req[i], abs(req[i] - head));
            head = req[i];
        }
    }
}

int calculateTotalSeekTime(int *req, int num_req, int head, int disk_size, int dir)
{
    int total_seek_time = 0, end = (dir == 1) ? disk_size - 1 : 0;
    for (int i = 0; i < num_req; i++)
    {
        if ((dir == 1 && req[i] >= head) || (dir == 0 && req[i] <= head))
        {
            total_seek_time += abs(req[i] - head);
            head = req[i];
        }
    }
    total_seek_time += abs(end - head) + end;
    head = 0;
    for (int i = 0; i < num_req; i++)
    {
        if ((dir == 1 && req[i] < head) || (dir == 0 && req[i] > head))
        {
            total_seek_time += abs(req[i] - head);
            head = req[i];
        }
    }
    return total_seek_time;
}

int main()
{
    int num_req, head, disk_size, dir;
    printf("\t*****SCAN Disk Scheduling Algorithm*****\n\t\t**NISHAN DHAKAL**\n\n");
    printf("Enter disk size (cylinders): "), scanf("%d", &disk_size);
    printf("Enter initial head position (0-%d): ", disk_size - 1), scanf("%d", &head);
    printf("Enter direction (1 for upwards, 0 for downwards): "), scanf("%d", &dir);
    printf("Enter number of requests: "), scanf("%d", &num_req);

    int *req = malloc(num_req * sizeof(int));
    printf("Enter disk requests (0-%d):\n", disk_size - 1);
    for (int i = 0; i < num_req; i++)
        scanf("%d", &req[i]);

    // Sorting requests
    for (int i = 0; i < num_req - 1; i++)
        for (int j = 0; j < num_req - i - 1; j++)
            if (req[j] > req[j + 1])
            {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }

    printSeekMovement(req, num_req, head, disk_size, dir);
    printf("\nTotal seek time using SCAN scheduling: %d\n", calculateTotalSeekTime(req, num_req, head, disk_size, dir));

    free(req);
    return 0;
}
