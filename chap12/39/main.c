#include <stdio.h>
#include <stdlib.h>

typedef int key_t;
size_t binary_search(key_t *a, int l, int r, key_t value);

int main(void)
{
    int n     = 10;
    key_t *a = malloc(n * n * sizeof *a);
    int i;
    int size = 0;

    for (i = 0; i < n; i++) {
        int j = 0;

        for (; j < i; j++) {
            a[size++] = i;
        }
    }

    for (i = 0; i < n; i++) {
        printf("There are %u %i in the array\n",
               binary_search(a, 0, size - 1, i), i);
    }

    free(a);
    return 0;
}

size_t binary_search(key_t *a, int l, int r, key_t value)
{
    if (l > r) {
        return 0;
    }

    int mid = l + ((r-l) >> 1);

    if (value == a[mid]) {
        size_t cnt = 1;
        int i;

        for (i = mid - 1; i >= l && value == a[i]; cnt++, i--) ;

        for (i = mid + 1; i <= r && value == a[i]; cnt++, i++) ;

        return cnt;
    } else if (value < a[mid]) {
        return binary_search(a, l, mid - 1, value);
    } else {
        return binary_search(a, mid + 1, r, value);
    }
}
