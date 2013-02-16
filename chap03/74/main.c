#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define A 1
#define B 0

static int **malloc2d(int row, int col);
static void free2d(int **matrix, int row);
static void print2d(int **matrix, int row, int col);
static int vertice_between(int **matrix, int row, int a, int b);

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
    printf("Total count is: %d\n", vertice_between(matrix, row, A, B));
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

static int vertice_between(int **matrix, int row, int a, int b)
{
    int i;
    int cnt;
    printf("The vertice between %d and %d are: ", a, b);

    for (i = 0, cnt = 0; i < row; i++) {
        if (matrix[i][a] == 1 && matrix[i][b] == 1) {
            printf("%3d", i);
            cnt++;
        }
    }

    printf("\n");
    /* the above calculating include vertice a and b,
     * so we should subtract them */
    return cnt;
}
