#include <stdio.h>
#include <string.h>

int kelimebul(char* kelime);
int main()
{
  kelimebul("Xanthos");
  kelimebul("Patara");
  kelimebul("Myra");
  kelimebul("Arycanda");
  kelimebul("Phaselis");



 
 return 0; 
}

int kelimebul(char* kelime){
  int i=0,j=0,k=0,d; /* i txt'deki satır sayımız, j arraydaki satır sayımız , k arraydaki sutun sayımız , d sondan harf bakarken kullanıyoruz */
  d=strlen(kelime);


   FILE *fp1;
   char Rows[250][100];
   int c;
   fp1 = fopen("input.txt","r");
   do {
     c = fscanf(fp1,"%s",Rows[i]); /* dosyadan bir kelime okuyalim */
    i++;                           /* arttiralim                   */
   } while (c != EOF);             /* ta ki EOF olana kadar        */
   fclose(fp1);

  
   /* bu for döngüleriyle txt dosyasında dolaşıyorum */
    for (j = 0; j < i; j++)							
    {
      for (k = 0; Rows[j][k]!='\0'; k++) /* input txt dosyasındaki dolaşmayı soldan sağa yapıyorum */
      {

        if (Rows[j][k]==kelime[0])  /* input txt dosyasındaki ilk harf kıyası yapıyorum */
        {
          if (Rows[j][k+1]==kelime[1]) /* input txt dosyasındaki ikinci harf kıyası yapıyorum */
          {
          	if (Rows[j][k+2]==kelime[2]) /* input txt dosyasındaki üçüncü harf kıyası yapıyorum */
          	{	
          		if (kelime[d-1]==Rows[j][k+d-1]) /* input txt dosyasındaki sondan birinci harf kıyası yapıyorum */

          		{
          			if (kelime[d-2]==Rows[j][k+d-2]) /* input txt dosyasındaki sondan ikinci harf kıyası yapıyorum */

          			{
          				printf("%s (%d,%d) Horizontal\n",kelime,j+1,k+1);
						return 0; /*bulduğu zaman programı anında sonlandırmak için return ediyoruz */
          			}
          		}

			
			}
		  }			  
        }


	        if (Rows[j][k]==kelime[0])  /* input txt dosyasındaki  birinci harf kıyası yapıyorum */
	        {
	          if (Rows[j+1][k]==kelime[1])  /* input txt dosyasındaki ikinci harf kıyası yapıyorum */
	          {
	          	if (Rows[j+2][k]==kelime[2]) /* input txt dosyasındaki üçüncü harf kıyası yapıyorum */
	          	{	
					if (kelime[d-1]==Rows[j+d-1][k]) /* input txt dosyasındaki sondan birinci harf kıyası yapıyorum */

          			{
	          			if (kelime[d-2]==Rows[j+d-2][k]) /* input txt dosyasındaki sondan ikinci harf kıyası yapıyorum */

	          			{
	          				printf("%s (%d,%d) Vertical\n",kelime,j+1,k+1);

							return 0; /*bulduğu zaman programı anında sonlandırmak için return ediyoruz */
	          			}
          			}
				}
			  }			  
	        }
        

      }
      

    }


printf("%s NOT FOUND !!!\n",kelime);
return 0;
}


