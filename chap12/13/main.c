#include <stdio.h>
#include <limits.h>
#include "st.h"

int main(void)
{
    int n = 10000000;
    st_t st = st_init(n);

    for (int i = 1; i <= n; i++) {
        st_insert(st, i);
    }

    printf("%.2f\n", st_avg(st));
    return 0;
}
