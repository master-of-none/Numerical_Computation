#include<stdio.h>
#include<math.h>

// Define f(x). Hardcoding the value and can be changed as and when required
#define f(x) (x * cos(2*x))
double simpsons(double,double,int);

int main(){
    
    double low, high;
    double integration;
    int panels;

    // Entering the values for low,high and panels
    //printf("Enter lower value of the integral\n");
    //change value here
    //scanf("%lf",&low);
    low = -2;

    printf("Enter higher value of the integral\n");
    //change value here
    //scanf("%lf",&high);
    high = 1;

    printf("Enter total panels or 'n' value\n");
    //change value here
    //scanf("%d",&panels);
    panels = 100;

    integration = simpsons(low,high,panels);
    printf("\nFinal Integration value is : %13.10lf \n\n",integration);
}

// Simpsons 1/3 rule calculating Function
double simpsons(double low, double high, int panels)
{
    double steps;
    double temp;
    double integration = 0.0;
    double temp_int;

    steps = (high - low) / panels;

    integration = f(low) + f(high);

    for(int i=1; i<=panels-1; i++){
        temp = low + i * steps;

        if(i%2 == 0){
            integration = integration + 2 * f(temp);
        }

        else{
            integration = integration + 4 * f(temp);
        }
        temp_int = integration * steps / 3;
        printf("Integration at iteration %d is : %13.10lf",i,temp_int);
        printf("\n");
    }
    integration = integration * steps / 3;
    return integration;
}