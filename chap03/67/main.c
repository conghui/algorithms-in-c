#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define ROW 5
#define COL 5
#define N 3

static inline int rand_i(int n);
static void fill_matrix(int (*matrix)[COL], int row, int col);
static void print_matrix(int (*matrix)[COL], int row, int col);
static void matrix2list(int (*matrix)[COL], int row, int col, list_t *list);
static void init_list(list_t *list, int row);
static void delete_list(list_t *list, int row);
static void print_list(list_t *list, int row);

int main(void)
{
    int matrix[ROW][COL];
    list_t list[ROW];
    fill_matrix(matrix, ROW, COL);
    print_matrix(matrix, ROW, COL);
    printf("\nBelow is the convertion:\n\n");
    /* init the list */
    init_list(list, ROW);
    matrix2list(matrix, ROW, COL, list);
    print_list(list, ROW);
    delete_list(list, ROW);
    return 0;
}

static inline int rand_i(int n)
{
    return rand() % n;
}

static void fill_matrix(int (*matrix)[COL], int row, int col)
{
    int i;
    int j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            matrix[i][j] = rand_i(N);
        }
    }
}

static void print_matrix(int (*matrix)[COL], int row, int col)
{
    int i;
    int j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%3d", matrix[i][j]);
        }

        putchar('\n');
    }
}

static void matrix2list(int (*matrix)[COL], int row, int col,
                        list_t *list)
{
    int i;
    int j;

    for (i = 0; i < row; i++) {
        list_t tail = list[i];

        for (j = 0; j < col; j++) {
            if (matrix[i][j] != 0) {
                list_t nn = list_newnode(matrix[i][j]);
                list_insert(tail, nn);
                tail = nn;
            }
        }
    }
}

static void init_list(list_t *list, int row)
{
    int i;

    for (i = 0; i < row; i++) {
        list[i] = list_new();
    }
}

static void delete_list(list_t *list, int row)
{
    int i;

    for (i = 0; i < row; i++) {
        list_free(list[i]);
    }
}

static void print_list(list_t *list, int row)
{
    int i;

    for (i = 0; i < row; i++) {
        list_print(list[i]);
    }
}
