#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, i, j, head, dir;
    int req[50], temp;
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 = right, 0 = left): ");
    scanf("%d", &dir);

    // Step 1: Sort the requests (ascending)
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    printf("\nHead Movement Sequence:\n");
    printf("%d", head);

    int start = head;

    // RIGHT direction (C-LOOK)
    if(dir == 1) {

        // Move right
        for(i = 0; i < n; i++) {
            if(req[i] >= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }

        // Jump to lowest request (circular)
        for(i = 0; i < n; i++) {
            if(req[i] < start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }
    }

    // LEFT direction (C-LOOK)
    else {

        // Move left
        for(i = n - 1; i >= 0; i--) {
            if(req[i] <= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }

        // Jump to highest request (circular)
        for(i = n - 1; i >= 0; i--) {
            if(req[i] > start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal Seek Time = %d\n", total);

    return 0;
}