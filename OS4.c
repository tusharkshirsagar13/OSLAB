#include <stdio.h>
#include <limits.h>

struct Process
{
    int id, at, bt, rt, priority, st, et, tat, wt;
    int started;
};

int main()
{
    int n, completed = 0, min_priority = INT_MAX, t = 0, shortest = 0, found = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("P%d :Enter AT, BT & priority : ", p[i].id);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
        p[i].started = 0;
    }

    while (completed != n)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[j].at <= t && (p[j].priority < min_priority) && p[j].rt > 0)
            {
                min_priority = p[j].priority;
                shortest = j;
                found = 1;
            }
        }
        if (found == 0)
        {
            t++;
            continue;
        }
        if (p[shortest].started == 0)
        {
            p[shortest].started = 1;
            p[shortest].st = t;
        }

        p[shortest].rt--;
        min_priority = (p[shortest].rt == 0) ? INT_MAX : p[shortest].priority;

        if (p[shortest].rt == 0)
        {
            completed++;
            found = 0;
            p[shortest].et = t + 1;
            p[shortest].tat = p[shortest].et - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
        t++;
    }

    printf("PID\tAT\tBT\tRT\tPriority\tST\tET\tTAT\tWT\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].rt, p[i].priority, p[i].st, p[i].et, p[i].tat, p[i].wt);
    }
    float total_tat = 0;
    float total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage TAT : %0.2f", total_tat / n);
    printf("\nAverage WT : %0.2f\n", total_wt / n);
}