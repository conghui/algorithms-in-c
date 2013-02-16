#include <stdio.h>
#include <stdlib.h>

typedef struct _node_t {
    int             entry;
    struct _node_t *next;
} node_t;

static void usgerr(const char *progname);

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        usgerr(*argv);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    node_t *start;
    node_t *last;
    start = last = malloc(sizeof *start);
    start->entry = 1;
    start->next = start;
    int i;

    for (i = 2; i <= N; i++) {
        last = last->next = malloc(sizeof *last);
        last->entry = i;
        last->next = start;
    }

    while (last->next != last) {
        for (i = 1; i < M; i++) {
            last = last->next;
        }

        /* delete the node after the last node */
        node_t *tmp = last->next;
        last->next = tmp->next;
        printf("%4d", tmp->entry);
        free(tmp);
    }

    printf("\nthe last one is: %d\n", last->entry);
    return 0;
}

static void usgerr(const char *progname)
{
    fprintf(stderr, "usage: %s N M\n", progname);
    exit(EXIT_FAILURE);
}
