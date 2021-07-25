#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*prototipler*/

void printSolution(char operations[], int arr[],size_t arr_len);
char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current);

int main(int argc, char const *argv[])
{	



    int arr[]={25, 12, 6, 10, 32, 8,1,1},i;
    size_t arr_len;
    arr_len = sizeof(arr) / sizeof(int);

    /*malloc ile  array uzunlugu kadar yer aldim.*/
    char *operations = (char*)malloc(sizeof(char)*arr_len);
    
    /*operayon burada bos bir dizi olarak atanmasi yapiliyor */
    for (i = 0; i < arr_len-1; ++i)
    {
    	operations[i]=' ';
    }

	printf("\n");
    printf("Yapilan islemler :");

    /*operations a find operationstan return eden karakterler yazilir .*/
    strcpy(operations,find_operations(arr,44,operations,arr_len,0,0));
    for (i = 0; i <arr_len-1 ; ++i)
    {
    	    printf("%c",operations[i]);

    }
  
    /*karakterlerin isleme dokulmesi */
    printf("\n\nSonuc  :");
    if (operations[0]!=' ')
    {
    	 printSolution(operations,arr,arr_len);
    }
    else
    	printf("%s\n",operations);

    printf("\n");

    /* hafiza free edilir*/
    free(operations);
    return 0;
}

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current){
    int i,tmp_current;
    char *tmp;
    char *a;

    /*islemleri kontrol etmek icin bir karakterlik alan ayrilir
    ve oraya her hanngi bir karakter atanir ben 'a' atadim  */

    a=(char*)malloc(sizeof(char));
    a[0]='a';

    /* cursorumuz arr_len ile esitse ve beklenen deger anlik degere esitse operations in son elemanina \0 atilir
    ve dongu biter bu bizim bitis durumumuzdur eger bitsezse a ya return eder */

    if (cursor==arr_len){
        if ( current==expected_val){
        	operations[arr_len]='\0';
            return operations;

        }
        else{
         
            return a;
        }


    }

     /*eger imlec ilk elemanda ise currente ilk iki elemanin carpinı atariz ve cursor artırırır
     imlecten bir eksik sayida islem olacağı icin bu durumda sadece carpmalari kontrol ettim */
    if (cursor == 0){

        tmp_current = arr[cursor]*arr[cursor+1];
        cursor++;
    }
    else
        tmp_current=arr[cursor]*current;


    operations[cursor-1]='*';

    tmp = find_operations(arr,expected_val,operations,arr_len,cursor+1,tmp_current);
    if (cursor==1)
        cursor--;

    if (tmp[0]!='a'){

        return tmp;
    }
	/*eger imlec ilk elemanda ise currente ilk iki elemanin carpinı atariz ve cursor artırırır
     imlecten bir eksik sayida islem olacağı icin bu durumda sadece cikarmalari kontrol ettim */
    if (cursor == 0){
        tmp_current = arr[cursor]-arr[cursor+1];
        cursor++;
    }
    else
        tmp_current=current-arr[cursor];


    operations[cursor-1]='-';

    tmp = find_operations(arr,expected_val,operations,arr_len,cursor+1,tmp_current);

    /*eger imlec ilk elemanda ise currente ilk iki elemanin carpinı atariz ve cursor artırırır
    imlecten bir eksik sayida islem olacağı icin bu durumda sadece toplamalari kontrol ettim */


    if (cursor==1)
        cursor--;
    if (tmp[0]!='a'){

        return tmp;
    }
    if (cursor == 0){
        tmp_current = arr[cursor]+arr[cursor+1];
        cursor++;
    }
    else
        tmp_current=arr[cursor]+current;


    operations[cursor-1]='+';

    tmp = find_operations(arr,expected_val,operations,arr_len,cursor+1,tmp_current);
    if (cursor==1)
        cursor--;

    if (tmp[0]!='a'){

        return tmp;
    }

    /*eger islemlerden basarisz kalırsa kac adet bosluk olacagini burada hesapladim */
    for (i = 0; i <arr_len-2 ; ++i)
    {
        tmp[i]=' ';
    }
    if (cursor==0){
    	free(a);
        return tmp;
    }
    	
    return a;



}




void printSolution(char operations[], int arr[],size_t arr_len){

/*sadece print icin yazdigim yardimci fonksiyon*/ 
	
int i = 0;
	
	for (i = 0; i <arr_len-1 ; ++i)
		printf("(");
	printf("%d%c%d)",arr[0],operations[0],arr[1]);

	for (i = 2; i <arr_len ; ++i)
	{
		printf("%c%d)",operations[i-1],arr[i]);
	}

}