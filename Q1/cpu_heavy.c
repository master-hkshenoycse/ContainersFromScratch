#include <stdio.h>
#include <time.h>



void fun()
{

    int x=0;
    for(int i=0;i<=100000;i++){
        for(int j=0;j<=500000;j++){
        x=x+1;
        x=x-1;
        x=x*1;
        x/=1;

        }
    }

}
 
// The main program calls fun() and measures time taken by fun()
int main()
{
    // Calculate the time taken by fun()
    clock_t t;
    t = clock();
    fun();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}