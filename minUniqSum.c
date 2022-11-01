#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(int arr[], int n)
{
    int i=0,j=0;
    int key = 0;
    for(i=1;i<n;i++)
    {
        j = i-1;
        key = arr[i];
        while(j>=0 && key < arr[j])
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void move_queue(int *in, int num)
{
    int i = 0;

    for (i = 1; i < num; i++) {
        in[i - 1] = in[i];
    }
    
}
int find_index(int *in, int num)
{
    int i = 0;

    for (i = 0; i < num - 1; i++) {
        if (in[i + 1] - in[i] > 1) {
            break;
        }
    }
    
    return i;
}
int requeue(int *in, int num)
{
    int index = 0;
    int i = 0;

    if (num == 1) {
        return in[0];
    }

    for (i = 0; i < num - 1;) {
        if (in[i] != in[i + 1]) {
            i++;
            continue;
        }

        index = find_index(&in[i + 1], num - i - 1);
        move_queue(&in[i + 1], index + 1);
        index += i + 1;
        in[index] = in[index - 1] + 1;
    }

    return 0;
}

int main()
{
    int arr[] = {1,3,2,2,2,3,5,7,7,7,9};
    int n = sizeof(arr)/sizeof(int);
    sort(arr, n);
    int i = 0, j = 0, k = 0;
    for(i=0; i< n; i++)
        printf(" %d", arr[i]);
printf("\n=======\n");
    
    requeue(arr, n);
    for(i=0; i< n; i++)
        printf(" %d", arr[i]);
printf("\n=======\n");
    return 0;
}

