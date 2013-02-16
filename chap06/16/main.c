#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef int item_t;

#define key(A) (A)

#define less(A, B) \
    (key(A) < key(B))

#define exch(A, B) { \
        item_t _tmp = A; \
        A           = B; \
        B           = _tmp; \
    }

#define compexch(A, B)  \
    if (less(B, A)) \
        exch(A, B) \
         
static void print(int *a, int size);
void sort(item_t a[], int l, int r);

static int count;

void sort(item_t a[], int l, int r)
{
    int i, j;

    for (i = l + 1; i <= r; i++) {
        j = i;

        while (less(a[j], a[j-1])) {
            count++;
            compexch(a[j-1], a[j]);
            j--;
        }
    }
}

int main(void)
{
    int i;
    int N  = 50;
    int *a = calloc(N, sizeof *a);
    a[0] = INT_MIN;

    for (i = 1; i <= N; i++) {
        a[i] = rand() % 100;
    }

    print(a, N);
    count = 0;
    sort(a, 1, N);
    print(a, N);
    printf("compare times: %d\n", count);
    return 0;
}

static void print(int *a, int size)
{
    int i;

    for (i = 1; i < size; i++) {
        printf("%3d ", a[i]);
    }

    putchar('\n');
}
