#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>


static int N  = 1e5;
static int M  = 997;
int foo(int base, int exp, int mod);
int bar(int base, int exp, int mod);
int fac_mod(int n, int mod);
int fac_mod2(int n, int mod);

int main(void)
{
    clock_t start;
    clock_t end;
    int result;
    start = clock();
    result = fac_mod(N, M);
    end    = clock();
    printf("%d! %% %d = %d; need %g sec\n",
           N, M, result, (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    result = fac_mod2(N, M);
    end    = clock();
    printf("%d! %% %d = %d; need %g sec\n",
           N, M, result, (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

int foo(int base, int exp, int mod)
{
    int ans;
    int i;

    for (ans = 1, i = 0; i < exp; i++) {
        ans = (ans * base) % mod;
    }

    return ans;
}

int bar(int base, int exp, int mod)
{
    int result;
    result = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        exp >>= 1;
        base = (base * base) % mod;
    }

    return result;
}

int fac_mod(int n, int mod)
{
    if (n == 1) {
        return 1;
    }

    return ((n % mod) * fac_mod(n - 1, mod)) % mod;
}

int fac_mod2(int n, int mod)
{
    int i;
    int result;
    result = 1;

    for (i = 1; i <= n; i++) {
        result *= i;

        if (result >= mod) {
            result %= mod;
        }
    }

    return result;
}
