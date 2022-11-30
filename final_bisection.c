/*

%% Author : Shrikrishna Bhat


The interval bisection method works iff 
the function is continuous and you can 
establish an initial left & right guess, 
such that:
   f(left) and f(right) have different signs
(i.e.: one is positive and the other negative)

COMPILE THIS CODE BY RUNNING:

gcc interval_bisection04_lab.c -lm

The -lm links with the math library

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Function for √2
double f1 (double x)
{
    double y ;
    y = x*x - 2 ;
    return y ;
}

// Function to test sin(x)
double f2 (double x)
{
    double y ;
    y = sin(x) ;
    return y ;
}

//Function for Quadratic equation
double f3 (double x)
{
    //  three roots,
    //  -3 - sqrt(3) = -4.732050,
    //  -3 + sqrt(3) = -1.267949,
    //   6

    double y ;
    y = x*x*x - 30*x - 36 ;
    return y ;
}

int interval_bisection1(double (*f)(double x), double left, double right,double epsilon, int maxreps,double results[2])
{
    
    //declartion of function variables
    double mid = left;
    double f_mid, f_left, f_right;

    //Initialise loop control variable
    int itr = 0;

    //calculate f(left) and f(right)
    f_left = f1(left);
    f_right = f1(right);

    if (f_left * f_right > 0.0)
    {
        /* code */
        printf("Incorrect Interval\n");
        return 0;
    }

    //Begininng of do-while loop
    do
    {
        //Iterate the loop control variable
        ++itr;

        //Calulate Mid Point
        mid = (right + left) / 2;

        //calculate f(x);
        f_mid = f1(mid);

        //Bisection Logic
        if (f_left * f_mid < 0)
        {
            right = mid;
            f_right = f_mid;
        }

        else
        {
            left = mid;
            f_left = f_mid;
        }
        
        //Print Each Interation Value
        printf("Iteration : %d ",itr);
        
        //Assign approximate root and calulate f(x)
        results[0] = mid;
        results[1] = f1(results[0]);

        printf("Approximation Root : %lf ",results[0]);
        printf("f(%lf) %lf \n", results[0], results[1]);

        if(itr >=maxreps)
        {
            return itr; 
        }
        
    } while (fabs(f_mid) > epsilon);
    
    return itr;
    
}

int interval_bisection2(double (*f)(double x), double left, double right,double epsilon, int maxreps,double results[2])
{
    
    //declartion of function variables
    double mid = left;
    double f_mid, f_left, f_right;

    //Initialise loop control variable
    int itr = 0;

    //calculate f(left) and f(right)
    f_left = f2(left);
    f_right = f2(right);

    if (f_left * f_right > 0.0)
    {
        /* code */
        printf("Incorrect Interval\n");
        return 0;
    }

    //Begininng of do-while loop
    do
    {
        //Iterate the loop control variable
        ++itr;

        //Calulate Mid Point
        mid = (right + left) / 2;

        //calculate f(x);
        f_mid = f2(mid);

        //Bisection Logic
        if (f_left * f_mid < 0)
        {
            right = mid;
            f_right = f_mid;
        }

        else
        {
            left = mid;
            f_left = f_mid;
        }
        
        //Print Each Interation Value
        printf("Iteration : %d ",itr);
        
        //Assign approximate root and calulate f(x)
        results[0] = mid;
        results[1] = f2(results[0]);

        printf("Approximation Root : %lf ",results[0]);
        printf("f(%lf) %lf \n", results[0], results[1]);

        if(itr >=maxreps)
        {
            return itr; 
        }
        
    } while (fabs(f_mid) > epsilon);
    
    return itr;
    
}


// f points at a function with one double input and a double output 
int interval_bisection3(double (*f)(double x), double left, double right,double epsilon, int maxreps,double results[2])
{
    
    //declartion of function variables
    double mid = left;
    double f_mid, f_left, f_right;

    //Initialise loop control variable
    int itr = 0;

    //calculate f(left) and f(right)
    f_left = f3(left);
    f_right = f3(right);

    if (f_left * f_right > 0.0)
    {
        /* code */
        printf("Incorrect Interval\n");
        return 0;
    }

    //Begininng of do-while loop
    do
    {
        //Iterate the loop control variable
        ++itr;

        //Calulate Mid Point
        mid = (right + left) / 2;

        //calculate f(x);
        f_mid = f3(mid);

        //Bisection Logic
        if (f_left * f_mid < 0)
        {
            right = mid;
            f_right = f_mid;
        }

        else
        {
            left = mid;
            f_left = f_mid;
        }
        
        //Print Each Interation Value
        printf("Iteration : %d ",itr);
        
        //Assign approximate root and calulate f(x)
        results[0] = mid;
        results[1] = f3(results[0]);

        printf("Approximation Root : %lf ",results[0]);
        printf("f(%lf) %lf \n", results[0], results[1]);

        if(itr >=maxreps)
        {
            return itr; 
        }
        
    } while (fabs(f_mid) > epsilon);
    
    return itr;
    
}

int main()
{
    int maxreps,numr,test_case ;
    double left_guess_f1,right_guess_f1,res[2],left_guess_f2,right_guess_f2;

    printf("Enter Test case 1,2,3 or enter anything else for exit\n");
    scanf("%d",&test_case);
    
    switch (test_case)
    {
    case 1:
            // test #1

            left_guess_f1  = 1 ;
            right_guess_f1 = 2 ;

            maxreps = 10;
            numr = interval_bisection1(f1, left_guess_f1,right_guess_f1,  1e-12, maxreps,  res) ;
    
            if (numr == 0) 
            {
                printf("Failure to find a root.\n") ;
            } 
            else {  
                    printf("------------------------------------------------\n");
                    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
                    printf("------------------------------------------------\n");
                    printf("Final Approximate root : %lf", res[0]);
    
                // res[0] is our approximation to a root.
                // res[1] is the function evaluated at res[0],
                // which should be close to 0 if we came close to finding a root.
    
                // NOTE: numreps equals maxreps, if the algorithm performed maxreps repititions
            }
            break;

    case 2 :
            //test #2 
            maxreps = 50;
            numr = interval_bisection2(sin, 3,4,  1e-12, maxreps,  res) ;
            // for this test the function is the sin(x)
  
            if (numr == 0) 
            {
                printf("Failure to find a root.\n") ;
            } 
            else 
            {
                printf("------------------------------------------------\n");
                printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
                printf("------------------------------------------------\n");
                printf("Final Approximate root : %lf", res[0]);
            }
    
            break;
    
    case 3 :
            //test #3:
  
            printf("Enter left,right for root search : ") ;
            scanf("%lf %lf",&left_guess_f2,&right_guess_f2) ;

            maxreps = 100 ;
            numr = interval_bisection3(f2, left_guess_f2,right_guess_f2,  1e-12, maxreps,  res) ;
  
            if (numr == 0) 
            {
                printf("Failure to find a root.\n") ;
            } 
    
            else 
            {
                printf("------------------------------------------------\n");
                printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
                printf("------------------------------------------------\n");
                printf("Final Approximate root : %lf", res[0]);
            }
            
            break;

    default:
            break;
    }
  
}
