#include <stdio.h>

int main(void)
{
    int a = 10;
    int *p;
    p = &a;
    printf("a = %d, p = 0x%x\n", a, p);
    (*p)++;
    printf("(*p)++\n");
    printf("a = %d, p = 0x%x\n", a, p);
    *p++;
    printf("*p++\n");
    printf("a = %d, p = 0x%x\n", a, p);
}
