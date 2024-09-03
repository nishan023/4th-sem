#include <stdio.h>

void display(int frames[], int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (frames[i] != -1)
            printf("| %2d \t", frames[i]);
        else
            printf("| - \t");
    }
    printf("|");
}

int fifoPageReplacement(int referenceString[], int length, int frameSize)
{
    int frames[frameSize], pageFaults = 0, index = 0, hits = 0;
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    for (int i = 0; i < length; i++)
    {
        int page = referenceString[i];
        int found = 0;
        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                hits++;
                break;
            }
        }
        if (!found)
        {
            frames[index] = page;
            index = (index + 1) % frameSize;
            pageFaults++;
        }
        printf("\n%2d\t\t", page);
        display(frames, frameSize);
        if (!found)
            printf("Fault");
        else
            printf("Hit");
    }
    printf("\n\nTotal no. of Reference String: %d", length);
    printf("\nTotal Page Faults:\t%d", pageFaults);
    printf("\nTotal Page Hits:\t%d", hits);
    return pageFaults;
}

int main()
{
    int length, pageFaults[3];
    int frameSizes[3];

    printf("\t****NISHAN DHAKAL****\n");
    printf("\t****Belady's Anomaly****\n");

    printf("Enter the length of Reference String: ");
    scanf("%d", &length);
    int referenceString[length];
    printf("Enter the string now: ");
    for (int i = 0; i < length; i++)
        scanf("%d", &referenceString[i]);

    for (int i = 0; i < 3; i++)
    {
        printf("\nEnter the Frame size: ");
        scanf("%d", &frameSizes[i]);

        printf("\nFIFO Page Replacement (Frame Size = %d):", frameSizes[i]);
        printf("\nIncoming\t");
        for (int j = 0; j < frameSizes[i]; j++)
            printf("|Frame %d", j + 1);
        printf("|Status");

        pageFaults[i] = fifoPageReplacement(referenceString, length, frameSizes[i]);
    }

    printf("\n\nTotal page faults with frame sizes %d, %d, and %d: %d, %d, and %d respectively",
           frameSizes[0], frameSizes[1], frameSizes[2], pageFaults[0], pageFaults[1], pageFaults[2]);

    // Check for Belady's Anomaly
    if ((pageFaults[1] > pageFaults[0]) || (pageFaults[2] > pageFaults[1]))
    {
        printf("\nBelady's Anomaly detected: More page faults with increased frame sizes.");
    }
    else
    {
        printf("\nNo Belady's Anomaly detected.");
    }

    return 0;
}
