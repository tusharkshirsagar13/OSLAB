#include <stdio.h>

int main() {
    int n, tq, time = 0, front = 0, rear = 0;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    int q[100], inq[10] = {0}, done = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("AT BT P%d: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Time Quantum: ");
    scanf("%d", &tq);

    // push processes that arrive at time 0
    for(int i = 0; i < n; i++)
        if(at[i] == 0) q[rear++] = i, inq[i] = 1;

    while(done < n) {
        if(front == rear) { time++; continue; }

        int i = q[front++];

        if(rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            done++;
        }

        // add newly arrived processes
        for(int j = 0; j < n; j++)
            if(at[j] <= time && !inq[j] && rt[j] > 0)
                q[rear++] = j, inq[j] = 1;

        // if not finished, push back to queue
        if(rt[i] > 0) q[rear++] = i;
    }

    float awt = 0, atat = 0;
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\n", awt/n, atat/n);
    return 0;
}