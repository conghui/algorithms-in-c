#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
static int **malloc2d(int row, int col);
static void free2d(int **matrix, int row);
static void print2d(int *const *matrix, int row, int col);

int main(int argc, const char *argv[])
{
    int row;
    int col;
    int **matrix;
    int i, j;

    if (argc != 3) {
        fprintf(stderr, "usage: %s row col\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    row = atoi(argv[1]);
    col = atoi(argv[2]);

    if (row <= 0 || col <= 0) {
        fprintf(stderr, "row and col should be greater than 0\n");
        exit(EXIT_FAILURE);
    }

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
    matrix = malloc(row * sizeof *matrix);
    assert(matrix);

    for (i = 0; i < row; i++) {
        matrix[i] = calloc(col, sizeof *matrix[i]);
        assert(matrix[i]);
        matrix[i][i] = 1;
    }

    return matrix;
}

static void free2d(int **matrix, int row)
{
    int i;

    if (matrix == NULL) {
        return;
    }

    for (i = 0; i < row; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

static void print2d(int *const *matrix, int row, int col)
{
    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%3d", matrix[i][j]);
        }

        printf("\n");
    }
}
