#include <stdio.h>
#include <time.h>

int main(void)
{
    int n = 20000;
    int i;
    int cnt = 0;
    clock_t begin;
    clock_t end;
    begin = clock();

    for (i = 0; i < n; i++) {
        int j;

        for (j = i; j < n; j++) {
            cnt += j;
            cnt /= 2;
            /*cnt >>= 1;*/
        }
    }

    end        = clock();
    double sec = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("cnt: %d, time elapse: %f\n", cnt, sec);
    return 0;
}
