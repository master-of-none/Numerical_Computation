#include  "FPToolkit.c"
// row reduces an n by n+1 matrix 
#define M 20

void print_matrix (double m[M][M+1], int n)
{
   int r,c ;
   for (r = 0 ; r < n ; r++) {
     for (c = 0 ; c <= n ; c++) {
        printf("%.16lf ",m[r][c]) ;
     }
     printf("\n") ;
   }
   printf("\n") ;
}
int gaussian_eliminationOLD(double m[M][M+1], int n, double x[M])
{
   int i,j,k ;
   double v,sum ;
   // reduce matrix to upper triangular form 
   for (j = 0 ; j < n-1 ; j++) {
     //print_matrix(m,n) ;
     if (m[j][j] == 0) return 0 ;
     for (k = j+1 ; k < n ; k++) {
       v = m[k][j] / m[j][j] ;
       for (i = 0 ; i <= n ; i++) {
          m[k][i] = m[k][i] - v*m[j][i] ;
       }
     }
   }
   // Output the upper triangular form
   //print_matrix(m,n) ;
   // Now do the back substitution 
   for (j = n - 1 ; j >= 0 ; j--) {
     sum = 0.0 ;
     for (k = j + 1 ; k < n ; k++) {
        sum += (m[j][k] * x[k]) ;
     }
     if (m[j][j] == 0) return 0 ;
     x[j] = (m[j][n] - sum)/m[j][j] ;
   }
   /*
   for (j = 0 ; j < n ; j++) {
     printf("x[%d] = %.16lf\n",j,x[j]) ;
   }
   printf("\n") ;
   */
   return 1 ;
}
int gaussian_elimination(double m[M][M+1], int n, double x[M])
{
   int i,j,k ;
   double v,sum ;
   int max_row,c ;
   // reduce matrix to upper triangular form 
   for (j = 0 ; j < n-1 ; j++) {
     //print_matrix(m,n) ;
     // search from row j+1 down to find the largest magnitude
     max_row = j ;
     for (k = j+1 ; k < n ; k++) {
       if (fabs(m[k][j]) > fabs(m[max_row][j])) { max_row = k ; }
     }
     if (max_row != j) {
       // swap rows
       for(c = j ; c <= n ; c++) {
 v = m[j][c] ; m[j][c] = m[max_row][c] ; m[max_row][c] = v ;
       }
     }
     if (m[j][j] == 0) return 0 ; 
          // this now means there does not exist a unique soln
          // have to think about this ...
          // consider the subproblem underneath this
          // it has either a unique soln, is inconsistent, or is underdetermined
          // Now we are adding a new equation with 0*new_variable + ...old vars...
          // Since 0 is multiplying the new_variable, we can view this
          // as an extra equation being added to the subproblem which is
          // already full of equations.  
          // case 1: if the subproblem had a unique solution then this solution
          //         either works or not with this added equation.  if it does
          //         not work, then we have an inconsistent system
          //         if it DOES work, then throwing the extra dimension in
          //         creates an UNDERDETERMINED situation as any value of
          //         xnew will still make things work
          // case 2: the subproblem is inconsistent. so no set of values
          //         of xsub can make the sub problem work and that will
          //         still be true, so new system is also inconsistenet
          // case 3: the subproblem is underdetermined.  throwing in the
          //         new equation could create a unique solution in the
          //         subspace but still leaves any choice for xnew so 
          //         the larger system is still underdetermined
     for (k = j+1 ; k < n ; k++) {
       v = m[k][j] / m[j][j] ;
       for (i = 0 ; i <= n ; i++) {
          m[k][i] = m[k][i] - v*m[j][i] ;
       }
     }
   }
   // Output the upper triangular form
   //print_matrix(m,n) ;
   //////////////////////////////////////////////////////
   // Now do the back substitution 
   for (j = n - 1 ; j >= 0 ; j--) {
     sum = 0.0 ;
     for (k = j + 1 ; k < n ; k++) {
        sum += (m[j][k] * x[k]) ;
     }
     if (m[j][j] == 0) return 0 ;
     x[j] = (m[j][n] - sum)/m[j][j] ;
   }
   /*
   for (j = 0 ; j < n ; j++) {
     printf("x[%d] = %.16lf\n",j,x[j]) ;
   }
   printf("\n") ;
   */
   return 1 ;
}
int main()
{
  int swidth, sheight;
  int degree;
  double lowleftx, lowlefty, width, height ;
  double p[100], x[100], y[100];
  double X,Y ;
  int point = 0;
  double terms[100];

  degree = 2;  


  swidth = 600 ;  sheight = 610 ;
  G_init_graphics (swidth,sheight) ;  // interactive graphics

  // clear the screen in a given color
  G_rgb (0.2, 0.2, 0.2) ;
  G_clear () ;


  G_rgb (0.0, 0.0, 1.0) ; // blue
  lowleftx = 500; lowlefty = 0 ; width = 30 ; height = 599 ;
  G_fill_rectangle (lowleftx, lowlefty, width, height) ;


  G_rgb(0,1,0) ;
  for(int i = 0; i < 100; i++){
    G_wait_click(p);
    if (p[0] >500)
      break;
    x[i] = p[0] ; y[i] = p[1];
    G_fill_circle(x[i],y[i],2);
    ++point;
  }
  G_rgb(1,0,0) ;

  double matrix[M][M+1];

  // stores the coefficients 
  double coefficients[degree+1];
  double sum = 0.0;
  for (int i = 0; i <= degree; i++){
    for (int j = 0; j <= degree +1; j++){

      // For the last row, Compute the special sum(x^i*Y)
      if (j == degree + 1){
        for (int k = 0; k < point; k++){
          if (i == 0){
            sum += y[k];
          }
          else
            sum += y[k] * pow(x[k], i);
        }
        matrix[i][j] = sum;
        sum = 0.0;
      }
      else{
        for (int k = 0; k < point; k++){
          sum += pow(x[k], j+i);
        }
        matrix[i][j] = sum;
        sum = 0.0;
      }
    }
  }

  int success = gaussian_elimination(matrix, degree+1, coefficients);
  if (success == 0){
    printf("Gaussian failed.\n");
    return 0;
  }

  // graph the Function using Y = ax^0 + bx^1 + cx^2
  for (X = 0; X < 800; X++){
    Y = 0.0;
    for (int i = 0; i < degree +1; i++){
      // get the Y value for the best fit
      Y += pow(X, i) * coefficients[i];
    }
    G_point(X,Y);
  }
  int key ;   
  key =  G_wait_key() ; // pause so user can see results

  G_save_image_to_file("Best_fit_poly.xwd") ;
}