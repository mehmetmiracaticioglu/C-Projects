#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*fonksiyon prototipleri*/
void menu();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
void horseRacingGame();
void countOccurrence();
void triangleOfSequences();
int digitNumber(int num);
int powal(int sayi,int ust);


int main(int argc, char const *argv[])
{
	menu();	
	return 0;
}
/*menu secimi yapilir*/
void menu(){
	int choice,flag=1;		
	do {	
			printf("1. Horse Racing Game\n2. Occurrence Counter\n3. Triangle of Sequences\n0. Exit\n");			
			choice = getInt(0,3);	
				switch(choice){ 
					case 1: horseRacingGame(); break;
					case 2: countOccurrence(); break;
					case 3: triangleOfSequences(); break;
					case 0: flag=0; break;
					default: flag=0; break;  
				}
			} while(flag);
		}
/*min ve max degerler arasinda userdan sayi alir*/
int getInt(int mini, int maxi){
	int flag=1,choice;
	while(flag){
		printf("Whats your choice ?\n");
		scanf("%d",&choice);
		if (mini<=choice && maxi>=choice)		
			flag=0;
	}
	return choice;		
}
/*random sayi olusturur ve retrunler*/	
int numberGeneratorBetweenRange(int min, int max){
	int random;
	random = min+rand()%((max-min)+1);
	return random;
}
/*EXCELLENT CODE IS HERE 
bu fonksiyon ganyan oyununun 3-5 at arasi 
minik bir kazana kaybeden mucadelesini anlatir*/
void horseRacingGame(){
	int i,NumberOfHorse,HorseNumber,a,Winner=0,horse=21,k,index=0,j=21,second_horse=21,third_horse=21,fourt_horse=21,fift_horse=21;
	srand(time(NULL));
	NumberOfHorse = numberGeneratorBetweenRange(3,5);
	printf("NumberOfHorse : %d\n",NumberOfHorse);
	printf("At seciniz :");
	scanf("%d",&HorseNumber);
	
	printf("Race starting...\n");
	for (;HorseNumber>NumberOfHorse;)
	{
		printf("\nAt seciniz :");
		scanf("%d",&HorseNumber);
	}

	for (i = 0; i < NumberOfHorse; ++i){	
		printf("Horse %d:",i+1);
		a=numberGeneratorBetweenRange(10,20);
		for (k = 0; k<a ; ++k){			
				printf("-");
			}
			index++;
		if (a<j){	
				Winner=index;
				j=a;
			}
		
		printf("\n");
	
/*tum atlarin hizini burada tutuyorum
tutmadiklarim yukarida 21 olarak tanimlandi ve kazanma 
ihtimalleri bulunmamakta
*/
		if (i==0)
		{
			horse=a;
		}
		if (i==1)
		{
			second_horse=a;
		}
		if (i==2)
		{
			third_horse=a;
		}
		if (i==3)
		{
			fourt_horse=a;
		}
		if (i==4)
		{
			fift_horse=a;
		}
	}

/*kazanan atin time i ile sectigimiz atin time ı ayni ise sectigimiz at winnerdir
kazandiiik */

	if (HorseNumber==1&&horse==j)
	{		
		printf("You win Winner is Horse 1\n");
	}
	else if (HorseNumber==2&&second_horse==j)
	{		
		printf("You win Winner is Horse 2\n");
	}
	else if (HorseNumber==3&&third_horse==j)
	{		
		printf("You win Winner is Horse 3\n");
	}
	else if (HorseNumber==4&&fourt_horse==j)
	{		
		printf("You win Winner is Horse 4\n");
	}
	else if (HorseNumber==5&&fift_horse==j)
	{		
		printf("You win Winner is Horse 5\n");
	}

	else
		printf("You lose Winner is Horse %d\n",Winner);

}

/* iki sayi alirim ve kalan isimli
degiskene en basta buyuk sayinin onustu modunu alip 
occurence arttirilir daha sonra sayi egerkaybolmasin diye
buyuksayimiz baska degere gonderilir
*/

void countOccurrence(){

	int bigNumber,searchNumber,i,temp2,occurrence=0,onustu=1,kalan=0,bigNumber2;
	printf("Whats the bigNumber :\n");
	scanf("%d",&bigNumber);
	printf("Whats the searchNumber :\n");
	scanf("%d",&searchNumber);	
	temp2=digitNumber(searchNumber);	
	onustu=powal(10,temp2);
	bigNumber2=bigNumber;

	for (i = 0; bigNumber>0; ++i)
	{	
		kalan=bigNumber%onustu;
		bigNumber/=10;
		if (kalan==searchNumber)
			occurrence++;		

	}
	printf("Big Number :%d\n",bigNumber2);
	printf("Search Number:%d\n",searchNumber);
	printf("Occurrence :%d\n",occurrence);

}

/*math.h library yasak oldugu icin on uzerini burada aliyorum*/
int powal(int sayi,int ust){
	int temp=1,i;
	for (i =0; i < ust; ++i)
	{
		temp*=sayi;
	}
	return	temp;

}

/*basamak degeri bulunur*/

int digitNumber(int num){
	int basamak_sayisi = 0;
    while(num>=1) {
        num /= 10;
        basamak_sayisi++;
    }
    return basamak_sayisi;
}


/*klasik ucgen ile sayi kodu
kucuk esitlikler onemli*/
	
void triangleOfSequences(){
	int n,i,j;
	n=numberGeneratorBetweenRange(2,10);
	for (i = 1; i <=n ; ++i)
	{
		for (j = 1; j<=i; ++j)
		{
			printf("%d ",j*i);
		}
		printf("\n");
	}
}

