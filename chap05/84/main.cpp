#include <stdio.h>
#include <limits.h>

#include "btree.h"
static int findidx(char *A, int start, int end, char value);
void visit(link_t link);
link_t build(char *preA, char *inA, int inStart, int inEnd);

int main(void)
{
    char preA[] = {'E', 'D', 'B', 'A', 'C', 'H', 'F', 'G'};
    char inA[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    link_t root = build(preA, inA, 0, 8);
    preorder_traverse(root, visit);
    return 0;
}

void visit(link_t link)
{
    printf("%c ", link->item);
}

link_t build(char *preA, char *inA, int inStart, int inEnd)
{
    static int i = 0;

    /* the end mark */
    if (inStart > inEnd) {
        return NULL;
    }

    link_t root;
    root = newlink(preA[i++], NULL, NULL);

    if (inStart == inEnd) { /* no child at all */
        return root;
    }

    int rootidx = findidx(inA, inStart, inEnd, root->item);
    root->l = build(preA, inA, inStart, rootidx - 1);
    root->r = build(preA, inA, rootidx + 1, inEnd);
    return root;
}

static int findidx(char *A, int start, int end, char value)
{
    int i;

    for (i = start; i <= end; i++)  {
        if (A[i] == value) {
            return i;
        }
    }

    return -1;
}
