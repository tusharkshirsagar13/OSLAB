#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, i, j, head, size, dir, total = 0;
    int req[50], temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter current head: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Direction (1=right, 0=left): ");
    scanf("%d", &dir);

    // Sort requests (ascending)
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    printf("\nCurrent\tMove\n");
    printf("%d\t0\n", head);

    int start = head;

    // RIGHT direction
    if(dir == 1) {

        // Move right
        for(i = 0; i < n; i++) {
            if(req[i] >= start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }
        }

        // Go to end of disk
        printf("%d\t%d\n", size - 1, abs(head - (size - 1)));
        total += abs(head - (size - 1));
        head = size - 1;   // ✅ FIXED

        // Move left
        for(i = n - 1; i >= 0; i--) {
            if(req[i] < start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }
        }
    }

    // LEFT direction
    else {

        // Move left
        for(i = n - 1; i >= 0; i--) {
            if(req[i] <= start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }
        }

        // Go to start (0)
        printf("0\t%d\n", abs(head - 0));
        total += abs(head - 0);
        head = 0;   // ✅ FIXED

        // Move right
        for(i = 0; i < n; i++) {
            if(req[i] > start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }
        }
    }

    printf("\nTotal Seek Length = %d\n", total);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// void sort(int queue[], int n){
//     for(int i=0; i<n-1; i++){
//         for(int j=0; j<n-i-1; j++){
//             if(queue[j]>queue[j+1]){
//                 int temp = queue[j];
//                 queue[j] = queue[j+1];
//                 queue[j+1] = temp;
//             }
//         }
//     }
// }

// int main(){
//     int queue[] = {176, 79, 34, 60, 92, 11, 41, 114, 15, 13, 8, 122, 184, 198, 105};
//     int n=15, seek_count = 0, head = 50, disk_size = 200;

//     sort(queue,n);

//     int idx = -1;
//     for(int i=0; i<n; i++){
//         if(head<queue[i]){
//             idx = i;
//             break;
//         }
//     }
    
//     printf("SCAN Sequence: %d",head);
//     for(int i=idx; i<n; i++){
//         seek_count += abs(queue[i]-head);
//         head = queue[i];
//         printf("-> %d",head);
//     }
    
//     seek_count += abs((disk_size-1)-head);
//     head = disk_size-1;
//     printf("-> %d",head);

//     for(int i=idx-1; i>=0; i--){
//         seek_count += abs(head-queue[i]);
//         head = queue[i];
//         printf("-> %d",head);
//     }

//     return 0;
// }