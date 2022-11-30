#include <stdio.h>
#include <math.h>
#define TRUE 1

double inputPolynomial (double coeff[], double n, double x){
double fx = 0.0, temp;
int i;


for (i = n; i >= 0; i--){
temp = coeff[i];
if (i == 0)
fx = fx + temp;
else
fx = fx + (pow(x, i) * temp);
}
return fx;
}


double getDerivative (double coeff[], double n, double x, double vfx){
double dfx = 0, temp;
int i;
for (i = n; i >= 0; i--){
temp = coeff[i];
if (i == 1){
dfx = dfx + temp;
return dfx;
}
else
dfx = dfx + (pow(x, i-1) * temp * i);
}
}

void newtonRaphson (){
int n, i;
double coeff[100], temp, x, fx, dfx, h;
printf("Enter the highest degree of the polynomial: ");


scanf("%d", &n);
for (i = n; i >= 0; i--){
printf("Enter the coefficient of %d degree: ", i);
scanf("%lf", &coeff[i]);
}
printf("Enter the initial assumed value of x: ");
scanf("%lf", &x);
while(TRUE){
fx = inputPolynomial(coeff, n, x);
dfx = getDerivative(coeff, n, x, fx);
h = fx / dfx;
if (fabs(h) < 0.00001)
break;
x = x - h;
}
printf("\nThe value of the root is %lf\n", x);
}

int main (){
newtonRaphson();
return 0;
}
