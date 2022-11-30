#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>


# define f(x) x * x + 1
int main()
{

 int j=0;
 complex x;
 double a,b;



/*for (j=1; j <=10 ;j++ )
{
    x = x + ( 2 * cpow(x,3) + x * x + x -1) / (6 * x * x + 2 * x +1);

    a = creal(x);
    b = creal(x);

    printf("%d : %20.16lf + %20.16lf * i \n", j, a,b);
}

*/
printf("Enter Real and Imaginary\n");
//scanf("%lf,%lf", &a, &a);
a = 10; b = 5; 

 x = a + b * I;
do
{
    j++;
    //x = x - ( 2 * cpow(x,3) + x * x + x - 1) / (6 * x * x + 2 * x +1);
    
    x = x - (x * x + 1) / (2 * x);

    a = creal(x);
    b = cimag(x);

    printf("%d : %lf + %lf * i \n", j, a,b);
    
} while (j<=15);

return 0;
}

/*
int degree
scanf degree;

double array size 100 to store co efficients


*/  

