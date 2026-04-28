#include <stdio.h>

int main()
{
    int n, i;
    int at[10], bt[10], ct[10], wt[10], tat[10];
    float awt = 0, atat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("AT & BT for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    // Sort by Arrival Time (FCFS)
    for (i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (at[i] > at[j])
            {
                int t;
                t = at[i];
                at[i] = at[j];
                at[j] = t;
                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;
            }

    int time = 0;

    for (i = 0; i < n; i++)
    {
        if (time < at[i])
            time = at[i]; // CPU idle case

        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        time = ct[i];

        awt += wt[i];
        atat += tat[i];
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\n", awt / n, atat / n);

    return 0;
}