#include "FPToolkit.c"
double swidth, sheight;
void newtonPolynomial(double x[], double y[], int points);
double findAreaCubic(double x[], double y[], int cur);
double findAreaQuadratic(double x[], double y[], int cur);

double Z10, Z21, Z32, Z210, Z321, Z3210, Y0, X0, X1, X2;

#define f(x) (Y0 + Z10 * (x - X0) + Z210 * (x - X0) * (x - X1))

#define g(x)                                                                   \
	(Y0 + Z10 * (x - X0) + Z210 * (x - X0) * (x - X1) +                        \
	 Z3210 * (x - X0) * (x - X1) * (x - X2))

int main(int argc, char **argv) {
	FILE *fptr;
	int numpoints, degree;
	double p[2], u, v;
	double x[1000], y[1000];
	int i;
	swidth = 600;
	sheight = 600;
	G_init_graphics(swidth, sheight);
	G_rgb(0, 0, 0);
	G_clear();
	G_rgb(1, 0, 0);
	G_fill_rectangle(0, sheight - 20, swidth, 20);
	G_rgb(1, 1, 1);
	// EITHER input by clicking OR by data
	// BEGIN point input code: do not modify!
	if (argc == 1) {
		numpoints = 0;
		G_wait_click(p);
		u = p[0];
		v = p[1];
		while (v < sheight - 20) {
			G_fill_circle(u, v, 3);
			x[numpoints] = u;
			y[numpoints] = v;
			numpoints++;
			G_wait_click(p);
			u = p[0];
			v = p[1];
		}
	} else {
		fptr = fopen(argv[1], "r");
		if (fptr == NULL) {
			printf("can't open file, %s\n", argv[1]);
			exit(0);
		}
		fscanf(fptr, "%d", &numpoints);
		for (i = 0; i < numpoints; i++) {
			fscanf(fptr, "%lf %lf", &x[i], &y[i]);
			G_fill_circle(x[i], y[i], 3);
			G_fill_rectangle(x[i] - 2.0, y[i] - 2.0, 5.0, 5.0);
		}
	}
	// END point input code

	printf("\n");
	printf("%d\n", numpoints);
	for (i = 0; i < numpoints; i++) {
		printf("%8.2lf  %8.2lf\n", x[i], y[i]);
		G_rgb(1, 0, 1);
		G_fill_circle(x[i], y[i], 4);
	}
	// YOUR CODE GOES HERE
	newtonPolynomial(x, y, numpoints);
	G_wait_key();
}
void newtonPolynomial(double x[], double y[], int points) {
	double z10, z21, z32, z210, z321, z3210;

	double X, Y;
	int cur = 0;
	int coeff;
	/*for (X = x[coeff]; X <= x[coeff + 3]; X += 0.01) {
		coeff = 0;

		z10 = (y[cur + 1] - y[cur]) / (x[cur + 1] - x[cur]);
		z21 = (y[cur + 2] - y[cur + 1]) / (x[cur + 2] - x[cur + 1]);
		z32 = (y[cur + 3] - y[cur + 2]) / (x[cur + 3] - x[cur + 2]);

		z210 = (z21 - z10) / (x[cur + 2] - x[cur]);
		z321 = (z32 - z21) / (x[cur + 3] - x[cur + 1]);

		z3210 = (z321 - z210) / (x[cur + 3] - x[cur]);
		Y = 0.0;
		Y += y[cur] + z10 * (X - x[cur]) +
			z210 * (X - x[cur]) * (X - x[cur + 1]) +
			z3210 * (X - x[cur]) * (X - x[cur + 1]) * (X - x[cur + 2]);

		if (X == x[coeff + 3]) {
			cur += 3;
			coeff += 3;
		}
		G_fill_circle(X, Y, 1);

	*/
	// int num = points % 3;
	// printf("%d\n", num);
	int r, d, n, q, c;
	n = points;

	r = n % 3;
	d = n / 3;
	if (r == 0) {
		c = d - 1;
		q = 1;
	} else if (r == 1) {
		c = d;
		q = 0;
	} else {
		c = d - 1;
		q = 2;
	}

	printf("Cubic : %d, quadratic : %d\n", c, q);
	/////
	// Commenting Quadratic code
	/////
	/*
	  if (points == 3 || points == 5) {
		  G_rgb(0, 0, 1);
		  for (X = 0.0; X < 800; X++) {
			  if (X > x[0]) {
				  if (X > x[points - 1])
					  break;
				  z10 = (y[cur + 1] - y[cur]) / (x[cur + 1] - x[cur]);
				  z21 = (y[cur + 2] - y[cur + 1]) / (x[cur + 2] - x[cur + 1]);

				  // printf("%lf ", z32);
				  // if (y[cur + 3] - y[cur + 2] < 0)
				  // break;

				  z210 = (z21 - z10) / (x[cur + 2] - x[cur]);
				  z321 = (z32 - z21) / (x[cur + 3] - x[cur + 1]);

				  Y = y[cur] + z10 * (X - x[cur]) +
					  z210 * (X - x[cur]) * (X - x[cur + 1]) +
					  G_fill_circle(X, Y, 1);
				  if (X == x[cur + 2]) {
					  printf("Here is Quadratic\n");
					  cur = cur + 2;
					  G_line(x[0], y[0], x[0], 0);
					  G_line(X, Y, X, 0);
				  }
			  }
		  }
	  }
	*/
	//// Comment ends here

	int quadratic = 0;
	double area, totalAreaQuadratic = 0, totalAreaCubic = 0;
	if (points == 3 || points == 5) {
		for (X = 0.0; X < 800; X++) {
			G_rgb(0, 1, 0);
			if (X > x[cur]) {
				if (X > x[points - 1])
					break;
				z10 = (y[cur + 1] - y[cur]) / (x[cur + 1] - x[cur]);
				z21 = (y[cur + 2] - y[cur + 1]) / (x[cur + 2] - x[cur + 1]);

				// printf("%lf ", z32);
				// if (y[cur + 3] - y[cur + 2] < 0)
				// break;

				z210 = (z21 - z10) / (x[cur + 2] - x[cur]);
				z321 = (z32 - z21) / (x[cur + 3] - x[cur + 1]);

				Y = y[cur] + z10 * (X - x[cur]) +
					z210 * (X - x[cur]) * (X - x[cur + 1]);
				// G_fill_circle(X, Y, 1);
				G_point(X, Y);

				if (X == x[cur + 2]) {
					printf("Here is Quadratic\n");
					Z10 = z10;
					Z210 = z210;
					Y0 = y[cur];
					X0 = x[cur];
					X1 = x[cur + 1];
					area = findAreaQuadratic(x, y, cur);
					printf("Area under the Quadratic is : %lf\n", area);
					totalAreaQuadratic += area;
					cur = cur + 2;
					quadratic++;
					G_line(x[0], y[0], x[0], 0);
					G_line(X, Y, X, 0);
					if (quadratic == q)
						break;
				}
			}
		}
	}
	printf("\n\nTotal area Under the Quadratic is : %lf\n", totalAreaQuadratic);

	int cubic = 0;
	totalAreaCubic = 0;
	area = 0;
	for (X = 0.0; X < 800; X++) {
		G_rgb(1, 0, 0);
		if (X > x[0]) {
			if (X > x[points - 1])
				break;
			z10 = (y[cur + 1] - y[cur]) / (x[cur + 1] - x[cur]);
			z21 = (y[cur + 2] - y[cur + 1]) / (x[cur + 2] - x[cur + 1]);
			z32 = (y[cur + 3] - y[cur + 2]) / (x[cur + 3] - x[cur + 2]);

			// printf("%lf ", z32);
			// if (y[cur + 3] - y[cur + 2] < 0)
			// break;

			z210 = (z21 - z10) / (x[cur + 2] - x[cur]);
			z321 = (z32 - z21) / (x[cur + 3] - x[cur + 1]);

			z3210 = (z321 - z210) / (x[cur + 3] - x[cur]);

			Y = y[cur] + z10 * (X - x[cur]) +
				z210 * (X - x[cur]) * (X - x[cur + 1]) +
				z3210 * (X - x[cur]) * (X - x[cur + 1]) * (X - x[cur + 2]);
			// G_fill_circle(X, Y, 1);
			G_point(X, Y);
			if (X == x[cur + 3]) {
				G_line(x[0], y[0], x[0], 0);
				G_line(X, Y, X, 0);
				printf("Here is Cubic\n");
				Z10 = z10;
				Z210 = z210;
				Z3210 = z3210;
				Y0 = y[cur];
				X0 = x[cur];
				X1 = x[cur + 1];
				X2 = x[cur + 2];
				area = findAreaCubic(x, y, cur);
				printf("Area under the Cubic is : %lf\n", area);
				totalAreaCubic += area;
				cur = cur + 3;
				cubic++;
				if (cubic == c)
					break;
			}
		}
	}
	printf("\n\nTotal area Under the Cubic is : %lf\n\n", totalAreaCubic);
	// printf("x[cur] is : %lf\n", x[cur]);

	totalAreaQuadratic = 0;
	area = 0;
	G_rgb(0, 0, 1);
	quadratic = 0;
	for (X = 0.0; X < 800; X++) {
		if (X > x[cur]) {
			if (X > x[points - 1])
				break;
			z10 = (y[cur + 1] - y[cur]) / (x[cur + 1] - x[cur]);
			z21 = (y[cur + 2] - y[cur + 1]) / (x[cur + 2] - x[cur + 1]);

			// printf("%lf ", z32);
			// if (y[cur + 3] - y[cur + 2] < 0)
			// break;

			z210 = (z21 - z10) / (x[cur + 2] - x[cur]);
			z321 = (z32 - z21) / (x[cur + 3] - x[cur + 1]);

			Y = y[cur] + z10 * (X - x[cur]) +
				z210 * (X - x[cur]) * (X - x[cur + 1]);
			// G_fill_circle(X, Y, 1);
			G_point(X, Y);
			if (X == x[cur + 2]) {
				printf("Here is Quadratic\n");
				Z10 = z10;
				Z210 = z210;
				Y0 = y[cur];
				X0 = x[cur];
				X1 = x[cur + 1];
				area = findAreaQuadratic(x, y, cur);
				printf("Area under the Quadratic is : %lf\n", area);
				totalAreaQuadratic += area;
				cur = cur + 2;
				quadratic++;
				G_line(x[cur], y[cur], x[cur], 0);
				G_line(X, Y, X, 0);
				if (quadratic == q)
					break;
			}
		}
	}
	printf(
		"\n\nTotal area Under the Quadratic is : %lf\n\n", totalAreaQuadratic);
}

double findAreaCubic(double x[], double y[], int cur) {
	double lower, upper, integration = 0.0, stepSize, k;
	int i, subInterval = 15;

	lower = x[cur];
	upper = x[cur + 3];
	printf("\n\nLower : %lf\nUpper : %lf\n", lower, upper);
	stepSize = (upper - lower) / subInterval;

	integration = g(lower) + g(upper);
	printf("Initial Integral : %lf\n", integration);
	for (i = 1; i <= subInterval - 1; i++) {
		k = lower + i * stepSize;
		integration = integration + 2 * g(k);
	}
	integration = integration * stepSize / 2;
	// printf("\nRequired value of integration is: %lf\n", integration);
	return integration;
}

double findAreaQuadratic(double x[], double y[], int cur) {
	double lower, upper, integration = 0.0, stepSize, k;
	int i, subInterval = 15;

	lower = x[cur];
	upper = x[cur + 2];
	printf("\n\nLower : %lf\nUpper : %lf\n", lower, upper);
	stepSize = (upper - lower) / subInterval;

	integration = f(lower) + f(upper);
	printf("Initial Integral : %lf\n", integration);
	for (i = 1; i <= subInterval - 1; i++) {
		k = lower + i * stepSize;
		integration = integration + 2 * f(k);
	}
	integration = integration * stepSize / 2;
	// printf("\nRequired value of integration is: %lf\n", integration);
	return integration;
}
