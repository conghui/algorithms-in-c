#include <stdio.h>

static void swap(int *a, int *b);
void compexch(int *a, int *b, int *c);
void compexch(int *a, int *b, int *c)
{
    if (*a < *b) {
        if (*c < *a) {
            swap(c, a);
            swap(b, c);
        } else if (*c > *b) {
            return ; /* a < b < c */
        } else {
            /* a < c < b */
            swap(c, b);
        }
    } else {
        if (*c < *b) {
            swap(a, c);
        } else if (*c > *a) {
            swap(a, b);
        } else {
            swap(a, b);
            swap(b, c);
        }
    }
}

static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

int main(void)
{
    int a = 2;
    int b = 3;
    int c = 1;
    compexch(&a, &b, &c);
    printf("%d %d %d\n", a, b, c);
    return 0;
}
