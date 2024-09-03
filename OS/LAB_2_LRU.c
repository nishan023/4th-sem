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
// Function to find the Least Recently Used (LRU) page index
int findLRUPageIndex(int memory[], int frame_size, int usage_order[], int ref_size)
{
    int lru_index = 0, min_usage = ref_size;
    for (int i = 0; i < frame_size; i++)
    {
        if (usage_order[memory[i]] < min_usage)
        {
            min_usage = usage_order[memory[i]];
            lru_index = i;
        }
    }
    return lru_index;
}
// Function to print the current state of frames
void printFrames(int memory[], int frame_size, bool page_hit)
{
    printf("Frames: ");
    for (int i = 0; i < frame_size; i++)
        memory[i] == -1 ? printf(" . ") : printf(" %d ", memory[i]);
    printf(" | %s\n", page_hit ? "Page Hit" : "Page Fault");
}

// Function to simulate LRU page replacement algorithm
int lru_page_replacement(int reference_string[], int ref_size, int frame_size, int *page_hits)
{
    int memory[MAX_FRAMES], page_faults = 0, usage_order[MAX_PAGES] = {0}, time = 0;
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
            // Find the LRU page index to replace
            int lru_index = (i < frame_size) ? i : findLRUPageIndex(memory, frame_size, usage_order, ref_size);
            memory[lru_index] = page;
        }
        else
        {
            (*page_hits)++;
        }

        // Update usage order for the current page
        usage_order[page] = time++;
        printFrames(memory, frame_size, page_hit);
    }
    return page_faults;
}

int main()
{
    int reference_string[MAX_PAGES], ref_size, frame_size, page_hits = 0;

    printf("\t*****NISHAN DHAKAL*****\n*****LRU Page Replacement Algorithm*****\n\n");
    printf("Enter the number of frames: ");
    scanf("%d", &frame_size);
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &ref_size);

    if (frame_size > MAX_FRAMES || ref_size > MAX_PAGES)
    {
        printf("Frame size or number of pages exceeds the maximum allowed.\n");
        return 1;
    }

    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < ref_size; i++)
        scanf("%d", &reference_string[i]);

    int page_faults = lru_page_replacement(reference_string, ref_size, frame_size, &page_hits);
    printf("\nNumber of pages: %d\nNumber of page faults: %d\nNumber of page hits: %d\n", ref_size, page_faults, page_hits);

    return 0;
}
