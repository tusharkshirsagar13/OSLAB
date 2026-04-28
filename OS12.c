#include <stdio.h>
int main()
{
    int n, f, i, j;
    int pages[50], frames[10];
    int faults = 0, hits = 0, front = 0;
    printf("Enter number of pages : ");
    scanf("%d", &n);
    printf("Enter number of frames : ");
    scanf("%d", &f);
    printf("Enter page reference string : ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    for (i = 0; i < f; i++)
        frames[i] = -1;
    printf("\nPage\t");
    for (i = 0; i < f; i++)
        printf("F%d\t", i);
    printf("Status\n");
    for (i = 0; i < n; i++)
    {
        int found = 0;
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            frames[front] = pages[i];
            front = (front + 1) % f;
            faults++;
            printf("%d\t", pages[i]);
            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("-\t");
                else
                    printf("%d\t", frames[j]);
            }
            printf("Fault\n");
        }
        else
        {
            hits++;
            printf("%d\t", pages[i]);
            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("-\t");
                else
                    printf("%d\t", frames[j]);
            }
            printf("Hit\n");
        }
    }
    printf("\nTotal Hits   = %d\n", hits);
    printf("Total Faults = %d\n", faults);
}