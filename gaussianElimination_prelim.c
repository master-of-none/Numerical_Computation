#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void readArray(int,int degree,float [][degree]);
void printArray(int,int degree, float[][degree]);
void copyMatrix(int,int degree, float[][degree],float[][degree]);
void gaussianElimination(int,int degree, float [][degree],float solution[]);
void partialPivot(int,int degree,float[][degree]);
int main()
{

    int inputDegree, degree=1;
    int equation;
    printf("Enter number of rows\n");
    scanf("%d",&equation);
    printf("Enter the columns\n");
    scanf("%d",&inputDegree);
    degree =inputDegree;

    float matrix[equation][degree]; // main matrix;
    float gaussianMatrix[equation][degree];
    float solution[equation];

    readArray(equation,degree,matrix);
    printArray(equation,degree,matrix);

    copyMatrix(equation,degree,matrix,gaussianMatrix);
    printf("\nCopied Array is \n");
    printArray(equation,degree,gaussianMatrix);

    gaussianElimination(equation,degree,gaussianMatrix,solution);

    printf("\nUpper Triangular Matrix\n");
    printArray(equation,degree,gaussianMatrix);


    for(int i=0;i<equation;i++){
        printf("Solution for Equation %d is %f\n", (i+1),solution[i]);
    }
    printf("\n");

    return 0;
}

void readArray(int equation,int degree, float matrix[equation][degree])
{   
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            //printf("Enter the elememnt in the matrix[%d][%d] ",i,j);
            printf("For equation %d Enter coefficeient for x[%d] ",i+1,(degree-j-1));
            scanf("%f",&matrix[i][j]);
        }
    }

}

void printArray(int equation,int degree, float matrix[equation][degree])
{   
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            printf("%f ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void copyMatrix(int equation,int degree,float matrix[equation][degree],float gaussianMatrix[equation][degree])
{
    for(int i=0;i<equation;i++){
        for(int j=0;j<degree;j++){
            gaussianMatrix[i][j] = matrix[i][j];
        }
    }

}

void gaussianElimination(int equation,int degree,float gaussianMatrix[equation][degree],float solution[equation])
{
    int i,j,k;

    partialPivot(equation,degree,gaussianMatrix);

    for(i=0;i<equation-1;i++){
        for(j=i+1;j<equation;j++){
            float temp = gaussianMatrix[j][i] / gaussianMatrix[i][i];

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

void partialPivot(int equation,int degree,float gaussianMatrix[equation][degree]){

    int i,j,k;
    for(i=0;i<equation-1;i++){
        for(j=i+1;j<equation;j++){

            if(fabsf(gaussianMatrix[i][i] < fabsf(gaussianMatrix[j][i]))){
                for(k=0;k<degree;k++){
                    float temp;
                    temp = gaussianMatrix[i][k];
                    gaussianMatrix[i][k] = gaussianMatrix[j][k];
                    gaussianMatrix[j][k] = temp;
                }
            }
        }
    }
}
