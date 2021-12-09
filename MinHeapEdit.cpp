#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 500
#define SIZE 10
#define null 0
#define bu printf("bug\n");

// step 修改方法,直接跳过下标0
void ShowArray(int A[], int len) {
    for (int i = 1; i <= len; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int *MakeArray(int n) {
    int *a =
        (int *)malloc(sizeof(int) * (n + 10));  // ^ 这里添加容量进行增删测试
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }
    return a;
}

// step 修改方法,跳过下标为0的
bool TestOrder(int A[], int len) {
    if (len <= 20) {
        ShowArray(A, len);
    }

    for (int i = 1; i < len; i++) {
        if (A[i] < A[i + 1]) {  // ^ 修改为逆序
            printf("无序\n");
            return false;
        }
    }

    printf("有序\n");
    return true;
}

void Sort(void (*p)(int A[], int n), int size) {
    int *A = MakeArray(size);
    TestOrder(A, size - 1);
    (*p)(A, size);
    printf("-----------------------------------------------\n");
}

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/* --------------------------------------------------------------------------*/
// step 小根堆中插入元素,删除元素

void HeadAdjust(int A[], int head, int len) {
    int i, k;
    for (i = head * 2; i <= len; i *= 2) {
        if (i < len && A[i + 1] < A[i]) i = i + 1;
        if (A[head] < A[i])
            break;
        else {
            Swap(A[head], A[i]);
            head = i;
        }
    }
}

void BuildMinHeap(int A[], int len) {
    for (int i = len / 2; i > 0; i--) {
        HeadAdjust(A, i, len);
    }
}

void ChildAdjust(int A[], int child, int len) {
    for (int i = child / 2; i > 0; i /= 2) {
        if (A[child] < A[i]) {
            Swap(A[child], A[i]);
            child = i;
        } else
            break;
    }
}

void AddHeap(int A[], int &len, int data) {
    A[++len] = data;
    ChildAdjust(A, len, len);
}

void DelHeap(int A[], int &len, int delPos) {
    A[delPos] = A[len--];
    HeadAdjust(A, delPos, len);
}

// step 这里测试给堆添加元素和删除元素
void HeapSort(int A[], int len) {
    len = len - 1;
    BuildMinHeap(A, len);
    printf("\n小根堆生成后\n");
    ShowArray(A, len);  // step len 是完全二叉树的节点数,不包含0节点
    printf("\n");
    // AddHeap(A, len, 1000);
    // AddHeap(A, len, 2222);
    // AddHeap(A, len, 50);
    DelHeap(A, len, 1);
    printf("增删处理后\n");
    ShowArray(A, len);
    printf("\n");
    DelHeap(A, len, 1);
    printf("增删处理后\n");
    ShowArray(A, len);
    printf("\n");
    for (int i = len; i > 1; i--) {
        Swap(A[i], A[1]);
        HeadAdjust(A, 1, i - 1);
    }

    TestOrder(A, len);
}

int main() {
    // ^ 方法一
    Sort(HeapSort, SIZE);
}