#include <stdio.h>

struct Process{
    int id, at, bt, st, et, tat, wt;
};
int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Process p[n];

    for(int i=0; i<n; i++){
        p[i].id = i+1;
        printf("P%d | Enter AT & BT: ",p[i].id);
        scanf("%d %d",&p[i].at, &p[i].bt);
    }

    for(int i=0 ; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].at > p[j+1].at){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    for(int i=0; i<n; i++){
        if(current_time < p[i].at) current_time = p[i].at;
        p[i].st = current_time;
        p[i].et = p[i].st + p[i].bt;
        p[i].tat = p[i].et - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        current_time = p[i].et;
    }

    printf("\nID\tAT\tBT\tST\tET\tTAT\tWT\n");
    printf("----------------------------------------------\n");
    float total_tat = 0;
    float total_wt = 0;
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at, p[i].bt,p[i].st, p[i].et, p[i].tat, p[i].wt);
        total_tat += p[i].tat; 
        total_wt += p[i].wt; 
    }
    printf("Average TAT: %0.2f\n",total_tat/n);
    printf("Average WT: %0.2f\n",total_wt/n);

    return 0;
}