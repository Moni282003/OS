#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {5, 2, 9, 1, 6};
    int arr2[] = {8, 4, 3, 7, 0};
    int n = 5;

    if (fork() == 0) {
        sort(arr1, n);
        printf("Child sorted array: ");
        printArray(arr1, n);
    } else {
        wait(NULL);
        sort(arr2, n);
        printf("Parent sorted array: ");
        printArray(arr2, n);
    }

    return 0;
}
