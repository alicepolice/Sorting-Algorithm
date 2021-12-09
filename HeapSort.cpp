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
// test 从小到大

void HeadAdjust(int A[], int head, int len) {
    for (int i = head * 2; i <= len; i *= 2) {
        if (i + 1 <= len && A[i + 1] > A[i]) i = i + 1;
        if (A[i] > A[head]) {
            Swap(A[i], A[head]);
            head = i;
        } else
            break;
    }
}

// @ 建立大根堆
void BuildMaxHeap(int A[], int len) {
    for (int i = len / 2; i > 0; i--) {
        HeadAdjust(A, i, len);
    }
}

// 0 ~ n-1
void HeapSort(int A[], int n) {
    n = n - 1;  // @ 完全二叉树节点个数
    BuildMaxHeap(A, n);
    for (int i = n; i > 1; i--) {
        Swap(A[1], A[i]);
        HeadAdjust(A, 1, i - 1);
    }
}

int main() {
    // ^ 方法一
    Sort(HeapSort, SIZE, 1);
}