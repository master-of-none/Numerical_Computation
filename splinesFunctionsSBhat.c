/*

    Program to plot splines using Tri Diagonal System solver

    Authors: Shrikrishna Bhat 
    Colloborated with : Abhishek Das

*/
#include "FPToolkit.c"
#include<stdbool.h>

#define M 20

//Function declarations to create window, call triDiagonalSolver, to form the matrix as required and finally to plot the points.
void windowForm();
int triDiagonalSolver(double m[M][M+1], int n, double x[M]);
void matrixFormation(double matrix[M][M+1],int points,double x[100],double y[100]);
void plotData(double matrix[M][M+1],int points, double *coefficients,double x[100],double y[100]);

int main()
{
    //Initially we initialise the graphic window and we call a function to initalise it
    windowForm();

    //Next we will be collecting the points clicked by user
    double p[100];
    double x[100],y[100];
    int points = 0;
    double matrix[M][M+1];
  
    for(int i = 0; i < 100; i++){
        G_wait_click(p);
    
        if (p[0] >500)
            break;
        
        x[i] = p[0] ; y[i] = p[1];
        G_fill_circle(x[i],y[i],2);
    
        ++points;
  }
    G_rgb(1,0,0) ;
  
    //Make all the elements in the matrix as 0
    for (int i = 0; i < M; ++i){
        for (int j = 0; j <= M; ++j){
            matrix[i][j] = 0;
        }
    }

    // Here we will call the function to create the matrix 
    matrixFormation(matrix,points,x,y);
    
    int key ;   
    key =  G_wait_key() ; // Toc check the results on the screen

}

// Graphic Initalisation window function
void windowForm()
{
    int swidth,sheight;
    int degree;

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
    This is a modified version of Gaussian Solver.
    This function was provided by Dr. Ely, and has been modified such that we will only traverse the diagonal and perform the back substitution.
    One can modify the traditional Gaussian algorithm, such that loop is modified and it will only run throgh 3 diagonals. This will save us a lot of time and reduntant operations are reduced vastly.
    Let us assume that if a loop in i is running through the rows, then we will only check the i-1, i and i+1 columns, and the last column containing the right hand side values.
*/

int triDiagonalSolver(double m[M][M+1], int n, double x[M])
{
  int i,j,k ;
  double v,sum ;

  for (i = 0 ; i < n-1 ; i++) {

    if (m[i][i] == 0) {
        return 0 ;
    }
    for (j = i+1 ; j < n ; j++) {

      v = m[j][i] / m[i][i] ;
      for (k = 0 ; k <= n ; k++) {
        m[j][k] = m[j][k] - v*m[i][k] ;
      }

    }


  }

  // We will do the back substitution.
  for (i = n - 1 ; i >= 0 ; i--) {
    sum = 0.0 ;
    for (j = i + 1 ; j < n ; j++) {
      sum += (m[i][j] * x[j]) ;
    }

    if (m[i][i] == 0){
        return 0 ;
    }

    x[i] = (m[i][n] - sum)/m[i][i] ;
  
  }

  return 1 ;
}

/*
    In this function we will form the required matrix for the calculation and pass it to the triDiagonal solver
*/

void matrixFormation(double matrix[M][M+1],int points,double x[100],double y[100])
{
    
    // Thing to be noted here is : 6 points will yield 5 splines, in total 10 variables and 11 columns
    int variables = (points - 1) * 2;
    double coefficients[variables];
    int cur = 1,temp = 0;
    bool flag = true;

    matrix[0][0] = 1;
    matrix[0][1] = -(x[1] - x[0]);
    matrix[0][variables] = 0;

    /*
        In this function we will be filling the matrix as per the requirement, that is adding values to the 3 diagonal elements.
    */
    for(int i=1; i<variables-1;i++,temp++){
        for(int j=temp;j<variables+1;j++){
            if(flag){
                if (j == temp){
                    matrix[i][j] = x[cur] - x[cur-1];
                }
            
                else if (j == temp + 1){
                    matrix[i][j] = pow(x[cur] - x[cur-1], 2);
                }
        
                else if (j == temp + 2){
                    matrix[i][j] = x[cur+1] - x[cur];
                }
        
                else if (j == variables){
                    matrix[i][j] = ((y[cur+1]-y[cur])/(x[cur+1]-x[cur])) - ((y[cur]-y[cur-1])/(x[cur]-x[cur-1]));
                }
        
                else{
                    continue;
                }    
            }

            else{
                if (j == temp){
                    matrix[i][j] = pow(x[cur] - x[cur-1], 2);
                }
        
                else if (j == temp + 1){
                    matrix[i][j] = -(x[cur + 1] - x[cur -1]);
                }
        
                else if (j == temp + 2){
                    matrix[i][j] = (x[cur] - x[cur -1]) * (x[cur +1] - x[cur]);
                }       
        
                else if (j == variables){
                    matrix[i][j] = -matrix[i-1][j];
                }
                else{ 
                    continue;
                }
            }
        }
        
        if (flag == true)
            flag = false;
    
        else {
            flag = true;
            ++cur;
        }
    }

    matrix[variables-1][variables-2] = 1;
    matrix[variables-1][variables-1] = 2 * (x[points-1] - x[points-2]);
    matrix[variables-1][variables] = 0;

    /*// This is to test whether the matrix formation works or not
    for(int i=0;i<variables-1;i++){
        for(int j=0;j<variables ;j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
  }
*/

    //Here we will call the triDiagonal Solver
    int success = triDiagonalSolver(matrix, variables, coefficients);
    if (success == 0){
        printf("TriDiagonal failed.\n");
        return;
    }

    plotData(matrix,points,coefficients,x,y);


}

// Function to plot the data
void plotData(double matrix[M][M+1],int points, double *coefficients,double x[100],double y[100])
{
    int cur;
    
    cur = 0;
    int corffCur = 0;
    double X,Y;
  
    for (X = 0; X < 800; X++){
        if(X > x[0]){
            if (X > x[points-1])
                break;
      
            Y = y[cur] + 
                ((y[cur+1]-y[cur])/(x[cur+1]-x[cur]))*(X-x[cur]) + 
                (coefficients[corffCur]*(X-x[cur])*(X-x[cur+1])) + 
                (coefficients[corffCur+1]*pow(X-x[cur],2)*(X-x[cur+1]));
      
            G_fill_circle(X,Y,1);
      
            if(X == x[cur+1]){
                ++cur;
                corffCur+=2;
            }
        
        }
    }
}

/*
    Reference for tridiagonal solver is : https://en.wikibooks.org/wiki/Algorithm_Implementation/Linear_Algebra/Tridiagonal_matrix_algorithm
*/