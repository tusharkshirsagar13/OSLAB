#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, i, head, total = 0, count = 0;
    int req[50], visited[50] = {0};
    printf("Enter number of requests: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("No requests");
        return 0;
    }

    printf("Enter request sequence: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
    }

    printf("Enter head movement: ");
    scanf("%d", &head);

    printf("Current\tHeadmovement\n");
    while (count < n)
    {
        int min = 9999, pos = -1;
        for (i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                int diff = abs(head - req[i]);
                if (diff < min)
                {
                    min = diff;
                    pos = i;
                }
            }
        }

        if (pos == -1)
            break;
        visited[pos] = 1;
        int diff = abs(head - req[pos]);
        printf("%d\t%d\n", req[pos], diff);
        total += diff;
        head = req[pos];
        count++;
    }

    printf("Total seek time:%d\n", total);
}