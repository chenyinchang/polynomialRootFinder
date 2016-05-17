//this program calculates the roots of a polynomial\
//user enters the coefficients, and, this program, using Halley's method, calulcate and displays the roots
//it first checks if the equation touches the x-axis before continuing to check for roots.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

//evaluates the polynomial at the value x
double fx_val(double a, double b, double c, double d, double e, double x)
{
    double y = 0;
	y+=a*pow(x, 4.0);
	y+=b*pow(x, 3.0);
	y+=c*pow(x, 2.0);
	y+=d*x;
	y+=e;
    return y;
}

//evaluates the derivative of the polynomial at the value x
double fx_dval(double a, double b, double c, double d, double e, double x)
{
    double y = 0;
	y+=4.0*a*pow(x, 3.0);
	y+=3.0*b*pow(x, 2.0);
	y+=2.0*c*x;
	y+=d;
    return y;
}

//evaluates the double derivative of the polynomial at the value x
double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    double y = 0;
	y+=12.0*a*pow(x, 2.0);
	y+=6.0*b*x;
	y+=2.0*c;
    return y;
}

//computes the absolute value of the value y
double double_abs(double x)
{
    x = fabs(x);
    return x;
}

//finds a root for the polynomial using newton's method with the given starting point.
//xn+1 = xn - (fxn)/(f'xn)
//checks for convergence between x and x(n+1) up to 10,000 times to ensure no infine loop
double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    double xNew = x;
    x=x-1;
    int counter = 0;

    while(fabs(x-xNew) > 0.000001 && counter < 10000){
      double fx = fx_val(a,  b,  c,  d,  e,  xNew);
      double fPrime = fx_dval(a,  b,  c,  d,  e,  xNew);
      double fDoublePrime = fx_ddval(a, b, c, d, e, xNew);
        x=xNew;
        xNew = x-((2 * fx * fPrime) / (2 * pow(fPrime, 2.0) - fx * fDoublePrime));

        counter++;
        }
    if(counter >= 9999){
	//if we've gone through the loop 10000 times, then it is probably not a number, and will return such
      xNew = NAN;
    }
    return xNew;
}

//finds the upper bound on the number of roots in the interval (l,r)
int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
	int vl = 0;
	double bNewL = 4.0*a*l + b;
	double cNewL = 6.0*a*pow(l, 2.0) + 3*b*l+c;
	double dNewL = 4*a*pow(l, 3.0) + 3*b*pow(l, 2.0) + 2*c*l+d;
	double eNewL = a*pow(l, 4.0) + b*pow(l, 3.0) + c*pow(l, 2.0) + d*l + e;
	//check for sign changes of left interval
	if((a >= 0 && bNewL <= 0) || (a <= 0 && bNewL >= 0)){
		vl++;
	}
	if((bNewL >= 0 && cNewL <= 0) || (bNewL <= 0 && cNewL >= 0)){
		vl++;
	}
	if((cNewL >= 0 && dNewL <= 0) || (cNewL <= 0 && dNewL >= 0)){
		vl++;
	}
	if((dNewL >= 0 && e <= 0) || (dNewL <= 0 && eNewL >= 0)){
		vl++;
	}
	int vr = 0;
	double bNewR = 4.0*a*r + b;
	double cNewR = 6.0*a*pow(r, 2.0) + 3*b*r+c;
	double dNewR = 4*a*pow(r, 3.0) + 3*b*pow(r, 2.0) + 2*c*r + d;
	double eNewR = a*pow(r, 4.0) + b*pow(r, 3.0) + c*pow(r, 2.0) + d*r + e;
	//check for sign change of right interval
	if((a >= 0 && bNewR <= 0) || (a <= 0 && bNewR >= 0)){
		vr++;
	}
	if((bNewR >= 0 && cNewR <= 0) || (bNewR <= 0 && cNewR >= 0)){
		vr++;
	}
	if((cNewR >= 0 && dNewR <= 0) || (cNewR <= 0 && dNewR >= 0)){
		vr++;
	}
	if((dNewR >= 0 && eNewR <= 0) || (dNewR <= 0 && eNewR >= 0)){
		vr++;
	}
	//find difference between vl and vr
	int vNew = fabs(vl - vr);
    return vNew;
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	double xNew;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);

	int upperBound = rootbound(a, b, c, d, e, l, r);
	//an upper bound of 0 means no roots
	if(upperBound == 0){
		printf("The polynomial has no roots in the given interval");
	}else{
		//iterates through interval
		for( ; l <= r; l+=0.5){
		       	xNew = newrfind_halley(a, b, c, d, e, l);
			//only prints root if it is a real number
			if(!isnan(xNew)){
			  printf("root: %f\n", xNew);
			}
		}
	}
    fclose(in);

    return 0;
}
