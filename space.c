#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *txt = "this    is a       test   ";

    char *p = txt;
    char *q = NULL;
    int s = 0;
    int w = 0;
    while(p)
    {
        if(*p == ' ')
        {
            p++;
            s++;
        }
        else
        {
            q = strchr(p, ' ');
            printf("q = [%s] , off=%d\n", q, q-txt);
            if(q)
            {
                      p = q;
                      w++;
            }
        }
    }
    if(p)
    {
        printf(" p = %s\n", p);
        w++;
    }
    printf("txt = [%s], s=%d, w = %d\n", txt, s, w);
    return 0;

}
