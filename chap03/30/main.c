#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE(x) \
    ((sizeof x) / (sizeof *x))

typedef struct _node_t  node_t;
struct _node_t {
    int     entry;
    node_t *next;
};
static void elect(int n, int m);

int main(void)
{
    unsigned int i;
    unsigned int j;
    int M[] = {2, 3, 5};
    int N[] = {1000, 10000, 100000, 1000000};

    for (i = 0; i < SIZE(N); i++) {
        for (j = 0; j < SIZE(M); j++) {
            elect(N[i], M[j]);
        }

        putchar('\n');
    }

    return 0;
}

static void elect(int n, int m)
{
    int i;
    node_t *head;
    node_t *tail;
    head = tail = malloc(sizeof *head);
    assert(head && tail);
    head->entry = 1;
    head->next = head;

    /* add the node to the list */
    for (i = 2; i <= n; i++) {
        tail = tail->next = malloc(sizeof *tail);
        assert(tail);
        tail->entry = i;
        tail->next = head;
    }

    /* elect the leader */
    while (tail != tail->next) {
        node_t *tmp;

        for (i = 1; i < m; i++) {
            tail = tail->next;
        }

        /* remove the node after tail */
        tmp = tail->next;
        tail->next = tmp->next;
        free(tmp);
    }

    printf("for n = %d, m = %d, the leader is %d\n", n, m, tail->entry);
}
