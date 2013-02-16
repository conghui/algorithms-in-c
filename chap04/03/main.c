#include <stdio.h>

#define ITEMShow(Item) \
    printf("%d", (Item));

typedef int Item;

int main()
{
    Item a = 1;
    ITEMShow(a);
    return 0;
}
