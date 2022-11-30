#include "FPToolkit.c"

typedef struct Points {
	double x;
	double y;
} P;
double orient(P a, P b, P c) {
	int v = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (v == 0)
		return 0;			// colinear
	return (v > 0) ? 1 : 2; // clock or counterclock wise
}

void convexHull(P points[], int m) {
	if (m < 3) // at least three points required
		return;
	double n[m];
	for (int i = 0; i < m; i++)
		n[i] = -1;
	int l = 0; // initialize result.
	for (int i = 1; i < m; i++)
		if (points[i].x < points[l].x)
			l = i; // find left most point
	int p = l, q;
	do {
		q = (p + 1) % m;
		for (int i = 0; i < m; i++)
			if (orient(points[p], points[i], points[q]) == 2)
				q = i;
		n[p] = q;
		p = q;
	} while (p != l);

	int pointConvex = 0;
	P drawP[m];
	for (int i = 0; i < m; i++) {
		if (n[i] != -1) {
			// printf("x : %lf, y : %lf", points[i].x, points[i].y);
			// G_line(points[i].x, points[i].y, points[i + 1].x, points[i +
			// 1].y);
			drawP[i].x = points[i].x;

			drawP[i].y = points[i].y;
			pointConvex++;
		}
	}
	int size;
	size = sizeof(drawP) / sizeof(drawP[0]);
	printf("%d ", size);
	int i, j;

	double temp1;
	for (i = 0; i < pointConvex - 1; i++) {
		printf("x : %lf, y : %lf", drawP[i].x, drawP[i].y);
		G_line(drawP[i].x, drawP[i].y, drawP[i + 1].x, drawP[i + 1].y);
	}
	G_line(drawP[0].x, drawP[0].y, drawP[i].x, drawP[i].y);
}

int main() {
	int swidth, sheight;
	int degree;
	double lowleftx, lowlefty, width, height;
	// double p[100], x[100], y[100];
	double X, Y;
	int count = 0;
	// double terms[100];
	// double matrix[M][M+1];

	// can change the degree and take input from User if scanf is added
	// Change the degree as desired, currently at 2

	swidth = 700;
	sheight = 710;
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
	double temp[2];
	P points[100];

	for (int i = 0; i < 100; i++) {
		G_wait_click(temp);
		if (temp[0] > 500)
			break;
		points[i].x = temp[0];
		points[i].y = temp[1];
		G_fill_circle(points[i].x, points[i].y, 2);
		++count;
	}
	// int n;
	// n = sizeof(points) / sizeof(points[0]);
	convexHull(points, count);
	int key;
	key = G_wait_key();
}
