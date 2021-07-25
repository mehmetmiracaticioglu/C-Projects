//mehmet mirac aticioglu
//linked list sure olcme eksik
// dosyadaki tum degerler okunur ve array ve linked liste atilir
//asal olanlar outputlara yazdilirlir
//terminal ekranina bastirilmaz
//datalar satır satır karakter olarak okunup atoi ile int cast yapilmistir.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>



#define MAXCHAR 1000000


typedef struct prime
{
	int data;
	struct prime *next;

}prime;

void bastir(prime *head,FILE* fp_3);
int isPrime(int sayi);
void read_data ();

int main()
{
	prime *head=NULL;

	read_data(head);
	


	return 0;
}

void read_data (prime *head){
	//burada degerler tanimi yapilir
	int i=0;
	FILE *fp;
	FILE *fp_2;
	FILE *fp_3;
	prime *iter;




	char *str;
	int *arr;
	struct timeval stop, start,stop2, start2,stop3, start3;


//str ve arr'a yer acilir
	str = (char *)calloc(MAXCHAR,sizeof(char));
	arr = (int *)calloc(MAXCHAR,sizeof(int));
	
	char* filename = "data.txt";
	char* filename2 = "output_prime_dynamic_array.txt";
	char* filename3 = "output_prime_LiknedList.txt";

	iter=(prime *)malloc(sizeof(prime));
	fp_3 = fopen (filename3, "w+");
	fp_2 = fopen (filename2, "w+");
	fp = fopen(filename, "r");

	if (fp == NULL){
	    printf("Could not open file %s",filename);
	    return ;
	}
	//elemanlar okunur ve array ve linked liste atilir
	while (fgets(str, MAXCHAR, fp) != NULL){

		arr[i]=atoi(str);
		if(i==0){
			iter->data = arr[i];
			head = iter;
			iter->next = (prime *)malloc(sizeof(prime));
			iter = iter->next;

		}
		else{
			iter->data = arr[i];
			iter->next = (prime *)malloc(sizeof(prime));
			iter = iter->next;
		}
		i++;

	}
	//yazdililir asal olanlar 

	for (i = 0; arr[i] < MAXCHAR; ++i) {
		if(isPrime (arr[i]) == 1){
			fprintf(fp_2,"%d\n",arr[i]);
			
			
		}	
	}

//asal linkled list bastirlir

	bastir(head,fp_3);


//dinamic sure olcer
	gettimeofday(&start, NULL);

	for (i = 0; arr[i] <500000; ++i){
		if(isPrime (arr[i]) == 1){	
			
		}	
	}

	gettimeofday(&stop, NULL);

	
	fprintf(fp_2,"1-500000 arasi %lu milisaniye sürdü \n",(stop.tv_usec - start.tv_usec));
		

	gettimeofday(&start2, NULL);
	for (i = 0; arr[i] < 750000; ++i) {
		if(isPrime (arr[i]) == 1){			
		}	
	}

	gettimeofday(&stop2, NULL);
	fprintf(fp_2,"1-750000 arasi %lu milisaniye sürdü \n",(stop2.tv_usec - start2.tv_usec));
	
		
	
gettimeofday(&start3, NULL);
	for (i = 0; arr[i] < MAXCHAR; ++i) {
		if(isPrime (arr[i]) == 1){			
		}	
	}
	gettimeofday(&stop3, NULL);

fprintf(fp_2,"1-1000000 arasi %lu milisaniye sürdü \n",(stop3.tv_usec - start3.tv_usec));
	



fclose(fp);
fclose(fp_2);
fclose(fp_3);

free(str);
free(arr);


}



int isPrime(int sayi){
	int i;
	if (sayi==1){	
		return 0;
	}
	else if(sayi==2){
		return 1;
	}
	else if (sayi==3){
		return 1;
	}
	else if (sayi==4){
		return 0;
	}

	else {		
			for (i = 2; i <=sqrt(sayi); ++i){
				if (sayi % i== 0)
		 		return 0;
			}
		}
	
	return 1;	

}
		

void bastir(prime *head,FILE* fp_3){
	prime *current = head;

	while(current->next!=NULL){
		if(isPrime (current->data) == 1){
			fprintf(fp_3,"%d\n",current->data);
			
		}	
		current = current->next;
	}
}
	
