#include <stdio.h>
#include <stdlib.h>

void sort(int *a, int l, int r);
void foreach(int *a, int n, void (*visit)(int *));
void init(int *a);
void print(int *a);

void sort(int *a, int l, int r)
{
    int h;

    /* look for the max gap */
    for (h = 1; h < r - l; h = h * 3 + 1) ;

    for (; h > 0; h /= 3) {
        /* for each gap, perform a insertion */
        int i;

        for (i = l + h; i <= r; i++) {
            int j = i;
            int v = a[i];

            for (; j >= l + h && v < a[j-h]; j -= h) {
                a[j] = a[j-h];
            }

            a[j] = v;
        }
    }
}

int main(void)
{
    int n  = 20;
    int *a = malloc(n * sizeof *a);
    foreach(a, n, init);
    foreach(a, n, print);
    putchar('\n');
    sort(a, 0, n-1);
    foreach(a, n, print);
    putchar('\n');
    free(a);
    return 0;
}

void foreach(int *a, int n, void (*visit)(int *))
{
    int i;

    for (i = 0; i < n; i++) {
        visit(a + i);
    }
}

void init(int *a)
{
    *a = rand() % 100;
}

void print(int *a)
{
    printf("%3d ", *a);
}
