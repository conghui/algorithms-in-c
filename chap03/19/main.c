#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXVAL 1000 /* max value */

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

    printf("average times if all value between [0, %d) are repeated is: %f\n",
           MAXVAL, sum / MAXVAL);
    return 0;
}

static int repeat()
{
    int cnt;
    int leftcnt;
    clear();
    leftcnt = MAXVAL;

    for (cnt = 1; leftcnt > 0 ; cnt++) {
        int n = rand_i(MAXVAL);

        if (occupy[n] == 0) {
            leftcnt--;
        }

        occupy[n]++;
    }

    return cnt;
}

static void clear()
{
    memset(occupy, 0, MAXVAL * sizeof *occupy);
}

