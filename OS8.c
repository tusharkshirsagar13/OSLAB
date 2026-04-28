#include <stdio.h>

struct Process{
    int id, at, bt, prio, st, et, tat, wt, completed;
};

int main(){
    int n, count = 0, current_time = 0, i;

    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Process p[n];

    for(i=0; i<n; i++){
        p[i].id = i+1;
        printf("P%d | Enter AT, BT, Priority ",p[i].id);
        scanf("%d %d %d",&p[i].at, &p[i].bt, &p[i].prio);
        p[i].completed = 0;
    }

    while(count<n){
        int idx = -1;
        int min_prio = 1e9;

        for(i=0; i<n; i++){
            if(p[i].at<=current_time && !p[i].completed){
                if(p[i].prio < min_prio){
                    min_prio = p[i].prio;
                    idx = i;
                }
            }
        }

        if(idx == -1){
            current_time++;
        }else{
            p[idx].st = current_time;
            p[idx].et = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].et - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            count++;
            current_time = p[idx].et;
        }
    }

    float total_tat = 0;
    float total_wt = 0;
    printf("\nID\tAT\tBT\tPriority\tST\tET\tTAT\tWT\n");
    printf("--------------------------------------------------------\n");
    for(i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].prio,p[i].st,p[i].et,p[i].tat,p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average TAT: %0.2f\n",total_tat/n);
    printf("Average WT: %0.2f\n",total_wt/n);

}