#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int comp(const void *v1, const void *v2);

int main(void)
{
    int i;
    int nlines;
    char *text[BUFSIZ];
    char line[BUFSIZ];

    for (i = 0, nlines = 0;
         i < BUFSIZ && fgets(line, BUFSIZ, stdin);
         i++, nlines++) {
        text[i] = malloc(strlen(line) + 1); /* allocate buffer */
        strncpy(text[i], line, strlen(line) + 1);
    }

    qsort(text, nlines, sizeof *text, comp);

    /* print them */
    for (i = 0; i < nlines; i++) {
        fputs(text[i], stdout);
    }

    /* free them */
    for (i = 0; i < nlines; i++) {
        free(text[i]);
    }

    return 0;
}

static int comp(const void *v1, const void *v2)
{
    const char *l = *(const char **)v1;
    const char *r = *(const char **)v2;
    return strcmp(l, r);
}
