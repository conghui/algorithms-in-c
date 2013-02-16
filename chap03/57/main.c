#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[BUFSIZ];

    while (fgets(str, BUFSIZ, stdin)) {
        size_t len = strlen(str);
        str[len-1] = '\0'; /* replace '\n' with '\0' */
        const char *p1;
        const char *p2;
        p1 = str;   /* points to the fist */
        p2 = str + strlen(str) - 1; /* points to the last */
        char c1;
        char c2;
        int same = 1;

        while (p1 < p2 && same == 1) {
            while ((c1 = *p1++) == ' ') /* first non space char */
                ;

            while ((c2 = *p2--) == ' ') /* first non space char in reverse order */
                ;

            if (c1 != c2) {
                same = 0;
            }
        }

        if (same) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}

