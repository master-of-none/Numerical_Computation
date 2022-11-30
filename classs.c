#include<stdio.h>
int main()
{
    double x1,x2,x3,x4;
    x1 = x2 = x3 = x4 = 0;
    
    printf("Enter initial Guess for all variable\n");
    scanf("%lf %lf %lf %lf",&x1,&x2,&x3,&x4);
    for(int i=1;i<=20;i++)
    {
        x1 = (44 - 5*x2 -7*x3 +2*x4) / 20;
        x2 = (-53 -4*x1 -2*x3-3*x4)/21;
        x3 = (40-2*x1-3*x2-4*x4)/13;
        x4 = (56-3*x1-5*x2+4*x3)/15;

        printf("%2d : %10.16f %10.16f %10.16f %10.16f \n",i,x1,x2,x3,x4 );
    }
    return 0;
}