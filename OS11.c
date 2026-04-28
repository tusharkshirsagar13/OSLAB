#include <stdio.h>

int main(){
    int f, n;

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f];
    for(int i = 0; i < f; i++){
        frames[i] = -1;
    }

    // Input reference string size
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
                break;
            }
        }

        // If MISS
        if(!hit){
            int replace_idx = -1, farthest = i;

            for(int j = 0; j < f; j++){
                // Empty frame available
                if(frames[j] == -1){
                    replace_idx = j;
                    break;
                }

                int next_use = n + 1; // assume not used again

                for(int k = i + 1; k < n; k++){
                    if(frames[j] == ref[k]){
                        next_use = k;
                        break;
                    }
                }

                if(next_use > farthest){
                    farthest = next_use;
                    replace_idx = j;
                }
            }

            frames[replace_idx] = ref[i];
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

    printf("\nNo. of faults : %d\n", faults);
    printf("No. of hits   : %d\n", n - faults);

    return 0;
}