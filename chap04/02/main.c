#include <math.h>
#include <stdio.h>

#define eq(A, B) \
    pointEq(A, B)

typedef struct point Item;

struct point {
    double x;
    double y;
};

inline int doubleEq(double a, double b);
inline int pointEq(struct point a, struct point b);

int main(void)
{
    Item A = {3.1415927, 3.1415926};
    Item B = {3.1415928, 3.1415929};

    if (eq(A, B)) {
        printf("Item A equals to Item B\n");
    } else {
        printf("Item A not equals to Item B\n");
    }

    return 0;
}

inline int doubleEq(double a, double b)
{
    return fabs(a - b) / (a > b ? a : b) < 1E-6;
}

inline int pointEq(struct point a, struct point b)
{
    return doubleEq(a.x, b.x) && doubleEq(a.y, b.y);
}

