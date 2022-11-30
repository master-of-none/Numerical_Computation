#include <stdio.h>
#include <complex.h>
#include<math.h>

void main()
{
    int it,n;
    double a[10],b[10],c[10];
    complex x;

    printf("Enter the degree of the polynomial:");
    scanf("%d",&n);
    printf("Enter the coefficients of the polynomial\n");
    for(int i=0;i<=n;i++)
        scanf("%lf",&a[i]);
    printf("Enter the initial guess in complex form: (x,y): \n");
    double a1,b1;
    scanf("%lf%lf",&a1,&b1);
    x = a1 + b1 * I;
    do{
        it=0;
        c[0]=a[0];
        b[0]=a[0];
        do{
            for(int i=1;i<=n;i++)
                b[i]=a[i]+x*b[i-1];
            for(int i=1;i<n;i++)
                c[i]=b[i]+x*c[i-1];
            x=x-b[n]/c[n-1];
            it++;
        }while(fabs(b[n])>1e-5 && it<100);
        a1 = creal(x);
        b1 = cimag(x);
        printf("The root is: %lf + %lf * i",a1,b1);
        n--;
        for(int i=0;i<=n;i++)
            a[i]=b[i];
            
    } while(n>=1);
}
