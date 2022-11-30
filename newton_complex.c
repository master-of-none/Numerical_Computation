/*
   Newton's method can find complex roots provided you
   use complex arithmetic.
   Try it out on 
      (2x + 3) (x - [3-4i]) (x - [3+4i]) 
    = (2x + 3) (x^2 - 6x + 25)
    = 2x^3 - 9x^2 + 32x + 75
   If you are working with a polynomial with real coefficients,
   to find roots that are not on the real axis, the initial guess
   MUST have a non-zero imaginary component, i.e. the initial
   guess cannot be on the real axis.  (Why?)
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
int main()
{
  double rp, ip ; // real and imaginary parts of complex number
  complex x ;
  int i ;
  
  printf("Enter real and imaginary components of complex initial guess\n") ;
  /*printf("Suggestion1 :  6  2\n") ;
  printf("Suggestion2 :  6 -2\n") ;
  printf("Suggestion3 :  6  0\n") ;
  printf("Suggestion4 : -2  1\n") ;    
  printf(" :  ") ;
  */
 
  scanf("%lf  %lf", &rp, &ip) ;
  x = rp + ip * I ;   // I is the imaginary unit
  for (i = 1 ; i <= 15 ; i++) {
    x = x - (2*x*x*x - 9*x*x + 32*x + 75) / (6*x*x - 18*x + 32) ;
    rp  = creal(x) ;
    ip  = cimag(x) ;
    printf("%2d : %20.16lf + %20.16lf I\n",i, rp,ip) ;
  }
}