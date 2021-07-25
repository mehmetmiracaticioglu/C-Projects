/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include "hw4_lib.h"
#include <math.h>
#include <stdio.h>

double swap(double *x, double *y){

    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

double integral(double f(double x), double xs, double xe, double delta){

	if (xs>xe)
	{
		swap(&xs,&xe);
		double sum = 0.0, x;
		for(x=xs; x <= xe; x += delta)
   		sum += f(x)*delta;
    	return -1*sum;
	}
	else{
		double sum = 0.0, x;
		for(x=xs; x <= xe; x += delta)
   		sum += f(x)*delta;
    	return sum;
	}



	

	


}



double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta){


/*riemann toplam integrali cift katli olacak sekilde kullanilmistir*/

		

	double sum = 0.0, x,y;
		
		for (y = ys;  y<=(ye) ; y += delta){
			for(x=xs; x <= (xe); x += delta){
				sum += f(x,y)*delta*delta;
				
					}									 
		}	
		
 	   	return sum;

}


int derivatives(double f(double a), double x, double eps, double * d1, double * d2){

*d1 = (f(x+eps)-f(x-eps))/(2*eps);
*d2 = (f(x+eps)-2*f(x)+f(x-eps))/(eps*eps);

return 0;
}


int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2){

	double a,b;

	derivatives(f,x,eps,&a,&b);

	*e1=fabs(a-d1(x));
	*e2=fabs(b-d2(x));



return 0;
}


int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4){
	

	/*yaklasma teoremi kullanirak yapilmasi planlasmistir lakin sol ve sag uc noktaları verilmedigi icin orta noktasi
	ve diger sekilde ulasmak zor bir hal almistır 
	ayrı bir fonksiyon yardimi ile cozulebilir ama her durumda uygun aralik bulmak icin surekli test yapilmasi gerekmektedir
	uygun algoritmayi kuramadigim icin yapamadim*/

	return 0;
}


