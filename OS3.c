#include <stdio.h>

struct Process{
    int id, at, bt, rt, st, et, tat, wt;
    int started;
};

int main(){
    int n, t=0, quantam, completed = 0;
    printf("Enter the no of process & Time Quantam: ");
    scanf("%d %d",&n, &quantam);
    struct Process p[n];

    for(int i=0; i<n; i++){
        p[i].id = i+1;
        printf("P%d | Enter the AT & BT : ",p[i].id);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = 0;
    }

    while(completed < n){
        int done_something = 0;
        for(int j = 0; j<n; j++){
            if(p[j].at<=t && p[j].rt>0){
                done_something = 1;

                if(p[j].started == 0){
                    p[j].started = 1;
                    p[j].st = t;
                }

                if(p[j].rt>quantam){
                    t+=quantam;
                    p[j].rt-=quantam;
                }else{
                    t += p[j].rt;
                    p[j].rt = 0;
                    completed++;
                    p[j].et = t;
                    p[j].tat = p[j].et - p[j].at;
                    p[j].wt = p[j].tat - p[j].bt;
                }
            }
        }
        if(!done_something) t++;
    }

    printf("\nID\tAT\tBT\tST\tET\tTAT\tWT\n");
    printf("----------------------------------------------------------\n");
    float total_tat = 0;
    float total_wt = 0;
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].st,p[i].et,p[i].tat,p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("Average TAT: %0.2f \n",total_tat/n);
    printf("Average WT: %0.2f \n",total_wt/n);

    return 0;
}