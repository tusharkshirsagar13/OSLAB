#include <stdio.h>

int main(){
    int f, n;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], counter[f];
    for(int i = 0; i < f; i++){
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    int ref[n];
    printf("Enter reference string:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &ref[i]);
    }

    int faults = 0;

    printf("\nRef\t");
    for(int i = 0; i < f; i++){
        printf("F[%d]\t", i);
    }
    printf("STATUS\n");
    printf("----------------------------------------------------------\n");

    for(int i = 0; i < n; i++){
        int hit = 0;

        // Check HIT
        for(int j = 0; j < f; j++){
            if(frames[j] == ref[i]){
                hit = 1;
                counter[j] = i; // update recent use
                break;
            }
        }

        // If MISS (Page Fault)
        if(!hit){
            int replace_idx = 0;

            for(int j = 0; j < f; j++){
                if(frames[j] == -1){
                    replace_idx = j;
                    break;
                }
                if(counter[j] < counter[replace_idx]){
                    replace_idx = j;
                }
            }

            frames[replace_idx] = ref[i];
            counter[replace_idx] = i;
            faults++;

            printf("%2d\t", ref[i]);
            for(int k = 0; k < f; k++){
                printf("%2d\t", frames[k]);
            }
            printf("FAULT\n");
        }
        else{
            printf("%2d\t", ref[i]);
            for(int k = 0; k < f; k++){
                printf("%2d\t", frames[k]);
            }
            printf("HIT\n");
        }
    }

    printf("\nTotal Page faults : %d", faults);
    printf("\nTotal Page hits   : %d\n", n - faults);

    return 0;
}