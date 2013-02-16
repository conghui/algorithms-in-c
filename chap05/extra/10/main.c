#include <stdio.h>
void list_number_ascend(int start, int end);
void list_number_descend(int start, int end);

int main(void)
{
    list_number_ascend(1, 20);
    putchar('\n');
    list_number_descend(1, 20);
    putchar('\n');
    return 0;
}

void list_number_ascend(int start, int end)
{
    if (start == end) {
        printf("%3d", start);
        return;
    }

    list_number_ascend(start, end - 1);
    printf("%3d", end);
}

void list_number_descend(int start, int end)
{
    if (start == end) {
        printf("%3d", start);
        return;
    }

    printf("%3d", end);
    list_number_descend(start, end - 1);
}
