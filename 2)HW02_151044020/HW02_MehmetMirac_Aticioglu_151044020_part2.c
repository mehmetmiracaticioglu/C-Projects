#include <stdio.h>

/* sayi 0dan buyuk oldugu surece 
modu alýnýr gerekli islemler yapilip 10a bolunur */

int main(int argc, char const *argv[]){
	int number,i=0,digit;
	printf("Enter the number :\n");
	scanf("%d",&number);
	if (number<23 || number>98760)	
		printf("Lutfen Aralikta bir deger giriniz !!!!\n");
	else{
		while(number>0){
		digit = number%10;
		i++;
		if(i == 1)
			printf("the first digit is : %d \n",digit);
		else if(i == 2)
			printf("the second digit is : %d \n",digit);
		else if(i == 3)
			printf("the third digit is : %d \n",digit);
		else if(i == 4)
			printf("the forth digit is : %d \n",digit);
		else if(i == 5)
			printf("the fifth digit is : %d \n",digit);
		number/=10;
	}
	}
return 0;
}


