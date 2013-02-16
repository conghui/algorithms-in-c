#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
static list_t *init_list(int row);
static void delete_list(list_t *list, int row);
static void print(list_t *list, int row);

int main(int argc, const char **argv)
{
    int     row;
    list_t *list;
    int     i;
    int     j;

    if (argc != 2) {
        fprintf(stderr, "usage: %s row\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    row  = atoi(argv[1]);

    if (row <= 0) {
        fprintf(stderr, "row should be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    list = init_list(row);

    while (scanf("%d%d", &i, &j) == 2) {
        list_t nn = list_newnode(j);
        list_insert_next(list[i], nn);
        /* the link list is synmetric, so continue adding */
        nn = list_newnode(i);
        list_insert_next(list[j], nn);
    }

    print(list, row);
    delete_list(list, row);
    return 0;
}

static list_t *init_list(int row)
{
    int i;
    list_t *list = calloc(row, sizeof *list);
    assert(list);

    for (i = 0; i < row; i++) {
        list[i] = list_new();
    }

    return list;
}

static void delete_list(list_t *list, int row)
{
    if (list == NULL) {
        return;
    }

    int i;

    for (i = 0; i < row; i++) {
        list_free(list[i]);
    }

    free(list);
}

static void print(list_t *list, int row)
{
    int i;

    for (i = 0; i < row; i++) {
        list_print(list[i]);
    }
}
