#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, i, j, head, size, dir, total = 0;
    int req[50], temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for(i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter current head: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Direction (1=right, 0=left): ");
    scanf("%d", &dir);

    // Sort requests
    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-i-1; j++)
            if(req[j] > req[j+1]) {
                temp = req[j];
                req[j] = req[j+1];
                req[j+1] = temp;
            }

    printf("\nCurrent\tMove\n%d\t0\n", head);

    int start = head;

    if(dir == 1) {
        for(i = 0; i < n; i++)
            if(req[i] >= start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }

        printf("%d\t%d\n", size-1, abs(head - (size-1)));
        total += abs(head - (size-1));
        head = 0;

        printf("0\t%d\n", size-1);
        total += size-1;

        for(i = 0; i < n; i++)
            if(req[i] < start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }

    } else {
        for(i = n-1; i >= 0; i--)
            if(req[i] <= start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            }

        printf("0\t%d\n", abs(head - 0));
        total += abs(head);
        head = size-1;

        printf("%d\t%d\n", size-1, size-1);
        total += size-1;

        for(i = n-1; i >= 0; i--)
            if(req[i] > start) {
                printf("%d\t%d\n", req[i], abs(head - req[i]));
                total += abs(head - req[i]);
                head = req[i];
            } 
    }
    printf("\nTotal Seek Length = %d\n", total);
}
