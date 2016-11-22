#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>

using namespace std;

#define SIZE 100000

int main()
{
    DWORD start, stop; // to hold the time values
    int a[SIZE],i,newn,n,temp;
    n=SIZE;
    srand (time(NULL)); //seed random
    for(i=0;i<SIZE;i++) // fill array with random data
    {
        a[i]=rand()%SIZE+1;
    }
    start=GetTickCount(); // get start time
    while(n!=0)
    {
        newn=0; //Bubble sort 
        for(i=1;i<=n-1;i++)
        {
            if(a[i-1]>a[i]) // see what is bigger, prev or current
            {
                temp=a[i-1]; // put prev in temp
                a[i-1]=a[i]; // put current in prev
                a[i]=temp; // put prev in current
                newn=i; // set newn to i
            }
        }
        n=newn; // set n to newn
    }
    stop=GetTickCount(); // get stop time
    cout<<"Sort Took "<<stop-start<<" Milliseconds\n"; // determine runtime
    system("PAUSE");
    return(0);
}
/*
 procedure bubbleSort( A : list of sortable items ) n = length(A)
 repeat
 newn = 0
 for i = 1 to n-1 inclusive do
 if A[i-1] > A[i] then swap(A[i-1], A[i]) newn = i
 end if end for
 n = newn until n = 0
 end procedure
 */
