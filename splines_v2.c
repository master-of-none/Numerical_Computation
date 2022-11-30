#include "FPToolkit.c"

int matrixmaker(
	double L[],
	double D[],
	double R[],
	double Q[],
	int n,
	double p[],
	double q[]);
int tri_diagonal_solver(
	double L[],
	double D[],
	double R[],
	double Q[],
	int n,
	double x[]);

int main() {
	int n;
	int swidth, sheight;
	double lowleftx, lowlefty, width, height;
	double p[100], y[100], x[100];
	int point = 0;

	double L[1000], D[1000], R[1000], Q[1000]; // Diagonal, Left, Right,
											   // y-values
	double c[1000];							   // coefficient array

	// entire array is initialized to 0. Only the values we'd want would be set
	// to the point data
	for (int i = 0; i < 1000; i++) {
		L[i] = 0;
		D[i] = 0;
		R[i] = 0;
		Q[i] = 0;
	}

	swidth = 600;
	sheight = 610;
	G_init_graphics(swidth, sheight); // interactive graphics

	// clear the screen in a given color
	G_rgb(255, 255, 255);
	G_clear();

	G_rgb(0, 0, 0); // Black
	lowleftx = 500;
	lowlefty = 0;
	width = 30;
	height = 599;
	G_fill_rectangle(lowleftx, lowlefty, width, height);

	G_rgb(0, 1, 0);
	for (int i = 0; i < 100; i++) {
		G_wait_click(p);
		if (p[0] > 500)
			break;
		x[i] = p[0];
		y[i] = p[1];
		G_fill_circle(x[i], y[i], 2);
		++point;
	}

	int key;

	double yplot;
	double xplot;

	int success = matrixmaker(L, D, R, Q, point, x, y);
	success = tri_diagonal_solver(L, D, R, Q, point, c);

    for(i=0; i <point;i++){
        printf("%lf ", c[i]);
    }
    /*
	for (int i = 0; i < point; i++) {
		for (double j = x[i]; j < x[i + 1]; j += 0.001) {
			yplot = y[i] +
				((y[i + 1] - y[i]) * (j - x[i])) / (x[i + 1] - x[i]) +
				c[i * 2] * (j - x[i]) * (j - x[i + 1]) +
				c[i * 2 + 1] * pow((j - x[i]), 2) * (j - x[i + 1]);
			xplot = j;

			G_rgb(1, 0, 0);
			G_fill_circle(xplot, yplot, 1);
		}
	}
    */
   int cur = 0;
   int corffCur = 0;
   for(xplot=0;xplot<800;xplot++){
    if(xplot > x[0]){
            if (xplot > x[point-1])
                break;
        
        yplot = y[cur] + 
                ((y[cur+1]-y[cur])/(x[cur+1]-x[cur]))*(xplot-x[cur]) + 
                (c[corffCur]*(xplot-x[cur])*(xplot-x[cur+1])) + 
                (c[corffCur+1]*pow(xplot-x[cur],2)*(xplot-x[cur+1]));
                
        G_fill_circle(xplot,yplot,1);
        
        if(xplot = x[cur+1]){
            ++cur;
            corffCur+=2;
        }
        
    }  
   }

	key = G_wait_key();
}

int matrixmaker(
	double L[],
	double D[],
	double R[],
	double Q[],
	int n,
	double p[],
	double q[]) {
	int i;
	double j, k;

	// 0th row:
	L[0] = 0;
	D[0] = p[1] - p[0];
	// n-1th row:
	D[n - 1] = 1;
	R[n - 1] = 2 * (p[n - 1] - p[n - 2]);

	for (i = 1; i < n - 1; i++) {
		L[i] = pow((p[i] - p[i - 1]), 2);
		D[i] = p[i - 1] - p[i + 1];
		R[i] = (p[i] - p[i - 1]) * (p[i + 1] - p[i]);
		Q[i] = (q[i] - q[i - 1]) / (p[i] - p[i - 1]) -
			(q[i + 1] - q[i]) / (p[i + 1] - p[i]);
	}
	return 1;
}

int tri_diagonal_solver(
	double L[],
	double D[],
	double R[],
	double Q[],
	int n,
	double x[]) {
	int i;
	double j, k;

	for (i = 1; i < n; i++) {
		k = R[i - 1] * (L[i] / D[i - 1]);
		j = Q[i - 1] * (L[i] / D[i - 1]);

		D[i] -= k;
		Q[i] -= j;
		L[i] = 0;
	}

	x[n - 1] = Q[n - 1] / D[n - 1];

	for (i = n - 2; i >= 0; i--) {
		x[i] = (Q[i] - (x[i + 1] * R[i])) / D[i];
		printf("%lf\n", x[i]);
	}

	return 1;
}