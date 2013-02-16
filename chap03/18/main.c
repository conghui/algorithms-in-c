#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXVAL 1000 /* max value */

#define YES 1
#define NO  0

#define rand_i(x) \
    (rand() % (x))

static int occupy[MAXVAL];
static int repeat();
static void clear();

int main(void)
{
    int i;
    double sum;
    srand(time(NULL));

    /* test MAXVAL times and calculate the avg */
    for (i = 0, sum = 0; i < MAXVAL; i++) {
        sum += repeat();
    }

    printf("average times if a value between [0, %d] is repeated is: %f\n",
           MAXVAL, sum / MAXVAL);
    return 0;
}

static int repeat()
{
    int cnt;
    clear();

    for (cnt = 1; ; cnt++) {
        int n = rand_i(MAXVAL);

        if (occupy[n] == YES) {
            break;
        } else {
            occupy[n] = YES;
        }
    }

    return cnt;
}

static void clear()
{
    int i;

    for (i = 0; i < MAXVAL; i++) {
        occupy[i] = NO;
    }
}
