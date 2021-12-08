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

/* --------------------------------------------------------------------------*/

void InsertSort(int A[], int n) {
    int i, k, temp;
    for (i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            temp = A[i];
            for (k = i - 1; k >= 0 && A[k] > temp; k--) {
                A[k + 1] = A[k];
            }
            A[k + 1] = temp;
        }
    }
}

void InsertSortWithGuard(int A[], int n) {
    int i, k;
    for (i = 2; i < n; i++) {
        if (A[i - 1] > A[i]) {
            A[0] = A[i];
            for (k = i - 1; A[k] > A[0]; k--) {
                A[k + 1] = A[k];
            }
            A[k + 1] = A[0];
        }
    }
}

void BinaryInsertSort(int A[], int n) {
    int low, high, mid, i, k;
    for (i = 2; i < n; i++) {
        A[0] = A[i];
        low = 1;
        high = i - 1;
        while (high >= low) {
            mid = (high + low) / 2;
            if (A[mid] > A[0])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (k = i - 1; k >= low; k--) {
            A[k + 1] = A[k];
        }
        A[low] = A[0];
    }
}

int main() {
    // ^ 方法一
    // int *A = MakeArray(SIZE, 0);
    // TestOrder(A, SIZE, 0);
    // InsertSort(A, SIZE);
    // TestOrder(A, SIZE, 0);
    Sort(InsertSort, SIZE, 0);

    // ^ 方法二 哨兵
    // int *A = MakeArray(SIZE, 1);
    // TestOrder(A, SIZE, 1);
    // InsertSortWithGuard(A, SIZE);
    // TestOrder(A, SIZE, 1);
    Sort(InsertSortWithGuard, SIZE, 1);

    // ^ 方法三 折半插入
    Sort(BinaryInsertSort, SIZE, 1);

    return 0;
}
