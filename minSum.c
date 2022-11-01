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

void resign(int nums[], int n, int index)
{
    int k = index+1;
    int j = 0;
    for(; k<n; k++)
    {
        if(nums[k] - nums[k-1]>=2)
        {
            for(j=index;j<k-1;j++)
            {
                nums[j] = nums[j+1];
                
            }
            nums[k-1] = nums[k-1]+1;
            break;
        }
    }

    //no find diff >= 2
    if(k == n)
    {
        for(k=index;k<n-1;k++)
            nums[k]=nums[k+1];
        nums[n-1] = nums[n-2]+1;
    }
}

int main()
{
    int arr[] = {1,2,2,2,2,3,6,4,3,3,3,6,8,22,22,24};
    int n = sizeof(arr)/sizeof(int);
    sort(arr, n);
    
//method1
    int i = 0, j = 0, k = 0;
    for(i=0; i< n; i++)
        printf(" %d", arr[i]);
    printf("\n");

    int ret = arr[0];
    for(i=1; i< n; i++)
    {
        while(arr[i] == arr[i-1])
        {
            resign(arr, n, i);
        }
        ret += arr[i];
    }
    for(i=0; i< n; i++)
        printf(" %d", arr[i]);
    printf("\n");
    printf("method1 : ret = %d\n", ret);


//method2
    int count = 0;
    ret = arr[0];
    for(i=1;i<n;i++)
    {
        if(arr[i]==arr[i-1])
        {
            count++;
            continue;
        }
        if(arr[i] - arr[i-1] >=2)
        {
            j = arr[i-1]+1;
            while(count && j< arr[i])
            {
                ret += j++;
                count--;
            }
        }
        ret+=arr[i];
    }

    j = arr[i-1]+1;
    while(count)
    {
        ret += j++;
        count--;
    }

    printf("method2 : ret = %d \n", ret);
    return 0;

}

