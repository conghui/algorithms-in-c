#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _list_t *list_t;

struct _list_t {
    int entry;
    list_t next;
};
void print(list_t head);
void list_free(list_t head);
list_t list_sort(list_t head);

int main(void)
{
    int i;
    list_t head = NULL;

    for (i = 0; i < 10; i++) {
        list_t nn = malloc(sizeof *nn);
        nn->entry = i;
        nn->next  = NULL;
        nn->next = head;
        head = nn;
    }

    print(head);
    head = list_sort(head);
    print(head);
    list_free(head);
    return 0;
}

void print(list_t head)
{
    for (; head != NULL; head = head->next) {
        printf("%3d", head->entry);
    }

    putchar('\n');
}

void list_free(list_t head)
{
    list_t tmp;

    for (tmp = head; tmp != NULL;) {
        head = head->next;
        free(tmp);
        tmp = head;
    }
}

list_t list_sort(list_t head)
{
    assert(head);
    list_t sortlist;
    list_t cur;
    list_t next;
    cur      = head;
    sortlist = NULL;

    while (cur != NULL) {
        next = cur->next;
        list_t tmp;
        list_t prev;
        tmp = sortlist;

        for (prev = NULL; tmp != NULL; tmp = tmp->next) {
            prev = tmp;

            if (prev->entry > cur->entry) {
                if (prev == sortlist) {
                    prev = NULL;
                }

                break;
            }
        }

        if (prev == NULL) { /* insert at the first element */
            cur->next = sortlist;
            sortlist = cur;
        } else {
            cur->next  = prev->next;
            prev->next = cur;
        }

        cur = next;
    }

    return sortlist;
}
