#include<stdio.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>

double allerr;
complex curr[100];
complex prev[100];


double rp,ip;
complex synthdiv(complex guess, int size, complex c[])
{
    
    complex px;
    complex ppx;
    complex rem;
     
    complex cprime[size];
    complex cprimeprime[size-1];

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
    if(ppx==0){
      printf("Math Error\n");
      return 0;
    }
    rem = px/ppx;

    return rem;
}

void rootarray(complex root, int size, complex c[], complex rarray[])
{
  rarray[0] = c[0];
  for(int i=1;i<size;i++)
  {
     rarray[i] = root * rarray[i-1] + c[i];
  }
}

complex rootfinder(int maxitr, complex c[], int degree, complex x0)
{
   complex x1, h;
   int j;
   for (j=1; j<maxitr+1; j++)
    {
        h=synthdiv(x0, degree, c);
    
    	x1=x0-h;
      rp = creal(x1);
      ip = cimag(x1);
        printf(" At Iteration no. %3d, rp = %9.16f, ip = %9.16f\n", j, rp,ip);
        if (fabs(h) < allerr)
        {
            printf("After %3d iterations, rp = %9.16f, ip = %9.16f\n", j, rp,ip);
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

int main()
{
    int itr, mi;
    int degree;
    complex guess;
    
    allerr = 1e-12;

    mi = 100;
    //guess = 2;

    printf("Enter Real guess\n");
    scanf("%lf",&rp);
    fflush(stdin);
    printf("Enter Complex guess\n");
    scanf("%lf",&ip);
    fflush(stdin);
    
    //scanf("%lf%lf",&rp,&ip);
    guess = rp + ip * I;

    printf("\nEnter degree of polynomial:\n");
    scanf("%d", &degree);
    fflush(stdin);

    complex coefficients[degree+1];

    for(int j=0; j<degree+1; j++)
    {
           itr = degree-j;
	   printf("\nEnter coefficient at exponenent %d:", itr);
	   scanf("%lf", &coefficients[j]);
     fflush(stdin);
    }
   
   complex roots[degree];
   
   guess = rootfinder(mi, coefficients, degree, guess);

   while(guess == 0){
    printf("Error Found try another root \n");

    printf("Enter Real guess\n");
    scanf("%lf",&rp);
    fflush(stdin);
    printf("Enter Complex guess\n");
    scanf("%lf",&ip);
    fflush(stdin);
     
     guess = rp + ip * I;

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
        
         printf("Enter Real guess\n");
      scanf("%lf",&rp);
      fflush(stdin);
     printf("Enter Complex guess\n");
      scanf("%lf",&ip);
      fflush(stdin);
     guess = rp + ip * I;

        fflush(stdin);
        guess = rootfinder(mi, curr, degree-j, guess);
     }

      rootarray(guess, degree-j, prev, curr);
      for(int k=0;k<degree-j+1;k++)
	   prev[k] = curr[k];  
      roots[j] = guess;
      
   }


   for(int j=0;j<degree;j++)
   {
        rp = creal(roots[j]);
        ip = cimag(roots[j]);
        printf("Root %d:%20.16lf + %20.16lf * i\n", j, rp,ip);
   }

  return 0;
}
