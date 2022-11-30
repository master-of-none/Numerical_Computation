#include<stdio.h>
#include<math.h>
#include<complex.h>

double allerr;
double curr[100];
double prev[100];

double synthdiv(double guess, int size, double c[])
{
    
    double px;
    double ppx;
    double rem;
     
    double cprime[size];
    double cprimeprime[size-1];

    cprime[0] = c[0];

    for(int i=1; i<size+1; i++)
    {
       cprime[i] = guess * cprime[i-1] + c[i];
    }

    px = cprime[size];

    cprimeprime[0] = cprime[0];

    for(int i=1; i<size; i++)
    {
      cprimeprime[i] = guess * cprimeprime[i-1] + cprime[i];
    }
    
    ppx = cprimeprime[size-1];
    if(ppx==0)
      printf("Math Error\n");

    rem = px/ppx;

    return rem;
}

void rootarray(double root, int size, double c[], double rarray[])
{
  rarray[0] = c[0];
  for(int i=1;i<size;i++)
  {
     rarray[i] = root * rarray[i-1] + c[i];
  }
}

double rootfinder(int maxitr, double c[], int degree, double x0)
{
   double x1, h;
   int j;
   for (j=1; j<maxitr+1; j++)
    {
        h=synthdiv(x0, degree, c);
        if(h==0)
        {
        }
    	x1=x0-h;
        printf(" At Iteration no. %3d, x = %9.16f\n", j, x1);
        if (fabs(h) < allerr)
        {
            printf("After %3d iterations, root = %8.16f\n", j, x1);
            break;
        }
        x0=x1;
    }
  if(j<maxitr+1)
    return x1;
  else{
    printf("Error ! Max iterations reached\n");
    return 0;
  }
}

void main()
{
    int itr, mi;
    int degree;
    double guess;
    
    allerr = 1e-12;

    mi = 15;
    guess = 2;


    printf("\nEnter degree of polynomial:\n");
    scanf("%d", &degree);

    double coefficients[degree+1];

    for(int j=0; j<degree+1; j++)
    {
           itr = degree-j;
	   printf("\nEnter coefficient at exponenent %d:", itr);
	   scanf("%lf", &coefficients[j]);
    }
   
   double roots[degree];
   
   guess = rootfinder(mi, coefficients, degree, guess);

   while(guess == 0){
    printf("Error Found, Try another root \n");
     scanf("%lf", &guess);
     guess = rootfinder(mi, coefficients, degree, guess);
   }
   rootarray(guess, degree, coefficients, curr);

   roots[0] = guess;

   for(int j=0;j<degree;j++)
    {
        prev[j] = curr[j];
    } 

   for(int j=1; j<degree; j++)
   {
        guess = rootfinder(mi, curr, degree-j, guess);
      while(guess == 0){
        
        printf("Max iterations reached. Try another Root\n");
        scanf("%lf", &guess);
        guess = rootfinder(mi, curr, degree-j, guess);
     }

      rootarray(guess, degree-j, prev, curr);
      for(int k=0;k<degree-j+1;k++)
	   prev[k] = curr[k];  
      roots[j] = guess;
      
   }


   for(int j=0;j<degree;j++)
   {
        printf("Root %d:%20.16lf\n", j, roots[j]);
   }
}
