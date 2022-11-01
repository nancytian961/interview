#include <stdio.h>

#define ADD(x) x + x
#define SUB(x) x - x



void func()
{
    int x = 0;
    static int y = 0;
    x++; y++;
    printf(" func %d--- %d \n", x, y);
}
int main()
{
    int y = ADD(3)/SUB(3);
    printf("%d", ADD(y));


    int a = 3, b =4;
    
    printf("a= %d, b = %d\n", a, b);
    a = a&b;
    b = a|b;
    a = a|b;
    printf("a= %d, b = %d\n", a, b);


    func();
    func();
    return 0;
}
