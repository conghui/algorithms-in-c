#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "st.h"

#define keymax 10000
#define strsiz 10

void print(item_t x);
key_t randkey();
char *randstr(char *s, size_t size);

int main(void)
{
    size_t max = 100000;
    size_t n = 200;
    char buf[strsiz];
    size_t i;
    st_t st = st_init(max);

    for (i = 0; i < n; i++) {
        item_t t = newitem(i, randstr(buf, strsiz));
        st_insert(st, t);
    }

    /* search items in a specific range */
    int m       = 10;
    int nsearch = 1000;

    while (nsearch-- > 0) {
        st_search(st, rand()%m);
    }

    st_finalize(&st);
    return 0;
}

void print(item_t x)
{
    printf("%3d: %s\n", getkey(x), getstr(x));
}

key_t randkey()
{
    return rand()%keymax;
}

char *randstr(char *s, size_t size)
{
    static const char *alphanum = "0123456789"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t len = strlen(alphanum);
    size_t i;

    for (i = 0; i < size; i++) {
        s[i] = alphanum[rand()%len];
    }

    s[i-1] = '\0';
    return s;
}
