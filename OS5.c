#include <stdio.h>
#include <limits.h>

struct Process {
    int id, at, bt, rt, st, et, tat, wt;
    int started;
};

int main(){
    int n, completed = 0, t=0, min_rt = INT_MAX, shortest = 0;
    int found = 0;

    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Process p[n];

    for(int i=0; i<n; i++){
        p[i].id = i+1;
        printf("P%d Enter the AT & BT :",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = 0;
        p[i].st = -1;
    }

    while(completed!=n){
        for(int j=0; j<n; j++){
            if((p[j].at<=t) && (p[j].rt<min_rt && p[j].rt>0)){
                min_rt = p[j].rt;
                shortest = j;
                found = 1;        //acts as a boolean flag that the CPU has an ongoing process
            }
        }
        if(found==0){
            t++;
            continue;
        }
        if(p[shortest].started==0){            //if the process is getting the CPU for the first time
            p[shortest].st = t;                // it's start time is initialized and the started flag is turned to 1.
            p[shortest].started = 1;
        }

        p[shortest].rt--;                      // Reduce Remaining Time
        min_rt = (p[shortest].rt==0)?INT_MAX:p[shortest].rt;

        if(p[shortest].rt==0){                 //when a process if completed , completed is incremented
            completed++;                       //and found is reset to 0, and end time is noted and tat, wt is calculated.
            found = 0;
            p[shortest].et = t+1;
            p[shortest].tat = p[shortest].et - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
        t++;
    }

    printf("\nID\tAT\tBT\tRT\tST\tET\tTAT\tWT\n");
    printf("-------------------------------------------------------------\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].rt,p[i].st,p[i].et,p[i].tat,p[i].wt);
    }

    int total_wt = 0, total_tat = 0;
    for(int i=0; i<n; i++){
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("Average WT : %0.2f\n",(float)total_wt/n);
    printf("Average TAT : %0.2f\n",(float)total_tat/n);

    return 0;
}