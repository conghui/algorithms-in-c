#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
static int charcmp(const void *v1, const void *v2);

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *str = malloc(strlen(argv[1]) + 1);
    assert(str);
    strncpy(str, argv[1], strlen(argv[1]) + 1);
    /* sort the string */
    qsort(str, strlen(str), sizeof *str, charcmp);
    printf("%10s%10s\n", "char:", "times");
    size_t i;
    int cnt = 1;

    for (i = 1; i < strlen(str); i++) {
        if (str[i] == str[i-1]) {
            cnt++;
        } else {
            printf("%10c%10d\n", str[i-1], cnt);
            cnt = 1;
        }
    }

    printf("%10c%10d\n", str[i-1], cnt);
    free(str);
    return 0;
}

static int charcmp(const void *v1, const void *v2)
{
    const char l = *(const char *)v1;
    const char r = *(const char *)v2;
    return l - r;
}
