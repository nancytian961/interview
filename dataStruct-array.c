#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printarr(int arr[], int size)
{
    int k = 0;
    while(k < size)
    {
        printf(" %d", arr[k++]);
    }
    printf("\n");
}

//bubble sort
void bubblesort(int a[], int n)
{
    printf("before sort:");    printarr(a, n);
    int i = 0;
    int j = 0;
    int temp = 0;
    for(i = 0; i< n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(a[j]>a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1]= temp; 
            }
        }
    }
    printf(" after sort:");    printarr(a, n);
}



//insert sort
void insertsort(int a[], int n)
{
    int i = 0;
    int j = 0;
    int key = 0;
    for(i = 1; i<n; i++)
    {
        key = a[i];
        j = i-1;
        while(j>=0 && key < a[j])
        {
                a[j+1] = a[j];
                j--;
        }
        a[j+1] = key;

    }
}

int partition(int arr[], int l, int h)
{
    int povit = arr[h];
    int i = l-1;
    int j = l;
    int temp = 0;
    for(j=l; j<h;j++)
    {
        if(arr[j]<povit)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i+1];
    arr[i+1] = arr[h];
    arr[h] = temp;

    return i+1;
}

void quicksort(int a[], int l, int h)
{
    int pi = 0;
    pi = partition(a, l, h);
    //printf("arr[%d] = %d\n", pi, a[pi]);
    if(pi-1 > l)
        quicksort(a, l, pi-1);
    if(pi+1 < h)
       quicksort(a, pi+1, h);

}


//count frequence
 void countFreq(int nums[], int numsSize, int fr[])
{
    int start = 0;
    int count = 1;
    int i = 0, j= 0;
    fr[0] = 1;
    for(i=1; i<numsSize;i++)
    {
        if(nums[i] != nums[i-1])
        {
            j = i-1;
            while(j>=start)
                fr[j--] = count;
            start = i;
            count = 1;
            fr[i] = 1;

        }
        if(nums[i] == nums[i-1])
        {
            count++;
            if(i==numsSize-1)
            {
                j=i;
                while(j>=start)
                    fr[j--] = count;
            }
        }
    }
}



void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)       L[i] = arr[l + i];
    for (j = 0; j < n2; j++)       R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {     arr[k] = L[i++];     } 
        else              {     arr[k] = R[j++];     }
        k++;
    }
 
    while (i < n1) {     arr[k++] = L[i++];    }
    while (j < n2) {     arr[k++] = R[j++];    }
}
 
/* l is for left index and r is right index */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

//find num in a[] that appears more than n/2
int majority(int a[], int n)
{
   int major = a[0];
   int count = 1;
   int i = 1;
   while(i<n)
   {
       if(major == a[i])
           count++;
       if(major != a[i] && count != 0)
           count--;
       else if(count == 0)
       {
           major = a[i];
           count = 1;
       }
        i++;
   }
   return major;
}

void selectSort(int* arr, int n)
{
    int i = 0;
    int j = 0, min = 0, index = 0;
    int temp = 0;
    for(i = 0; i<n; i++)
    {
       min = arr[i];
       for(j = j+1; j<n; j++)
       {
           if(min > arr[j])
           {
               min = arr[j];
               index = j;
           }
       }
       if(i != index)
       {
           temp = arr[i];
           arr[i] = arr[index];
           arr[index] = temp;
       }
    }
}
int main(void)
{
    int arr[] = {7,7,7};
    int n = sizeof(arr)/sizeof(int);

    printf("before sort:");    printarr(arr, n);
    //bubblesort(arr, n);
    //insertsort(arr, n);
    //mergeSort(arr, 0, n-1);
    quicksort(arr, 0, n-1);
    //selectSort(arr, n);

    printf(" after sort:");    printarr(arr, n);

    return 0;
}

