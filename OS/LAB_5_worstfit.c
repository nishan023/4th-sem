#include <stdio.h>
#include <limits.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

// Function to implement the Worst Fit memory allocation algorithm
void worstFit(int blocks[], int originalBlocks[], int m, int processes[], int n)
{
    int allocation[n];
    // Initialize allocations to -1 (not allocated)
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    // Allocate memory to processes
    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1, maxDiff = -1;
        // Find the worst fit block for the current process
        for (int j = 0; j < m; j++)
            if (blocks[j] >= processes[i] && blocks[j] - processes[i] > maxDiff)
                maxDiff = blocks[j] - processes[i], worstIdx = j;
        // If a suitable block is found, allocate it to the process
        if (worstIdx != -1)
            allocation[i] = worstIdx, blocks[worstIdx] -= processes[i];
    }

    // Print the allocation result
    printf("\n%-8s %-12s %-8s %-10s %-10s\n", "Process", "Proc Size", "Block", "Block Size", "Holes");
    for (int i = 0; i < n; i++)
        allocation[i] != -1 ? printf("%-8c %-12d %-8d %-10d %-10d\n", 'A' + i, processes[i], allocation[i], originalBlocks[allocation[i]], originalBlocks[allocation[i]] - processes[i]) : printf("%-8c %-12d %-8s %-10s %-10s\n", 'A' + i, processes[i], "NA", "", "");

    // Print the final state of memory blocks
    printf("\nFinal State of Memory Blocks:\n");
    for (int i = 0; i < m; i++)
        printf("Block %d (Original size %d) - Remaining Size: %d\n", i, originalBlocks[i], blocks[i]);
}

// Function to read an integer within a specified range
int readInteger(const char *prompt, int min, int max)
{
    int value;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max)
            break;
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        while (getchar() != '\n')
            ; // Clear the input buffer
    }
    return value;
}

// Function to read sizes of blocks or processes
void readSizes(const char *prompt, int arr[], int n)
{
    printf("%s\n", prompt);
    for (int i = 0; i < n; i++)
        arr[i] = readInteger("Size: ", 1, INT_MAX);
}

int main()
{
    int blocks[MAX_BLOCKS], originalBlocks[MAX_BLOCKS], processes[MAX_PROCESSES];
    printf("\t****NISHAN DHAKAL****\n**** Worst Fit Algorithm****\n");

    // Read the number of memory blocks and their sizes
    int m = readInteger("Enter the number of free memory blocks: ", 1, MAX_BLOCKS);
    readSizes("Enter the sizes of free memory blocks:", blocks, m);
    for (int i = 0; i < m; i++)
        originalBlocks[i] = blocks[i];

    // Read the number of processes and their sizes
    int n = readInteger("Enter the number of process requests: ", 1, MAX_PROCESSES);
    readSizes("Enter the sizes of process requests:", processes, n);

    // Execute the Worst Fit memory allocation algorithm
    worstFit(blocks, originalBlocks, m, processes, n);
    return 0;
}
