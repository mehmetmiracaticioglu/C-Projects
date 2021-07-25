/*###########################################################################*/
/*HW01_Mehmet_Mirac_Aticoglu_151044020.h							 		 */
/*_____________________________________									     */
/*Created on 04.03.2018 15.34 by Mehmet Mirac Aticioglu						 */
/*									    									 */
/*Description  								  								 */
/*________  								   								 */
/*Program that calculates square and circle area by rectangle	 			 */
/*Includes only funtions because of HW's last update						 */
/*									    									 */
/*###########################################################################*/
/*																			 */
/*---------------------------------------------------------------------------*/
/*                               Includes                                    */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#define PI 3.14
/* fonksiyon prototipleri */

double circle_area(double radius);
double calc_hypotenuse(int side1,int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square);

/*main fonksiyonu sonuclari almak icin display_result fonksiyonunu cagirir*/ 
int main(){
	
	int side1,side2;
	double smallest_circle,smallest_square,largest_circle,largest_square;
	
	printf("Enter First Side for rectangle :\n");
	scanf("%d",&side1);
	printf("Enter second Side for rectangle :\n");
	scanf("%d",&side2);	
	smallest_circle = calc_area_of_smallest_circle(side1,side2);
	largest_circle = calc_area_of_largest_circle(side1,side2);
	smallest_square = calc_area_of_smallest_square(side1,side2);
	largest_square = calc_area_of_largest_square(side1,side2);	
	display_results(largest_circle,largest_square,smallest_circle,smallest_square);
	return 0;
}
/* math.h kutuphanesindeki pow fonksiyonu kullanirak 
dairenin alani hesaplanir pi*r*2                    */
double circle_area(double radius){
	double area;
	area=pow(radius,2)*PI;
	return area;
}
/*hipotenus hesaplamasi icin oncelikle kenarlarin kareleri alinir ve toplanir 
daha sonra karekoku alinarak return edilir 							*/
double calc_hypotenuse(int side1,int side2){
	double hypotenuse_circle;
	hypotenuse_circle=pow(side1,2)+pow(side2,2);
	hypotenuse_circle=sqrt(hypotenuse_circle);
	return hypotenuse_circle;		
}

/* kenarlar karsilastirilir cunku kucuk daire icin kucuk kenar gereklidir 
kucuk kenar cap olacak sekilde ele alinir yaricap istenildigi icin 
capimiz ikiye bolunerek yoluna devam eder									.*/
double calc_radius_of_smallest_circle(int side1, int side2){

	double radius_of_smallest_circle;
	radius_of_smallest_circle = calc_hypotenuse(side1,side2);
	radius_of_smallest_circle=radius_of_smallest_circle/2;
	return radius_of_smallest_circle;
}
/* buyuk cemberin capi dikdortgenin hipotenusu olacagindan oncelikle hipotenus hesaplanir 
 */
double calc_radius_of_largest_circle(int side1, int side2){

	double radius_of_largest_circle;
	if (side1<side2)
	{
		radius_of_largest_circle = side1/2;
		return radius_of_largest_circle;
	}
	else{
		radius_of_largest_circle = side2/2;
		return radius_of_largest_circle;
	}	
}

/*dikdortgenin disini kaplayan en kucuk cemberi buluruz bu sekilde */
double calc_area_of_smallest_circle(int side1, int side2){
	
	double smallest_circle_area,diameter_of_smallest_circle;
	diameter_of_smallest_circle = calc_hypotenuse(side1,side2);
	smallest_circle_area = circle_area((double)diameter_of_smallest_circle/2);
	return smallest_circle_area;
}
/*dikdortgenin icindeki en buyuk alanı temsil eder.
kucuk kenari cap olarak kabul eder.*/

double calc_area_of_largest_circle(int side1, int side2){
	double largest_circle_area;
		if (side1<side2)
	{
		largest_circle_area = circle_area((double)side1/2);
		return largest_circle_area;
	}
	else
	{
		largest_circle_area = circle_area((double)side2/2);
		return largest_circle_area;
	}	
}
/*dikdortgeni cevreleyen en kucuk kare olarak ele alindi buyuk kenar calc_are_of_square fonksiyonuna gider*/
double calc_area_of_smallest_square(int side1, int side2){
 
	double smallest_square;
		if (side1<side2)
		{
			smallest_square=calc_area_of_square (side2);
			return smallest_square;
		}
		else{
			smallest_square=calc_area_of_square (side1);
			return smallest_square;
		}
}
/*bir dikdortgen icindeki en buyuk karenin alani olarak kayda alindi
kucuk kenar bulunur ve carpilir */
double calc_area_of_largest_square(int side1, int side2){

	double largest_square;

		if (side1<side2)
		{
			largest_square = calc_area_of_square (side1);
			return largest_square;
		}
		else{
			largest_square = calc_area_of_square (side2);
			return largest_square;
		}
}
/*karenin alani kenarların caprimi ya da kenarin üssü*/
double calc_area_of_square (int side){

	double square_area;
	square_area=pow(side,2);
	return square_area;
}

/*bastirilması gereken sonuclar*/

void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square){
	
	printf("The area of largest circle that fits inside a rectangle:%.2lf \n",largest_circle);
	printf("The area of largest square that fits inside a rectangle:%.2lf \n",largest_square);
	printf("The area of smallest circle surrounds the same rectangle:%.2lf \n",smallest_circle);
	printf("The area of smallest square surrounds the same rectangle:%.2lf \n",smallest_square);
	
	
	
}
 

void display_results(void){
	
	int side1,side2;
	
	printf("what are the rectangle sides :\n");
	scanf("%d%d",&side1,&side2);

	printf("calc_hypotenuse :%lf \n",calc_hypotenuse(side1,side2));
	printf("calc_radius_of_smallest_circle:%lf \n",calc_radius_of_smallest_circle(side1,side2));
	printf("calc_radius_of_largest_circle:%lf \n",calc_radius_of_largest_circle(side1,side2));
	printf("calc_area_of_largest_circle:%.2lf \n",calc_area_of_largest_circle(side1,side2));
	printf("calc_area_of_largest_square:%.2lf \n",calc_area_of_largest_square(side1,side2));
	printf("calc_area_of_smallest_circle:%.2lf \n",calc_area_of_smallest_circle(side1,side2));
	printf("calc_area_of_smallest_square:%.2lf \n",calc_area_of_smallest_square(side1,side2));
	
}
