/*

    Program to plot splines using Tri Diagonal System solver

    Authors: Shrikrishna Bhat 
    Colloborated with : Abhishek Das

*/

#include "FPToolkit.c"

//Function declarations to create window, call triDiagonalSolver, to form the matrix as required and finally to plot the points.
void windowForm();
int matrixFormation(double *left, double *diagonal, double *right, double *Q, int n, double *p, double *q);
int triDiagonalSolver(double *L,double *D,double *R, double *Q,int n, double *x);
void plotData(double *x, double *y, double *coefficients,int points);

int main() {

	//Initially we will create the graphic window and we call a function to initalise it
	windowForm();

	//Variables to get the points and hold the values in x and y
	double p[100], x[100], y[100];
	int points = 0;
    int key;
	int success;
	// Array to hold left diagonal, main diagonal, right diagonal and RHS values
	double left[100], diagonal[100], right[100], Q[100];

	// Array to hold values after tri diagonal solver									
	double coefficients[100];							   

	//Initially all the diagonals are filled with 0 
	for (int i = 0; i < 100; i++) {
		left[i] = 0;
		diagonal[i] = 0;
		right[i] = 0;
		Q[i] = 0;
	}

	// We will get the points clicked by user
	for (int i = 0; i < 100; i++) {
		G_wait_click(p);
		if (p[0] > 500)
			break;
		x[i] = p[0];
		y[i] = p[1];
		G_fill_circle(x[i], y[i], 2);
		++points;
	}



	// We will call the matrix formation function to create the desired matrix
	success = matrixFormation(left, diagonal, right, Q, points, x, y);
	if (success == 0)
    {
       
        printf("Matrix Formation failed\n");
    }

	// We will call the tridiagonal solver and get the values stored in coefficents matrix
	success = triDiagonalSolver(left, diagonal, right, Q, points, coefficients);
    if (success == 0)
    {
       
        printf("TriDiagonal failed\n");
    }
    

	// Printing the coefficients matrix just to verify the results
    for(int i=0; i <points;i++){
        printf("%lf ", coefficients[i]);
    }
    
	// Function to plot the points
    plotData(x,y,coefficients,points);
    

	key = G_wait_key();

}


// Graphic Initalisation window function
void windowForm()
{
    int swidth,sheight;

    double leftx, lefty, width, height;

    swidth = 600;
    sheight = 610;

    G_init_graphics (swidth,sheight);

    // clear the screen in a given color
    G_rgb(255, 255, 255);
    G_clear();


    G_rgb(0,0,0);
    leftx = 500; 
    lefty = 0; 
    width = 30; 
    height = 599;
  
    G_fill_rectangle(leftx, lefty, width, height);


    G_rgb(0,1,0);
}


/* 
	In this function we have 4 array for left, main and right diaginals respectively
	since we have all the diagonals 0, we will form the required matrix from the equations we know
	We have calculated and added 2 new rows as per the problem requirement
*/

int matrixFormation(double *left, double *diagonal, double *right, double *Q, int n, double *p, double *q) 
{
	int i;
	double j, k;

	// This is the 0th row
	left[0] = 0;
	diagonal[0] = p[1] - p[0];
	
	// This is the n-1th row 
	diagonal[n - 1] = 1;
	right[n - 1] = 2 * (p[n - 1] - p[n - 2]);

	// This is for forming the required equations
	for (i = 1; i < n - 1; i++) {
		left[i] = pow((p[i] - p[i - 1]), 2);
		diagonal[i] = p[i - 1] - p[i + 1];
		right[i] = (p[i] - p[i - 1]) * (p[i + 1] - p[i]);
		Q[i] = (q[i] - q[i - 1]) / (p[i] - p[i - 1]) - (q[i + 1] - q[i]) / (p[i + 1] - p[i]);
	}
	return 1;
}

/*
	In this function we will pass the diagonals we created and solve it and store the values in coefficient array
*/
int triDiagonalSolver(double *left, double *diagonal, double *right, double *Q, int n, double *x) 
{
	int i;
	double j, k;

	//Tridiagonal solver begins here
	for (i = 1; i < n; i++) {
		k = right[i - 1] * (left[i] / diagonal[i - 1]);
		j = Q[i - 1] * (left[i] / diagonal[i - 1]);

		diagonal[i] -= k;
		Q[i] -= j;
		left[i] = 0;
	}

	x[n - 1] = Q[n - 1] / diagonal[n - 1];

	for (i = n - 2; i >= 0; i--) {
		x[i] = (Q[i] - (x[i + 1] * right[i])) / diagonal[i];
		printf("%lf\n", x[i]);
	}

	return 1;
}

/*
	In this function we plot the graph as per the requirement 
*/
void plotData(double *x, double *y, double *coefficients,int points)
{
  double X,Y;
  
for (int i = 0; i < points; i++) {
		for (double j = x[i]; j < x[i + 1]; j += 0.001) {
			Y = y[i] +
				((y[i + 1] - y[i]) * (j - x[i])) / (x[i + 1] - x[i]) +
				coefficients[i * 2] * (j - x[i]) * (j - x[i + 1]) +
				coefficients[i * 2 + 1] * pow((j - x[i]), 2) * (j - x[i + 1]);
			
			X = j;

			G_rgb(1, 0, 0);
			G_fill_circle(X, Y, 1);
		}
	}
}