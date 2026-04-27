#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    int n, i, j, temp;
    int arr[20];
    pid_t p;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    p = fork();

    // if(p < 0) {
    //     perror("Fork failed");
    //     return 1;
    // }

    if(p == 0)
    {
        // Child Process
        printf("\nChild : Sorting in Ascending order: (PID: %d)\n", getpid());

        for(i = 0; i < n - 1; i++)
        {
            for(j = 0; j < n - i - 1; j++)
            {
                if(arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);
        
        printf("\nChild : Process finished.\n");
        exit(0);
    }
    else
    {
        // Parent Process
        printf("\nParent waits() for child to finish...\n");
        
        // The Parent stops here and waits for child's exit signal
        wait(NULL); 

        printf("\nParent : Child's exit signal received. Now sorting Descending order : (PID: %d)\n", getpid());

        for(i = 0; i < n - 1; i++)
        {
            for(j = 0; j < n - i - 1; j++)
            {
                if(arr[j] < arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);

        printf("\nParent : Process finished.\n");
    }

    return 0;
}