#include <stdio.h>
/*mehmet mirac aticioglu 
151044020*/

/*hatalarim:

1) encrpt yaptiktan sonra encript icin girilen deger 
elde tutulmadıgi ve parametre olarak gnderilmedigi icin
decpryt de yeniden sayi istiyorum bunu  yaparkem
iki sayinin butunleyeninin uyguladim
(a+b=26 ==> b=26-a) */


/*prototipler*/
void decrypt_secret_msg();
void encrypt_open_msg();
void encrypt(char* a,int l,int inp);
int len(char * a);
void menu();
void reverse(char * input,int input_len);
int sayi(int sayi1);


/* uzunluk bulma fonksiyonu
son metindeki son bitis dizisindeki
ascii kodu 10 oldugu icin boyle yapıldı
*/
int len(char * a){
  int i=0;
  while(a[i] != '\0')
    i++;
  if(i == 0){
      return 0;
  }
  if(a[i-1] != 10)
    i++;
  return i-1;
}


/*sifreleme algoritması*/
void encrypt(char* a,int l,int inp){
  int i,j=0;
  for(i=0;i<l;i++){
    if(a[i]<= 'z' && a[i] >= 'a'){
      while(j<inp){
        if(a[i] == 'a'){
          a[i] = 'z';
          j++;
        }
        else{
          a[i] -=1;
          j++;
        }

      }
    }
    else if(a[i]<= 'Z' && a[i] >= 'A'){
      while(j<inp){
        if(a[i] == 'A'){
          a[i] = 'Z';
          j++;
        }
        else{
          a[i] -=1;
          j++;
        }

      }
    }
    else if(a[i] == ' ')
      a[i] = '_';
    else if(a[i] == '_')
      a[i] = ' ';  
    j=0;
    /*eger . karakterini goruruse * karakterine cevirir */
    if(a[i] == '.')
    	a[i] = '*';
    /*eger * karakterini gorurse . karakterine cevirir*/
    else if (a[i] == '*')
    	a[i] = '.';
    	
    
  }
}
/*menu*/
void menu(){
	int choice,flag=1;
	/*do while ile ilk kez alindiktan sonra if ile deger araligi kontrol edilmiştir*/		 	
	do {
		printf("1. Encrypt\n2. Decryptn\n0. Exit\n");
		printf("Choice: :\n"); scanf("%d",&choice);
		if (choice>0 || choice<3){
				switch(choice){
				case 0 : flag =0; break ;
				case 1: encrypt_open_msg();break ;
				case 2 : decrypt_secret_msg();break;					
			}
		}
		else{
			printf("1. Encrypt\n2. Decryptn\n0. Exit\n");
			printf("Choice: :\n"); scanf("%d",&choice);			
		}
	}while(flag);
}

/*tersten yazdırma*/
void reverse(char * input,int input_len){

    char tmp [input_len];
  /*uzunluk kadar bir string olustururulur
  ve elemanlar sira ile yazdirilir*/
  int i,j=input_len-1;
  for(i=0;j>=0;j--,i++)
      tmp[i]=input[j];
  for(j=0,i=0;i<input_len;i++)
  	/*13 sayisi carriage retun bu yuzden secreta yazarken bos satir birakiyıordu*/
    if(tmp[i] != 13){
      input[j] = tmp[i];
      j++;
    }
}

/*encrypt metinini okuma*/
void encrypt_open_msg(){
  FILE * fp,*f=fopen("secret_msg.txt","w"); char line [1024]; int input;
  fp = fopen("open_msg.txt","r");
  printf("Key: ");
  scanf("%d",&input);
  /*fgets ile satirlar alinir 
  len ile boyu bulunur
  dosya encpyt fonskiyonuna gonderilir ve 
  girilen key kadar geriye doner
  dosya kapatilir*/
  if(fp){
      while(fgets(line,1024,fp)){
        if(len(line) == 0)
          break;
        reverse(line,len(line));
        encrypt(line,len(line)+1,input);
        printf("%s",line);

        fprintf(f,"%s",line);
        
      }
      printf("\n");
      fclose(fp);
      fclose(f);
  }
  else
    printf("Cannot open file\n");

}

/*encpty ile aynı tek fark ilk okunan dosya secret_msgdir onu decpyrt etmek icin
 kullacidan encrty edilen sayiyi yeniden girmesi beklebir .*/
void decrypt_secret_msg(){
FILE * fp,*f=fopen("open_msg.txt","w"); char line [1024]; int input;
  fp = fopen("secret_msg.txt","r");
  printf("Key: ");
  scanf("%d",&input);
  if(fp){
      while(fgets(line,1024,fp)){
        if(len(line) == 0)
          break;
        reverse(line,len(line));
        encrypt(line,len(line),26-input);
        printf("%s",line);
        fprintf(f,"%s",line);
      }
      printf("\n");
      fclose(fp);
      fclose(f);
  }
  else
    printf("Cannot open file\n");
	return;
}

/*main menuyu aktif bir sekilde kullanir 
ve biter
return degeri 0*/
int main(){
  menu();
  return 0;
 
}