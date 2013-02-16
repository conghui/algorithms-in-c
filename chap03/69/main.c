#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static int **malloc2d(int row, int col);
static void free2d(int **matrix, int row);
static void print2d(int **matrix, int row, int col);

int main(void)
{
    int **matrix;
    int row = 7;
    int col = 7;
    int i;
    int j;
    matrix = malloc2d(row, col);

    while (scanf("%d%d", &i, &j) == 2) {
        matrix[i][j] = matrix[j][i] = 1;
    }

    print2d(matrix, row, col);
    free2d(matrix, row);
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

    for (i = 0; i < row; i++) {
        matrix[i][i] = 1;
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
