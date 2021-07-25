/*Mehmet mirac Aticioglu 
151044020				*/

/*includes*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*structs*/

typedef struct Forest{	
char **Map;
int Width;
int Height;
int Flower_X;
int Flower_Y;

}Forest;

typedef struct Botanist{
int Coord_X;
int Coord_Y; 
int Water_Bottle_Size;

}Botanist;


/*prototip*/
void freeArray(char **a, int m);
void print_map (Forest forest);
void search(Forest *forest,Botanist *botanist);
void init_game (Forest *forest, Botanist *botanist);
int isLegal(int x,int y,Forest forest);


int main(){
    srand(time(NULL));	
	Forest forest;
	Botanist botanist;	
	init_game(&forest,&botanist);
    print_map (forest);   	
   	printf("\n");
   	printf("Searching ...\n\n");
   	search(&forest,&botanist);

   	/*free ettircez*/
   	freeArray(forest.Map,forest.Height);
	return 0;
}


/*burada dosya line by line olarak okunmustur*/
void init_game (Forest *forest, Botanist *botanist){
/*getline ile line line alinmistir .*/
	char * pch;
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i,j;
    fp = fopen("init.csv", "r");
    if (fp == NULL)
        printf("Dosya YOK!\n");

    /*atoi kullanilarak linedaki dosyadaki ilk ve sayi 
    alinip botanistin su haznesine konur
    ikinci sayi ve 3.sayi alinip bboard olusturulur*/
    if (getline(&line, &len, fp) != -1)
    {
    	botanist->Water_Bottle_Size=atoi(line);
    }
    if (getline(&line, &len, fp) != -1)
    {	
  		pch = strtok (line,",\n");		 	
		forest->Height=atoi(pch);		
		pch = strtok (NULL, ",\n");
		forest->Width=atoi(pch);
    } 
    /*burada calloc ile yer acilir*/
    forest->Map=(char **)calloc(forest->Height,sizeof(char *));
	for (i = 0; i <forest->Height; ++i)
	 {
	 	  forest->Map[i]=(char *)calloc(forest->Width,sizeof(char *));  

	 } 


  	i=0;
  	j=0;


  	/* dosya okuma getline kullanimi stackowerfloowdan bakarak editleyerek yazdim */


  	/*strtok kullanirak linelardaki ',' ler ve \n ler kulalnilrak parce edilir.*/
    while ((read = getline(&line, &len, fp)) != -1){
    	pch = strtok (line,",\n");	
	    while (pch != NULL){

	    	forest->Map[i][j]=pch[0];
	    	
	    	if ((forest->Map[i][j]) == 'F' )
	    	{
	    		forest->Flower_X=i;
	    		forest->Flower_Y=j;
	    		
	    	}
	    	if ((forest->Map[i][j])=='B')
	    	{
	    		botanist->Coord_X=i;
	    		botanist->Coord_Y=j;
	    		
	    	}

	    	pch = strtok (NULL,",\n");



	    	j++;

	  }
	
	  	j=0;
	  	i++;
  
    }

    /*dosya kapanir */
    fclose(fp);
    if (line)
        free(line);

    
}
/*print map */
void print_map (Forest forest){
	int i,j;

	for (i = 0; i <forest.Height ; ++i)
	{
		for (j = 0; j <forest.Width ; ++j)
		{
			printf("%c ",forest.Map[i][j]);
		}
		printf("\n");
	}
}
/*recursion fucntion */
void search(Forest *forest,Botanist *botanist){
   
	int direction,tempX,tempY;


/*base case suyun bitmis olma durumu */
   if (botanist->Water_Bottle_Size == 0) {
   		print_map(*forest);
   		printf("Help! I am on (%d,%d)\n",botanist->Coord_X,botanist->Coord_Y); 		
   		return;
   }

   /*cicegi bulma durumu */
   if(forest->Flower_X==botanist->Coord_X && forest->Flower_Y==botanist->Coord_Y){
   		forest->Map[botanist->Coord_X][botanist->Coord_Y] = 'F';
   		print_map(*forest);   		
   		printf("I have found it on (%d,%d)!\n",botanist->Coord_X,botanist->Coord_Y);
   		return;
   }
   /*rastgele bir yon belirlenir */
   direction=rand()%4+1;
 	
 	/*botanistin koordinatları tempx ve tempy ye atanir */	
   tempX = botanist->Coord_X;
   tempY = botanist->Coord_Y;
   /*1) asagi 
   2)yukari
   3) sola 
   4)saga 
   kontrol yapar */
   if(direction == 1){
   		/*Array sinirlari icinde olup olmadigi burada kontrol eder */
   		if(isLegal(tempX+1,tempY,*forest)){
	   		if(forest->Map[tempX+1][tempY] == '#'){
	   			/*agaca den geldi ise tekrardan yon belirlenir */
	   			search(forest,botanist);
	   		}
	   		else{
	   			forest->Map[tempX][tempY] = ' ';
	   			botanist->Coord_X = tempX+1;
	   			forest->Map[botanist->Coord_X][botanist->Coord_Y] = 'B';
	   			botanist->Water_Bottle_Size--;
	   			/*su bir azaltilip yeniden yenilenmis 
	   			koordinatlarla birlikte aramaya devam edilir*/
	   			search(forest,botanist);
	   		}		
   		}
   		else{
   			
   			search(forest,botanist);
   		}
   		
   }

   else if(direction == 2){
   	   	/*Array sinirlari icinde olup olmadigi burada kontrol eder */
		if(isLegal(tempX-1,tempY,*forest)){
	   		if(forest->Map[tempX-1][tempY] == '#'){
	   			/*agaca den geldi ise tekrardan yon belirlenir */
	   			search(forest,botanist);
	   		}
	   		else{
	   			/*eski yerine bos atanip yeni yere dolu atanir */
	   			forest->Map[tempX][tempY] = ' ';
	   			botanist->Coord_X = tempX-1;
	   			forest->Map[botanist->Coord_X][botanist->Coord_Y] = 'B';
	   			botanist->Water_Bottle_Size--;
	   			/*su bir azaltilip yeniden yenilenmis 
	   			koordinatlarla birlikte aramaya devam edilir*/
	   			search(forest,botanist);
	   		}		
   		}
   		else{
   			
   			search(forest,botanist);
   		}
   }

   else if(direction == 3){
   		/*Array sinirlari icinde olup olmadigi burada kontrol eder */
   	   	if(isLegal(tempX,tempY-1,*forest)){
	   		if(forest->Map[tempX][tempY-1] == '#'){
	   			/*agaca den geldi ise tekrardan yon belirlenir */
	   			search(forest,botanist);
	   		}
	   		else{
	   			forest->Map[tempX][tempY] = ' ';
	   			botanist->Coord_Y = tempY-1;
	   			forest->Map[botanist->Coord_X][botanist->Coord_Y] = 'B';
	   			botanist->Water_Bottle_Size--;
	   			/*su bir azaltilip yeniden yenilenmis 
	   			koordinatlarla birlikte aramaya devam edilir*/
	   			search(forest,botanist);
	   		}		
   		}
   		else{
   			
   			search(forest,botanist);
   		}
   }

   else if(direction == 4){
   		/*Array sinirlari icinde olup olmadigi burada kontrol eder */
   	   	if(isLegal(tempX,tempY+1,*forest)){
	   		if(forest->Map[tempX][tempY+1] == '#'){
	   			/*agaca den geldi ise tekrardan yon belirlenir */
	   			search(forest,botanist);
	   		}
	   		else{
	   			forest->Map[tempX][tempY] = ' ';
	   			botanist->Coord_Y = tempY+1;
	   			forest->Map[botanist->Coord_X][botanist->Coord_Y] = 'B';
	   			botanist->Water_Bottle_Size--;
	   			/*su bir azaltilip yeniden yenilenmis 
	   			koordinatlarla birlikte aramaya devam edilir*/
	   			search(forest,botanist);
	   		}		
   		}
   		else{
   		
   			search(forest,botanist);
   		}
   }
}

int isLegal(int x,int y,Forest forest){
	//printf("legalx: %d ,, legaly: %d ,, forestwidth: %d ,, forestheight: %d\n", x,y,forest.Width,forest.Height);
	if(x < 0 || y < 0 || x > forest.Height-1 || y > forest.Width-1){
		return 0;
	}
	else{
		return 1;
	}

}


/*array free edilir.*/
void freeArray(char **a, int m) {
    int i;
    for (i = 0; i < m; ++i) {
        free(a[i]);
    }
    free(a);
}