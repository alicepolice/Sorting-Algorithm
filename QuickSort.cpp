#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 500
#define SIZE 10
#define null 0
#define bu printf("bug\n");

void ShowArray(int A[], int n, int start) {
    for (int i = 0 + start; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int *MakeArray(int n, int start) {
    int *a = (int *)malloc(sizeof(int) * n);
    srand(time(NULL));
    for (int i = 0 + start; i < n; i++) {
        a[i] = rand() % 100;
    }
    return a;
}

bool TestOrder(int A[], int n, int start) {
    if (n <= 20) {
        ShowArray(A, n, start);
    }

    for (int i = 0 + start; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            printf("无序\n");
            return false;
        }
    }
    printf("有序\n");
    return true;
}

void Sort(void (*p)(int A[], int low, int high), int size, int start) {
    int *A = MakeArray(size, start);
    TestOrder(A, size, start);
    (*p)(A, 0, size - 1);  // step 下标 0~n-1
    TestOrder(A, size, start);
    printf("-----------------------------------------------\n");
}

/* --------------------------------------------------------------------------*/

int Partition(int A[], int low, int high) {
    int pivot = A[low];
    while (high > low) {
        while (high > low && A[high] > pivot) high--;
        A[low] = A[high];
        while (high > low && A[low] < pivot) low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;  // step 返回枢轴的下标
}

void QuickSort(int A[], int low, int high) {
    if (high > low) {
        int pivotPos = Partition(A, low, high);
        QuickSort(A, low, pivotPos - 1);
        QuickSort(A, pivotPos + 1, high);
    }
}

int main() {
    // ^ 方法一
    Sort(QuickSort, SIZE, 0);
}