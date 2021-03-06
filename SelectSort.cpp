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

void Sort(void (*p)(int A[], int n), int size, int start) {
    int *A = MakeArray(size, start);
    TestOrder(A, size, start);
    (*p)(A, size);
    TestOrder(A, size, start);
    printf("-----------------------------------------------\n");
}

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/* --------------------------------------------------------------------------*/

void SelectSort(int A[], int n) {
    int i, k, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (k = i + 1; k < n; k++) {
            if (A[k] < A[min]) {
                min = k;
            }
        }
        if (min != i) Swap(A[i], A[min]);
    }
}

int main() {
    // ^ 方法一
    Sort(SelectSort, SIZE, 0);
}