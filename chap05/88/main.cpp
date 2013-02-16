#include <stdio.h>

#include "btree.h"
void print(link_t l);

int main(void)
{
    btree_t bt;
    char *pre = "123##45##67###8##";
    /*char *pre = "12#4##3##";*/
    bt = btree_init(pre);
    count = 0;
    int inner_length;
    inner_length = btree_internal_length(bt);
    printf("The length of internal node is: %d, count=%d\n",
           inner_length, count);
    count = 0;
    inner_length = btree_internal_length2(bt);
    printf("The length of internal node is: %d, count = %d\n",
           inner_length, count);
    count = 0;
    inner_length = btree_internal_length3(bt);
    printf("The length of internal node is: %d, count = %d\n",
           inner_length, count);
    btree_finalize(&bt);
    return 0;
}

void print(link_t l)
{
    if (l == NULL) {
        return ;
    }

    printf("%d ", l->item);
}
