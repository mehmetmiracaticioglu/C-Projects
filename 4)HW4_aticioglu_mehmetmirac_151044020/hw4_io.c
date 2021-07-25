/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/
#include <stdio.h>

#include "hw4_io.h"

/*a0 x^3lu sayinin kuvveti olacak sekilde tasarlandi*/

int read_polynomial3(double * a0, double * a1, double * a2, double * a3){
	scanf("%lf %lf %lf %lf",a0,a1,a2,a3);
	write_polynomial3(*a0,*a1,*a2,*a3);
	return 0;
}

/*a0 x^4lu sayinin kuvveti olacak sekilde tasarlandi*/

int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4){

	scanf("%lf %lf %lf %lf %lf",a0,a1,a2,a3,a4);
	write_polynomial4(*a0,*a1,*a2,*a3,*a4);

return 0;

}

/*sayilari tam sayi mi diye test eder
0 dan buyuk ve kucukluk durumlarina bakar
ona gore katsayı belirleyerek yazar*/
void write_polynomial3(double a0, double a1, double a2, double a3){
	if (a0>0)
	{
		if (a0!=1)
			a0==(int)a0 ? printf("%dx^3",(int)a0) : printf("%.1lfx^3",a0);			
				
		else
			printf("x^3");
	}
else if (a0<0)
	{
		if (a0!=-1)	
			a0==(int)a0 ? printf("%dx^3",(int)a0) : printf("%.1lfx^3",a0);	
			
		else
			printf("x^3");
	}


	if (a1>0)
	{
		if (a1!=1)
			a1==(int)a1 ? printf("+%dx^2",(int)a1) : printf("+%.1lfx^2",a1);		
		
		else
			printf("+x^2");
	}
else if (a1<0)
	{
		if (a1!=-1)
			a1==(int)a1 ? printf("%dx^2",(int)a1) : printf("%.1lfx^2",a1);
				
		else
			printf("-x^2");
	}


if (a2>0)
	{
		if (a2!=1)
		a2==(int)a2 ? printf("+%dx",(int)a2) : printf("+%.1lfx",a2);		
					
		else
			printf("+x");
	}
else if (a2<0)
	{
		if (a2!=-1)
			a2==(int)a2 ? printf("%dx",(int)a2) : printf("%.1lfx",a2);							
		else
			printf("-x");
	}	


if (a3>0)			
		a3==(int)a3 ? printf("+%d",(int)a3) : printf("+%.1lf",a3);					
else if (a3<0)	
		a3==(int)a3 ? printf("%d",(int)a3) : printf("%.1lf",a3);
		printf("\n");	



}

/*sayilari tam sayi mi diye test eder
0 dan buyuk ve kucukluk durumlarina bakar
ona gore katsayı belirleyerek yazar
tekrar eden islemler icin polynomial3 cagirilir*/

void write_polynomial4(double a0, double a1, double a2, double a3, double a4){
	if (a0>0)
	{
		if (a0!=1)
			a0==(int)a0 ? printf("%dx^4",(int)a0) : printf("%.1lfx^4",a0);			
		else
			printf("x^4");
	}
	else if (a0<0)
	{
		if (a0!=-1)
			a0==(int)a0 ? printf("%dx^4",(int)a0) : printf("%.1lfx^4",a0);			
		else
			printf("-x^4");
	}
	if (a1>0)
	{
		printf("+");
	}

	write_polynomial3(a1,a2,a3,a4);
}