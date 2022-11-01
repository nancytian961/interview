#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char devName[7][20] = {"printer", "tv", "printer", "tv","printer", "tv", "monitor"};
    int  devCount = 7;

    int i = 0, j = 0;
    int len = 0;
    int count[7] = {0};
    char** retDev = (char**)malloc(sizeof(char*)*(devCount+1));

    //method1
    char** uniqDev = (char**)malloc(sizeof(char*)* (devCount+1));
    int uniq = 0;
    for(i=0;i<devCount;i++)
    {
        len = strlen(devName[i])+8;
        retDev[i] = (char*)malloc(sizeof(char)*len);
        j = 0;
        while(j<uniq)
        {
            if(strcmp(devName[i], uniqDev[j])==0)
            {
                sprintf(retDev[i], "%s%d", devName[i], count[j]);
                count[j]++;
                break;
            }
            j++;
        }
        if(j== uniq)
        {
            strcpy(retDev[i], devName[i]);
            uniqDev[uniq] = devName[i];
            count[uniq] = 1;
            uniq++;

        }
        printf("%d ========================================= %s\n", __LINE__, retDev[i]);
    }
    free(uniqDev);

    //method2
    i=0;
    strcpy(retDev[i],devName[0]);
    count[0] = 1;
    for(i = 1; i< devCount; i++)
    {
        j = i-1;
        while(j>=0)
        {
            if(strcmp(devName[i], devName[j])==0)
            {
                sprintf(retDev[i], "%s%d", devName[i], count[j]);
                count[i] = count[j]+1;
                break;
            }
            j--;
        }
        if(j<0)
        {
            strcpy(retDev[i],devName[i]);
            count[i] = 1;
        }
        printf("%d ========================================= %s\n", __LINE__, retDev[i]);
    }
    return 0;
}
