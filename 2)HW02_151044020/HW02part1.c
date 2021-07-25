/*kullanilan kutuphaneler*/
/*151044020 Mehmet Mirac Aticioglu */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*fonksiyon prototipleri*/

int succesful(int student_count);
int unsuccesful(int student_count);
void statictis(int student_count);
void avarage(int student_count);
void all_data(int student_count);
void letter(int a);
void show_message(int student_count);


/* menu olusumu burada yapilir ve ogrencilerle ilgili bilgiler burada hazirlanir*/
int main(int argc, char const *argv[]){
	srand(40);
	int student_count,flag=1;
	int secim;
		printf("Enter Student Count :\t");
		printf("\n");
		scanf("%d",&student_count);

		while (student_count<3||student_count>50){
				printf("Not in range!\n");
				printf("Enter Student Count :\t");	
				printf("\n");
				scanf ("%d",&student_count);				
		}

show_message(student_count);

	while(flag) {
		printf("\n");
		printf("Student Score Calculater Menu for %d Student \n",student_count);
		printf("1) Show most successful student\n2) Show most unsuccessful student\n3)Letter Grade Statistic\n4)Calculate Average\n5) Show All Data.\n\n");
		printf("\t\t Make Selection :\n\n");
		scanf("%d",&secim);
			switch (secim){
				case -1:return 0;
				case 1:succesful(student_count); break;
				case 2:unsuccesful(student_count);break;
				case 3:statictis(student_count); break;
				case 4:avarage(student_count);break;
				case 5:all_data(student_count);break;
				default:printf("False Selection !!!\n\n");break;
			}
}
return 0;
}


/*basarili ogrenci burada tespit edilir */
int succesful(int student_count){
srand(40);
int most_big=0,i,a,index;
if (student_count<3||student_count>50)	
		printf("Not in range!\n");

else {
	for (i = 0; i < student_count; ++i){	
			a=rand()%101;				
		if (most_big<a){
			most_big=a;
			index=i;
		}	
	}
printf("Most Succesfully Student\n");
printf("Index :%d\n",index);		
printf("Score :%d\n",most_big);
letter(most_big);
printf("\n");
	}
	return most_big;
}

/*basarisiz ogrenci burada tespit edilir */

int unsuccesful(int student_count){
srand(40);
int most_small=100,i,a,index;
	if (student_count<3||student_count>50)	
		printf("Not in range!\n");
	else {
		for (i = 0; i < student_count; ++i){	
			a=rand()%101;				
				if (most_small>a){
					most_small=a;
					index=i;
					}			
			}
	printf("Most Unsuccesfully Student\n");		
	printf("Index :%d\n",index);
	printf("Score :%d\n",most_small);
	letter(most_small);
	printf("\n");
	}
	return most_small;
}

/*istatiski bilgiler burada depolanir hangi araliklarda hangi harf notlari olacagi belirlenmistir*/
void statictis(int student_count){
	srand(40);
	int i,a,A=0,B=0,C=0,D=0,F=0;

for (i = 0; i < student_count; ++i){		
	a=rand()%101;
	switch(a/10){
		case 10: A++;break;
		case 9: A++;break;												
		case 8: B++;break;												
		case 7: C++;break;											
		case 6: D++;break;
		default:F++;break;
		}
	}
	printf("%d student got letter grade 'A'\n",A);
	printf("%d student got letter grade 'B'\n",B);
	printf("%d student got letter grade 'C'\n",C);
	printf("%d student got letter grade 'D'\n",D);
	printf("%d student got letter grade 'F'\n",F);
	A=0,B=0,C=0,D=0,F=0;
}


/*ortalama burada hesaplanir toplam ogrenci sayisina toplam puan bolunur*/
void avarage(int student_count){
	srand(40);
	int toplam=0,i,a;
	for (i = 0; i < student_count; ++i){		
		a=rand()%101;
		toplam+=a;	
	}
	printf("The Average of %d student : %.2f\n",student_count,(double)toplam/student_count);
	toplam=0;
}


/*harf notu asagidaki kurala gore belirlenir*/
void letter(int a){
	if (a>=90)           
        printf("Letter Grade : 'A'\n");
    else if (a<90&&a>=80)            
        printf("Letter Grade : 'B'\n");          
    else if (a<80&&a>=70)            
        printf("Letter Grade : 'C'\n");           
    else if (a<70&&a>=60)            
        printf("Letter Grade : 'D'\n");
    else if (a<60)            
        printf("Letter Grade : 'F'\n");
}

/*tum verileri g�rebilecegimiz yer*/
void all_data(int student_count){
	succesful (student_count);
	unsuccesful (student_count);
	statictis (student_count);
	avarage (student_count);	
}

 /*girilen sayida ogrencinin notunu ekrana yazdirir*/
void show_message(int student_count){
	int i,a;
	for (i = 0; i < student_count; ++i){	
				a=rand()%101;
				printf("%d ",a);
			}
}
