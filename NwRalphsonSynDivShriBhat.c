/*Program 2: Newton Raphson Method applied to find roots using Synthetic division and a complex initial guess as an option. Finds both real and complex roots
Authors: Abhishek Das, ShriKrishna Bhat
*/

#include<stdio.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>

double allerr;
complex curr[100];
complex prev[100];  

//We used global arrays for simplicity of storage of the coefficients produced by each synthetic division
//A link list would have been the better choice with appropriate deallocation and garbage cleanup
//This method definitely leads to stack overflow as there are some very large numbers being placed on the stack repeatedly
//We did clear the buffer which did help a little with the overflow problems but repeated usage still causes stack overflow
//causing false roots to pop up.

double rp,ip;//the real and imaginary coefficients for guesses and roots

/*This method performs the sythetic division twice to get us a x and x' value returning the 
  x/x' value if it passes the x'= 0 flag. If x'= 0 it currently returns 0
  */
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


/*
   This method performs synthetic array with a found root and produces the coefficient array of the original equation divided by x-said root.
   */

//This is generally where stack overflow happens from repeated use as we're allocating to the stack each time we want to push
//values onto the global arrays

void rootarray(complex root, int size, complex c[], complex rarray[])
{
	rarray[0] = c[0];
	for(int i=1;i<size;i++)
	{
		rarray[i] = root * rarray[i-1] + c[i];
	}
}

/*
   This method finds the root using the synthdiv method to produce an h value that gets subtracted from the original guess
   If the difference is negligible i.e. abs(h) is just about equal or less than allowed error (allerr), we've found our root

   If we hit the maximum allowed iterations, an error code is thrown and 0 is returned. code 0 allows for the 
   main function to prompt the user to enter a further guess. This guess can in fact be the last value found on
   convergence in the previous set of iterations
   */
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

/*
The main function interfaces with the user by asking for the real and imaginary coefficients and then the degree of the equation
and finally the coefficients at each respective exponent including 0. Allowed error has been set to 1e-12 but can be changed at will
as can number of iterations in the variable mi.
*/

int main()
{
	int itr, mi;
	int degree;
	complex guess;

	allerr = 1e-12; //if allowed error to be adjusted, adjust here.

	mi = 100; //if number of iterations to be changed, change here.

	printf("Enter Real guess\n");
	scanf("%lf",&rp);
	fflush(stdin);
	printf("Enter Complex guess\n");
	scanf("%lf",&ip);
	fflush(stdin);

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
//After initial values get set into each of the holding arrays, we go into a loop that proceeds to find roots and then divide further to search for more roots
	for(int j=1; j<degree; j++)
	{
		guess = rootfinder(mi, curr, degree-j, guess);
		while(guess == 0){

			printf("Max iterations reached. Try another Root\n");

/*It should be noted: C has limits to which roots can be found. We tested with 15 iterations during our initial forays, and tried 50 then 500 then 5000 even with guesses that were large numbers 
and far from the expected roots. What was observed was that the convergence had limits at a certain point (this is why we started using doubles instead of float but even that had its limits.
The most interesting aspect of this was that once a certain point of convergence was reached at a certain decimal point of data size, convergence stopped and all that happened was a pendulum
like swinging between two data values that were very close in value to each other but not quite in the range of the solution*/

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

