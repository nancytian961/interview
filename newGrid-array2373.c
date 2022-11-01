#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int arr[][4]= {
        //{1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5},{1,2,3,4,5}
        {9,9,8,1},{5,6,2,6},{8,2,6,4},{6,2,2,2}
    };
    int count = sizeof(arr[0])/sizeof(int);
    int retSize = count-2;

    printf("inputSize = %d, outputSize = %d\n", count, retSize);

    int** ret = (int**)malloc(sizeof(int*)*(retSize+1));
    int i = 0, j = 0;
    int r = 0, c = 0;
    int max = 0;
    for(i=0;i<retSize;i++)
    {
        ret[i] = (int*)malloc(sizeof(int)*(retSize+1));
        memset(ret[i], 0, sizeof(int)*(retSize+1));
    }

    for(i=0;i<retSize;i++)
    {
        for(j=0; j< retSize; j++)
        {
            max = 0;
            for(r=i;r<i+3;r++)
            {
                for(c=j;c<j+3;c++)
                {
                    //printf("i=%d, j = %d, r = %d, c = %d \n", i, j, r, c);
                    max = max > arr[r][c] ? max : arr[r][c];
                }
            }
            ret[i][j] = max;
            printf(" %d",max);
        }
        printf("\n");
    }
       
    return 0;
}
