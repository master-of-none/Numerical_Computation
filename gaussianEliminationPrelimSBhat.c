/*Guassian Elimination With Partial Pivoting*/
/*Authors: Shrikrishna Bhat, Abhishek Das*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void readArray(int,int degree,double [][degree]);
void printArray(int,int degree, double[][degree]);
void copyMatrix(int,int degree, double[][degree],double[][degree]);
void gaussianElimination(int,int degree, double [][degree],double solution[]);
void partialPivot(int,int degree,double[][degree]);

int main()
{

    int inputDegree, degree=1;
    int equation;
    //These form the row and column number of the matrix respectively
    printf("Enter number of rows\n");
    scanf("%d",&equation);
    printf("Enter the columns\n");
    scanf("%d",&inputDegree);
    degree =inputDegree;

    double matrix[equation][degree]; // main matrix;
    double gaussianMatrix[equation][degree];
    double solution[equation];

    readArray(equation,degree,matrix);
    printArray(equation,degree,matrix);

    copyMatrix(equation,degree,matrix,gaussianMatrix);
    printf("\nCopied Array is \n");
    printArray(equation,degree,gaussianMatrix);

    gaussianElimination(equation,degree,gaussianMatrix,solution);

    printf("\nUpper Triangular Matrix\n");
    printArray(equation,degree,gaussianMatrix);


    for(int i=0;i<equation;i++){
        printf("Solution for Equation %d is %lf\n", (i+1),solution[i]);
    }
    printf("\n");

    return 0;
}

/*A function to read in quantities into a 2d matrix in that will go in each slot
quantities are able to be entered equation by equation starting from the left most
or highest degree coefficient*/
void readArray(int equation,int degree, double matrix[equation][degree])
{   
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            //printf("Enter the elememnt in the matrix[%d][%d] ",i,j);
            printf("For equation %d Enter coefficeient for x[%d] ",i+1,(degree-j-1));
            scanf("%lf",&matrix[i][j]);
        }
    }

}
/*Prints out the array. It will look like it would in matrix form*/
void printArray(int equation,int degree, double matrix[equation][degree])
{   
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            printf("%lf ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*Copies one matrix into another*/
void copyMatrix(int equation,int degree,double matrix[equation][degree],double gaussianMatrix[equation][degree])
{
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            gaussianMatrix[i][j] = matrix[i][j];
        }
    }

}
/*Calls the partial pivoting method first to get the matrix into an appropriate form to perform elimination on. Then 
performs back substitution to get our solution array of coefficients*/
void gaussianElimination(int equation,int degree,double gaussianMatrix[equation][degree],double solution[equation])
{
    int i,j,k;

    partialPivot(equation,degree,gaussianMatrix);

    for(i=0;i<equation-1;i++){
        for(j=i+1;j<equation;j++){
            double temp = gaussianMatrix[j][i] / gaussianMatrix[i][i];

            for(k=0;k<degree;k++){
                gaussianMatrix[j][k] = gaussianMatrix[j][k] - temp * gaussianMatrix[i][k];
            }
        }
    }

    //Back Substitution
    for(i=equation-1;i>=0;i--){
        solution[i] = gaussianMatrix[i][degree-1];

        for(j=i+1;j<degree-1;j++){
            solution[i] = solution[i] - gaussianMatrix[i][j] * solution[j];
        }
        solution[i] = solution[i] / gaussianMatrix[i][i];
    }

}

/*Checks if partial pivoting is necessary by comparing absolute values and if lesser, performing the pivot. This has
the side effect of flipping rows when a non zero value is less than the value in the given row index. However,
flipping these rows does not affect the core algorithm*/
void partialPivot(int equation,int degree,double gaussianMatrix[equation][degree]){

    int i,j,k;
    for(i=0;i<equation-1;i++){
        for(j=i+1;j<equation;j++){

            if(fabsf(gaussianMatrix[i][i] < fabsf(gaussianMatrix[j][i]))){
                for(k=0;k<degree;k++){
                    double temp;
                    temp = gaussianMatrix[i][k];
                    gaussianMatrix[i][k] = gaussianMatrix[j][k];
                    gaussianMatrix[j][k] = temp;
                }
            }
        }
    }
}

