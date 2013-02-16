#include <stdio.h>
#include <string.h>

#define nil '\0'

int count(char *str, int c);
int _count(char *str, int a, int b, int c);

int times = 0;

int main(void)
{
    char *str = "aabcdaa";
    printf("there are %d 'a' in %s\n", count(str, 'a'), str);
    printf("The recursion is called %d times\n", times);
    return 0;
}

int count(char *str, int c)
{
    return _count(str, 0, strlen(str) - 1, c);
}

int _count(char *str, int a, int b, int c)
{
    times++;

    if (a == b) {
        return str[a] == c ? 1 : 0;
    }

    return (str[a] == c ? 1 : 0) + _count(str, a + 1, b, c);
}
