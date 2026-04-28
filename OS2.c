#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    for(i = 0; i < n-1; i++) {
        min = i;
        for(j = i+1; j < n; j++) {
            if(arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[20];

    printf("Enter elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if(pid == 0) {
        printf("\nChild Process (PID: %d, PPID: %d)\n", getpid(), getppid());

        selectionSort(arr, n);

        printf("Child Sorted (Ascending): ");
        for(i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        sleep(10);
        printf("Child after parent exit (Orphan) -> New PPID: %d\n", getppid());

        exit(0);
    }
    else {
        printf("\nParent Process (PID: %d)\n", getpid());

        bubbleSort(arr, n);

        printf("Parent Sorted (Ascending): ");
        for(i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("\n[Zombie Demo] Parent sleeping, NOT calling wait()\n");
        sleep(20);

        printf("\n[Orphan Demo] Parent exiting now...\n");
        exit(0);
    }

    return 0;
}