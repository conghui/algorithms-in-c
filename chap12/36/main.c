#include <stdio.h>

#include "st.h"

int main(void)
{
    int n = 10;
    int i;
    st_t st;
    st = st_init(n);

    for (i = 0; i < n; i++) {
        st_insert(st, i);
    }

    for (i = 0; i < n; i++) {
        if (st_search(st, i)) {
            printf("Found key %2d\n", i);
        }
    }

    st_finalize(&st);
    return 0;
}
