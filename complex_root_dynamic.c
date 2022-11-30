#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

/*
# define f(x) x * x + 1
int main()
{

 int j=0;
 complex x;
 double a,b;



for (j=1; j <=10 ;j++ )
{
    x = x + ( 2 * cpow(x,3) + x * x + x -1) / (6 * x * x + 2 * x +1);

    a = creal(x);
    b = creal(x);

    printf("%d : %20.16lf + %20.16lf * i \n", j, a,b);
}

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


int degree
scanf degree;

double array size 100 to store co efficients


*/  

int main()
{
    // Find the polynomial

    int degree,i,temp,temp1,degree1;
    int start,end;
    double a,b;
    int j = 1;
    printf("Enter degree of the polynomial\n");
    scanf("%d",&degree);

    
    double c[100],c_d[100];

    /*
    temp = 100-degree-1;


    for ( i = 99; i >= (100-degree-1) ;i--)
    {
        
        printf("Enter Constants\n");
        scanf("%lf",&c[temp++]);    
    }

   for ( i = 99;i >= (100-degree-1) ;i--)
   {
        c_d[i] = c[i-1] * j ;
        j++;
   }
    
    
    for (i = 99; i>=(100-degree-1); i--)
    {
        printf("At Position : %d is c[i] is %lf ",i,c[i]);
    }
    
    printf("\n");
    for (i = 99; i>=(100-degree-1); i--)
    {
        printf("At Position : %d is c_d[i] is %lf ",i,c_d[i]);
    }
   

    complex x;
    complex fx, f_x;
    fx = 0;
    f_x = 0;

     printf("Enter Real and Imaginary\n");
    //scanf("%lf,%lf", &a, &a);
    a = 10; b = 5; 

    x = a + b * I;

    j=0;
    for ( i = 99;i >= (100-degree-1) ;i--)
    {
        //coeff1 = c[i];
        //coeff2 = c_d[i];
        //if(degree == 0)
          //  fx = fx + coeff1;

        //else{
          //  fx = fx + (pow(x,j) * coeff1);
        fx = fx + (pow(x,j) * c[i]);
        f_x = f_x + (pow(x,j) * c_d[i]);
        
        j++;
    }    

    /*
    j=0;
    for ( i = 99;i >= (100-degree-1) ;i--)
    {
        f_x = f_x + (c_d[i] * pow(x,j));
        j++;
    }  
    */
  /*
    j=0;
    do
    {
        j++;
        //x = x - ( 2 * cpow(x,3) + x * x + x - 1) / (6 * x * x + 2 * x +1);
    
        x = x - (fx / f_x);

        a = creal(x);
        b = cimag(x);

        printf("%d : %lf + %lf * i \n", j, a,b);
    
    } while (j<=15);
*/


    for ( i = degree; i >=0; i--)
    {
        printf("Enter constant for co-efficient x^%d\n",i);
        scanf("%lf",&c[i]);
    }
    

    for (i = degree; i>=0; i--)
    {
        printf("At Position : %d is c[i] is %lf ",i,c[i]);
    }

    
 /*
    j = degree - 1;
    for (i = degree; i>=0; i--)
    {
        
        c_d[j] = c[i] * i; 
        j--;
    }
*/

    degree1 = degree;
    j = degree -1 ;
    

    for(i=degree;i>=0;i--)
    {
        c_d[j] = c[i] * i ;
        j--;
    }
     //printf("Degree is %d",degree);2

    printf("\n"); 

    
    for (i = degree1-1; i>=0; i--)
    {
        
        printf("At Position : %d is c_d[i] is %lf ",i,c_d[i]);
    }

    
 complex x, fx, f_x;
    degree = degree1;
     printf("Enter Real and Imaginary\n");
    //scanf("%lf,%lf", &a, &a);
    a = 10; b = 5; 

    x = a + b * I;

    fx = c[0] + 0 * I;
    for(i=1;i<degree;i++)
    {
        
        fx += (c[i] * cpow(x,i));
    }
    
    f_x = c_d[0] + 0 * I;
    for (i = 1; i < degree1; i++)
    {
        
        f_x += (c_d[i] * cpow(x,i));
    }

    //printf("%d%d",degree,degree1);

    
    j=0;
    do
    {
        j++;
        //x = x - ( 2 * cpow(x,3) + x * x + x - 1) / (6 * x * x + 2 * x +1);
    
        x = x - (fx / f_x);

        a = creal(x);
        b = cimag(x);

        printf("%d : %lf + %lf * i \n", j, a,b);
    
    } while (j<=15);

    return 0;
}