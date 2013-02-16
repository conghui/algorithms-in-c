#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "bst.h"

#define MAX RAND_MAX

int main(void)
{
    int n = 1000000;
    int k = 1000;

    for (; k <= n; k *= 10) {
        clock_t begin;
        clock_t end;
        double sec;
        int i;
        bst_t bst1 = bst_init();
        bst_t bst2 = bst_init();
        int *item = malloc(k * sizeof *item);
        int *result1 = malloc(k * sizeof *result1);
        int *result2 = malloc(k * sizeof *result2);
        int *search_items = malloc(k * sizeof *search_items);

        for (i = 0; i < k; i++) {
            item[i] = rand()%MAX;
            search_items[i] = rand()%MAX;
        }


        begin = clock();
        for (i = 0; i < k; i++) {
            bst_insert_normal(bst1, item[i]);
        }
        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("For n = %7d,  Normal insert use %.2f seconds, ", k, sec);

        begin = clock();
        for (i = 0; i < k; i++) {
            result1[i] = bst_find(bst1, search_items[i]);
        }
        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("search uses %.2f seconds\n", sec);

        begin = clock();
        for (i = 0; i < k; i++) {
            bst_insert_balance(bst2, item[i]);
        }
        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("For n = %7d, Balance insert use %.2f seconds, ", k, sec);

        begin = clock();
        for (i = 0; i < k; i++) {
            result2[i] = bst_find(bst2, search_items[i]);
        }
        end = clock();
        sec = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("search use %.2f seconds\n\n", sec);

        assert(memcmp(result1, result2, k * sizeof *result1) == 0);
        bst_finalize(&bst1);
        bst_finalize(&bst2);
        free(item);
        free(search_items);
        free(result1);
        free(result2);
    }
    return 0;
}
