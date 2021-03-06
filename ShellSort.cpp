#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 500
#define SIZE 200
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
    if (n <= 200) {
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
    clock_t begin, end;
    TestOrder(A, size, start);
    begin = clock();
    (*p)(A, size);
    end = clock();
    TestOrder(A, size, start);
    printf("CPU 占用的总时间：%f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("-----------------------------------------------\n");
}

/* --------------------------------------------------------------------------*/

void ShellSort(int A[], int n) {
    int i, k, d, temp;
    for (d = n / 2; d >= 1; d /= 2) {  // important d/=2 在函数体执行完成后执行
        for (i = d; i < n; i++) {
            if (A[i - d] > A[i]) {
                temp = A[i];
                for (k = i - d; k >= 0 && A[k] > temp; k -= d) {
                    A[k + d] = A[k];
                }
                A[k + d] = temp;
            }
        }
    }
}

// @ 等当前子表排完再排其他表
void ShellSortSub(int A[], int n) {
    int i, j, k, d, temp;
    for (d = n / 2; d >= 1; d /= 2) {
        for (j = 0; j < d; j++) {  // step 排几个表
            for (i = j; i < n; i += d) {
                if (A[i - d] > A[i]) {
                    temp = A[i];
                    for (k = i - d; k >= 0 && A[k] > temp; k -= d) {
                        A[k + d] = A[k];
                    }
                    A[k + d] = temp;
                }
            }
        }
    }
}

int main() {
    // ^ 方法一
    Sort(ShellSort, SIZE, 0);

    // ^ 排完当前子表再排其他子表
    Sort(ShellSortSub, SIZE, 0);
}