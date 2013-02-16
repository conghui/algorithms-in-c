#include <stdio.h>
static void trim(char *dest, const char *src);

int main(void)
{
    char buf[BUFSIZ];
    char dest[BUFSIZ];

    while (fgets(buf, BUFSIZ, stdin)) {
        trim(dest, buf);
        printf("%s", dest);
    }

    return 0;
}

static void trim(char *dest, const char *src)
{
    const char *p = src;

    while (*p != '\0') {
        if (*p == ' ') {
            while (*++p == ' ')
                ;

            *dest++ = ' ';
        } else {
            *dest++ = *p++;
        }
    }

    *dest = '\0';
}
