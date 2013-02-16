#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

static int **malloc2d(int row, int col);
static void free2d(int **matrix, int row);
static void print2d(int **matrix, int row, int col);
static list_t *init_list(int row);
static void delete_list(list_t *list, int row);
static void print(list_t *list, int row);

int main(void)
{
    int **matrix;
    list_t *list;
    int row = 7;
    int col = 7;
    int i;
    int j;
    matrix = malloc2d(row, col);
    list = init_list(row);

    while (scanf("%d%d", &i, &j) == 2) {
        matrix[i][j] = 1; /* assign for the adjacent matrix */
        /* assignment for the adjacent list */
        list_t nn = list_newnode(j);
        list_insert_next(list[i],nn);
    }

    print2d(matrix, row, col);
    free2d(matrix, row);
    print(list, row);
    delete_list(list, row);
    return 0;
}

static int **malloc2d(int row, int col)
{
    int i;
    int **matrix;
    matrix = calloc(row, sizeof *matrix);
    assert(matrix);

    for (i = 0; i < row; i++) {
        matrix[i] = calloc(col, sizeof *matrix[i]);
        assert(matrix[i]);
    }

    return matrix;
}

static void free2d(int **matrix, int row)
{
    int i;
    assert(matrix);

    for (i = 0; i < row; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

static void print2d(int **matrix, int row, int col)
{
    int i, j;
    printf("   ");

    for (i = 0; i < row; i++) {
        printf("%3d", i);
    }

    printf("\n");

    for (i = 0; i < row; i++) {
        printf("%3d", i);

        for (j = 0; j < col; j++) {
            printf("%3d", matrix[i][j]);
        }

        printf("\n");
    }
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
    printf("\n");

    for (i = 0; i < row; i++) {
        printf("%d", i);
        list_print(list[i]);
    }
}
