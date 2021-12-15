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
    // a[0] = 3;
    // a[1] = -2;
    // a[2] = -1;
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
    clock_t begin, end;
    TestOrder(A, size, start);
    begin = clock();
    (*p)(A, 0, size - 1);  // FAIL 数组个数与下标数不同,要减1
    end = clock();
    TestOrder(A, size, start);
    printf("CPU 占用的总时间：%f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("-----------------------------------------------\n");
}

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/* --------------------------------------------------------------------------*/
int *B = (int *)malloc(sizeof(int) * SIZE + 10);

void Merge(int A[], int low, int mid, int high) {
    int a = low, b = mid + 1, k = low;
    for (int i = low; i <= high; i++) {
        B[i] = A[i];
    }
    while (a <= mid && b <= high) {
        if (B[a] > B[b])
            A[k++] = B[b++];
        else
            A[k++] = B[a++];
    }
    if (a > mid)
        for (; b <= high;) A[k++] = B[b++];
    if (b > high)
        for (; a <= mid;) A[k++] = B[a++];
}

void MergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}

int main() {
    // ^ 方法一
    Sort(MergeSort, SIZE, 0);
}