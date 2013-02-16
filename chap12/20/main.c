#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "st.h"

#define keymax 100
#define strsiz 10

void print(item_t x);
key_t randkey();
char *randstr(char *s, size_t size);

int main(void)
{
    size_t max = 100;
    size_t n = 1;
    char buf[strsiz];
    size_t i;
    st_t st = st_init(max);
    st_t st2 = st_init(max);

    for (i = 0; i < n; i++) {
        item_t t = newitem(randkey(), randstr(buf, strsiz));
        item_t t2 = newitem(randkey(), randstr(buf, strsiz));
        st_insert(st, t);
        st_insert(st2, t2);
    }

    st_join(st, st2);
    st_sort(st, print);
    st_finalize(st);
    st_finalize(st2);
    return 0;
}

void print(item_t x)
{
    if (x == NULL) {
        printf("NULL\n");
    }

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
