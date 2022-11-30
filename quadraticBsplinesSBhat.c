/*
    Quadratic B-splines
    Author : Shrikrishna Bhat
    In this code we will be making quadratic bsplines. 
    Here we will be making bspines using the quadratic functions

    x(t) = a(t)*x0  +  b(t)*x1  +  c(t)*x2  
    y(t) = a(t)*y0  +  b(t)*y1  +  c(t)*y2  
    
    We will only be considering 3 points = Q012

    Q012(t) = a(t)*P0  +  b(t)*P1  +  c(t)*P2 

    By mathematically solving using the same principle as given the notes we get the below equations

    a(t) = (1^2 - 2*t*1 + t*t)/2
    The above equation can be rewritten as a(t) = (1-t)^2 / 2.0

    b(t) = -t*t + t + 1/2

    c(t) = t*t/2

    So finally all the equations to calculate a(t), b(t) and c(t) are:
    a(t) = (1-t)^2 / 2.0
    b(t) = -t*t + t + 1.0/2.0 [ Note here that if the value was taken as 1/2 the code wasnt working anr it was giving integer values]
    c(t) = t*t / 2.0

    By using the above 3 equations we will plot the bsplines as required 
*/

#include "FPToolkit.c"

void createWindow(void);

int main() {
	
    // Here we are creating the graphic window to draw the points
    
    createWindow;

	double p[100], x[100], y[100];
	double X, Y;
	int point = 0;
	//double terms[100];

    // Here we are collecting the user clicked points
	for (int i = 0; i < 100; i++) {
		G_wait_click(p);
		if (p[0] > 500)
			break;
		x[i] = p[0];
		y[i] = p[1];
		G_fill_circle(x[i], y[i], 2);
		++point;
	}
	G_rgb(1, 0, 0);

	/* Pre Final version
	
    for (int i = 0; i < (point - 3) + 1; i += 2) {
		for (double t = 0.0; t <= 1.0; t += 0.001) {
			X = pow(1 - t, 2) * x[i] + 2 * (1 - t) * t * x[i + 1] +
				t * t * x[i + 2];
			// Y = pow(t, 2) / 2.0 * y[i] + (1 / 2 + t - pow(t, 2)) * y[i + 1] +
			// pow((1 - t), 2) / 2.0 * y[i + 2];
			Y = pow(1 - t, 2) * y[i] + 2 * (1 - t) * t * y[i + 1] +
				t * t * y[i + 2];
			G_point(X, Y);
		}
	}
    
    */

    /* 
        Here we wil be drawing the bsplines.
        Since Bsplines we consider here are of 3 points, we will each be considering 3 points iteratively and will form the equations as required
    
    */

	for (int i = 0; i < (point - 3) + 1; i++) {
		for (double t = 0.0; t <= 1.0; t += 0.001) {
			X = pow((1 - t), 2) / 2.0 * x[i] +
				(-t * t + t + 1.0 / 2.0) * x[i + 1] + (t * t) / 2.0 * x[i + 2];
			Y = pow((1 - t), 2) / 2.0 * y[i] +
				(-t * t + t + 1.0 / 2.0) * y[i + 1] + (t * t) / 2.0 * y[i + 2];
			// printf("%lf, %lf \n", X, Y);
			G_point(X, Y);
		}
	}

	int key;
	key = G_wait_key();
}

void createWindow()
{
    int swidth, sheight;
	int degree;
	double lowleftx, lowlefty, width, height;

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

}