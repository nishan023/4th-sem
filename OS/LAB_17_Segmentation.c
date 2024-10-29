#include <stdio.h>
#include <stdlib.h>

void print_table(int num_segments, int *segment_base_address, int *segment_limit)
{
    // Print table header
    printf("\n%-8s %-15s %-5s\n", "Segment", "Base Address", "Limit");
    printf("---------------------------------\n");

    // Print table data
    for (int i = 0; i < num_segments; i++)
    {
        printf("%-8d %-15d %-5d\n", i, segment_base_address[i], segment_limit[i]);
    }
}

int main()
{
    int num_segments;
printf("\t****SEGMENTATION****\n\t**NISHAN DHAKAL**\n\n");
    // Ask user for the number of segments
    printf("Enter the number of segments: ");
    scanf("%d", &num_segments);

    // Allocate memory for base addresses and limits
    int *segment_base_address = (int *)malloc(num_segments * sizeof(int));
    int *segment_limit = (int *)malloc(num_segments * sizeof(int));

    // Check if memory allocation was successful
    if (segment_base_address == NULL || segment_limit == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input segment base addresses and limits
    printf("Enter base addresses and limits for %d segments:\n", num_segments);
    for (int i = 0; i < num_segments; i++)
    {
        printf("Segment %d\n", i);
        printf("  Base Address: ");
        scanf("%d", &segment_base_address[i]);
        printf("  Limit: ");
        scanf("%d", &segment_limit[i]);
    }

    // Display the table of input base addresses and limits
    print_table(num_segments, segment_base_address, segment_limit);

    char continue_program;
    do
    {
        // Input segment number and offset from user
        int segment_number, offset;
        printf("\nEnter segment number: ");
        scanf("%d", &segment_number);
        printf("Enter offset: ");
        scanf("%d", &offset);

        // Validate segment number
        if (segment_number < 0 || segment_number >= num_segments)
        {
            printf("Invalid segment number.\n");
        }
        else
        {
            // Check if offset is within the limit
            if (offset < 0 || offset >= segment_limit[segment_number])
            {
                printf("Illegal reference or generate trap signal.\n");
            }
            else
            {
                int physical_address = segment_base_address[segment_number] + offset;
                printf("Physical Address: %d\n", physical_address);
            }
        }

        // Ask if the user wants to continue
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_program); // Note the space before %c to ignore any leftover newline characters

    } while (continue_program == 'y' || continue_program == 'Y');

    // Free allocated memory
    free(segment_base_address);
    free(segment_limit);

    return 0;
}
