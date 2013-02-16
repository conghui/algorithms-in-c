#include <stdio.h>
#include <ctype.h>

#include "deque.h"

#define SIZE(x) \
    (sizeof (x)) / (sizeof *(x))

int main()
{
    const char *output[] = {"EsaY", "YasE", "aYsE", "asYE"};
    const char *input = "EasY";
    const char *pinput; /* point to input */
    const char *poutput; /* point to output */
    size_t i;

    for (i = 0; i < SIZE(output); i++) {
        pinput = input;
        poutput = output[i];
        printf("for pattern %s:\n", poutput);

        for (; *poutput != '\0';) {
            if (!deque_empty() && deque_front() == *poutput) {
                printf("+\t%c\n", deque_pop_front());
                poutput++;
            } else if (!deque_empty() && deque_back() == *poutput) {
                printf("*\t%c\n", deque_pop_back());
                poutput++;
            } else { /* the deque is empty or not the first or last */
                if (islower(*pinput)) {
                    deque_push_back(*pinput++);
                } else if (isupper(*pinput)) {
                    deque_push_front(*pinput++);
                } else if (*pinput == '\0') {
                    printf("unable to generate such pattern\n");
                    break;
                }
            }
        }

        putchar('\n');
    }

    return 0;
}
