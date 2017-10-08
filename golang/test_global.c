#include <stdio.h>

int *GLOBAL_PTR;

void func()
{
    int local_a = 10;
    GLOBAL_PTR = &local_a;
}

int main(void)
{
    func();
    printf("*GLOBAL_PTR = %d\n", *GLOBAL_PTR);
    return 0;
}
