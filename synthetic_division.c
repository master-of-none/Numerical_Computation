#include<stdio.h>
#include<complex.h>


void main(){
                
                double poly[6],q[6],px,p_x,a,b;
                int m, r, i,j;
                complex x;
                printf("\t\tSYNTHETIC DIVISION");
                printf("\n Enter the highest degree of the equation (max 5): ");
                scanf("%d",&m);

                for(i=0;i<=m;i++){
                                printf("\n Coefficient x[%d] = ", m-i);
                                scanf("%lf",&poly[i]);
                }

                printf("\n Enter the value of constant in (x-r) : ");
                scanf("%d",&r);
                q[0] = poly[0];
                for(i=1;i<=m;i++){
                                q[i] = (q[i-1]*r)+poly[i];
                }

                printf("\n Coefficients of quotient are: \n");
                for(i=0;i<m;i++){
                                printf("\t%lf",q[i]);
                }
                px=q[m];
                printf("\n Remainder is: %lf", px);

                //q[0] = q[0];
                for(i=1;i<=m;i++){
                                q[i] = (q[i-1]*r)+q[i];
                }

                printf("\n Coefficients of quotient are: \n");
                for(i=0;i<m-1;i++){
                                printf("\t%lf",q[i]);
                }
                p_x=q[m-1];
                printf("\n Remainder is: %lf\n", p_x);

                j=0;

                
                x = 12 + 1 * I;

                complex temp=x;;
                while (j<100)
                {
                    j++;
                    //x = temp;
                    x = x - (px/p_x);
                    
                    //temp = x;
                   

                }
                a = creal(x);
                b = cimag(x);
                printf("%lf + %lf * i \n",a,b);

                for ( i = 0; i <= m; i++)
                {
                    /* code */
                    printf("%lf ", q[i]);
                }
                
}