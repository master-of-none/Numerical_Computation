#include "FPToolkit.c"
#include<stdbool.h>

#define M 20

int triDiagonalSolver(double m[M][M+1], int n, double x[M])
{
  int i,j,k ;
  double v,sum ;
  int max_row,c ;

  // reduce matrix to upper triangular form 

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
  //////////////////////////////////////////////////////

  // Now do the back substitution 
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

int main()
{
    int swidth,sheight;
    int degree;

    double leftx, lefty, width, height;

    double p[100], x[100], y[100];
    double X,Y;

    int points = 0;
    double terms[100];

    swidth = 600;
    sheight = 610;

    G_init_graphics (swidth,sheight);

    // clear the screen in a given color
    G_rgb (255, 255, 255) ;
    G_clear () ;


    G_rgb (0,0,0) ; // Black
    leftx = 500; 
    lefty = 0; 
    width = 30; 
    height = 599;
  
    G_fill_rectangle (leftx, lefty, width, height);


    G_rgb(0,1,0);
  
    for(int i = 0; i < 100; i++){
        G_wait_click(p);
    
        if (p[0] >500)
            break;
        
        x[i] = p[0] ; y[i] = p[1];
        G_fill_circle(x[i],y[i],2);
    
        ++points;
  }
    G_rgb(1,0,0) ;
    // intializing variables
  
    double matrix[M][M+1];
  
    for (int i = 0; i < M; ++i){
        for (int j = 0; j <= M; ++j){
            matrix[i][j] = 0;
        }
    }
  
    int variables = (points - 1) * 2;
    double coefficients[variables];
    int cur = 1,temp = 0;
    bool flag = true;

    matrix[0][0] = 1;
    matrix[0][1] = -(x[1] - x[0]);
    matrix[0][variables] = 0;

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
    matrix[variables-1][variables-1] = -2 * (x[points-1] - x[points-2]);
    matrix[variables-1][variables] = 0;

    for(int i=0;i<variables-1;i++){
        for(int j=0;j<variables ;j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
  }

    int success = triDiagonalSolver(matrix, variables, coefficients);
    if (success == 0){
        printf("Gaussian failed.\n");
        return 0;
    }

    cur = 0;
    int coeff_cur = 0;
  
    for (X = 0; X < 800; X++){
        if(X > x[0]){
            if (X > x[points-1])
                break;
      
            Y = y[cur] + 
                ((y[cur+1]-y[cur])/(x[cur+1]-x[cur]))*(X-x[cur]) + 
                (coefficients[coeff_cur]*(X-x[cur])*(X-x[cur+1])) + 
                (coefficients[coeff_cur+1]*pow(X-x[cur],2)*(X-x[cur+1]));
      
            G_point(X,Y);
      
            if(X == x[cur+1]){
                ++cur;
                coeff_cur+=2;
            }
        
        }
    }

  int key ;   
  key =  G_wait_key() ; // pause so user can see results

}