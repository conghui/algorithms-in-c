#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "st.h"

#define keymax INT_MAX;
#define strsiz 10

void print(item_t x);
key_t randkey();
char *randstr(char *s, size_t size);

int main(void)
{
    size_t max = 10000;
    size_t n = 5;
    char buf[strsiz];
    size_t i;
    clock_t begin, end;
    double sec;
    st_t st = st_init(max);
    size_t j = 0;

    for (; j < n; j++) {
        begin = clock();

        for (i = 0; i < max; i++) {
            item_t t = newitem(randkey(), randstr(buf, strsiz));
            st_insert(st, t);
        }

        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d insertion needs %.2f seconds\n", j+1, sec);
        /* clear the list by select the first one and delete it */
        begin = clock();

        while (!st_empty(st)) {
            st_delete(st, st_select(st, 0));
        }

        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d deletion needs %.2f seconds\n\n", j + 1, sec);
    }

    st_finalize(st);
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
