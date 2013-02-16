#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
static int **malloc2d(size_t r, size_t c);
static int ** *malloc3d(size_t row, size_t col, size_t depth);

int main(void)
{
    size_t row   = 5;
    size_t col   = 5;
    size_t depth = 5;
    int **matrix = malloc2d(row, col);
    int ***cube;
    size_t i;
    size_t j;
    cube = malloc3d(row, col, depth);
    int cnt = 0;
    size_t k;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            for (k = 0; k < depth; k++) {
                printf("%4d", ++cnt);
            }

            printf("\n");
        }

        printf("\n");
    }

    return 0;
}

static int **malloc2d(size_t r, size_t c)
{
    size_t i;
    int **matrix = calloc(r, sizeof *matrix);
    assert(matrix);

    for (i = 0; i < r; i++) {
        matrix[i] = calloc(c, sizeof *matrix[i]);
        assert(matrix[i]);
    }

    return matrix;
}

static int ** *malloc3d(size_t row, size_t col, size_t depth)
{
    int ***cube = calloc(row, sizeof *cube);
    assert(cube);
    size_t i;

    for (i = 0; i < row; i++) {
        cube[i] = calloc(col, sizeof *cube[i]);
        assert(cube[i]);
    }

    size_t j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cube[i][j] = calloc(depth, sizeof *cube[i][j]);
            assert(cube[i][j]);
        }
    }

    return cube;
}
