#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

// Function to check if a page is already in memory
bool isPageInMemory(int page, int memory[], int frame_size)
{
    for (int i = 0; i < frame_size; i++)
        if (memory[i] == page)
            return true;
    return false;
}

// Function to print the current state of frames
void printFrames(int memory[], int frame_size, bool page_hit)
{
    printf("Frames: ");
    for (int i = 0; i < frame_size; i++)
        memory[i] == -1 ? printf(" . ") : printf(" %d ", memory[i]);
    printf(" | %s\n", page_hit ? "Page Hit" : "Page Fault");
}

// Function to simulate FIFO page replacement algorithm
int fifo_page_replacement(int reference_string[], int ref_size, int frame_size, int *page_hits)
{
    int memory[MAX_FRAMES], page_faults = 0, memory_index = 0;

    // Initialize memory frames to -1 (empty)
    for (int i = 0; i < frame_size; i++)
        memory[i] = -1;

    printf("Page\tFrames\t\t\tStatus\n----\t---------------------\t-------\n");

    for (int i = 0; i < ref_size; i++)
    {
        int page = reference_string[i];
        bool page_hit = isPageInMemory(page, memory, frame_size);
        printf("%d\t", page);

        if (!page_hit)
        {
            page_faults++;
            // Add the page to memory using FIFO replacement
            if (memory_index < frame_size)
                memory[memory_index++] = page;
            else
                memory[0] = page, memory_index = 1; // Reset index for FIFO
        }
        else
        {
            (*page_hits)++;
        }

        printFrames(memory, frame_size, page_hit);
    }
    return page_faults;
}

int main()
{
    int reference_string[MAX_PAGES], ref_size, frame_size, page_hits = 0;

    printf("\t*****NISHAN DHAKAL*****\n*****FIFO Page Replacement Algorithm*****\n\n");
    printf("Enter the number of frames: ");
    scanf("%d", &frame_size);
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &ref_size);

    if (frame_size > MAX_FRAMES || ref_size > MAX_PAGES)
    {
        printf("Frame size or number of pages exceeds the maximum allowed.\n");
        return 1;
    }

    printf("Enter the reference string: ");
    for (int i = 0; i < ref_size; i++)
        scanf("%d", &reference_string[i]);

    int page_faults = fifo_page_replacement(reference_string, ref_size, frame_size, &page_hits);

    printf("\nNumber of pages: %d\nNumber of page faults: %d\nNumber of page hits: %d\n", ref_size, page_faults, page_hits);
    return 0;
}
