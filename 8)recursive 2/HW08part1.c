#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum{Start,Normal,Pen,Snake,Stairs,Boost,Traps,Finish}b_tip;
typedef struct {
    char text[7];
    int  data,pos_x, pos_y, jump_x, jump_y;
    b_tip tip;
}block;


typedef struct {
    block Current;
    int dice,player,path;
}oyuncu;


void displayGame(block board[10][10]);
void doldur_board(block board[][10]);
oyuncu oyna(block board[][10],oyuncu p1);
int zar_at();
oyuncu Stairs_or_Snake_or_Traps_Boost(block board[][10],oyuncu p);
void oyna_multi(block board[][10]);
oyuncu play_player(block board[][10],oyuncu p);


int main(){
    srand(time(NULL));
    oyuncu p;
    p.path=0;
    block board[10][10];
    int oyunsec;

    doldur_board(board);
    displayGame(board);
    printf("Tek oyuncu ise 1\nmuliplayer ise 2 \n");
    scanf("%d",&oyunsec);

    if (oyunsec==1)
    	oyna(board,p);
    else if (oyunsec==2)
    	oyna_multi(board);
 
    return 0;
}


void doldur_board(block board[][10]){
    int i,j,block_tag=100;

/*board initilazion*/

    for (i = 0; i <10 ; ++i){
        if (i%2==0){
            for (j = 9;  j>=0 ; --j){
                board[i][j].data=block_tag;
                board[i][j].tip=Normal;
                block_tag--;
            }
        }

        else{
            for (j = 0;  j<10 ; ++j){
                board[i][j].data=block_tag;
                board[i][j].tip=Normal;
                block_tag--;
            }

        }
    }

    board[0][2].tip= Traps;
    strcpy(board[0][2].text,"T\0");
    board[0][2].jump_x=1;
    board[0][2].jump_y=2;

    board[2][8].tip= Traps;
    strcpy(board[2][8].text,"T\0");
    board[2][8].jump_x=2;
    board[2][8].jump_y=3;

    board[4][3].tip= Traps;
    strcpy(board[4][3].text,"T\0");
    board[4][3].jump_x=5;
    board[4][3].jump_y=1;

    board[6][9].tip= Traps;
    strcpy(board[6][9].text,"T\0");
    board[6][9].jump_x=6;
    board[6][9].jump_y=5;



    board[0][7].tip= Snake;
    strcpy(board[0][7].text,"S\0");
    board[0][7].jump_x=2;
    board[0][7].jump_y=1;

    board[0][8].tip= Snake;
    strcpy(board[0][8].text,"S\0");
    board[0][8].jump_x=4;
    board[0][8].jump_y=5;

    board[3][7].tip= Snake;
    strcpy(board[3][7].text,"S\0");
    board[3][7].jump_x=4;
    board[3][7].jump_y=1;

    board[2][2].tip= Snake;
    strcpy(board[2][2].text,"S\0");
    board[2][2].jump_x=3;
    board[2][2].jump_y=2;

    board[4][9].tip= Snake;
    strcpy(board[4][9].text,"S\0");
    board[4][9].jump_x=5;
    board[4][9].jump_y=6;

    board[5][5].tip= Snake;
    strcpy(board[5][5].text,"S\0");
    board[5][5].jump_x=7;
    board[5][5].jump_y=8;

    board[7][5].tip= Snake;
    strcpy(board[7][5].text,"S\0");
    board[7][5].jump_x=8;
    board[7][5].jump_y=1;

    board[9][4].tip= Snake;
    strcpy(board[9][4].text,"S\0");
    board[9][4].jump_x=9;
    board[9][4].jump_y=9;



    board[1][1].tip= Stairs;
    strcpy(board[1][1].text,"M\0");
    board[1][1].jump_x=0;
    board[1][1].jump_y=3;

    board[2][5].tip= Stairs;
    strcpy(board[2][5].text,"M\0");
    board[2][5].jump_x=1;
    board[2][5].jump_y=7;

    board[3][1].tip= Stairs;
    strcpy(board[3][1].text,"M\0");
    board[3][1].jump_x=2;
    board[3][1].jump_y=6;

    board[4][6].tip= Stairs;
    strcpy(board[4][6].text,"M\0");
    board[4][6].jump_x=2;
    board[4][6].jump_y=6;

    board[6][1].tip= Stairs;
    strcpy(board[6][1].text,"M\0");
    board[6][1].jump_x=4;
    board[6][1].jump_y=1;

    board[8][6].tip= Stairs;
    strcpy(board[8][6].text,"M\0");
    board[8][6].jump_x=7;
    board[8][6].jump_y=2;

    board[9][3].tip= Stairs;
    strcpy(board[9][3].text,"M\0");
    board[9][3].jump_x=8;
    board[9][3].jump_y=0;



    board[1][5].tip= Pen;
    strcpy(board[1][5].text,"P\0");
    board[1][5].jump_x=1;
    board[1][5].jump_y=5;

    board[5][2].tip= Pen;
    strcpy(board[5][2].text,"P\0");
    board[5][2].jump_x=5;
    board[5][2].jump_y=2;

    board[8][2].tip= Pen;
    strcpy(board[8][2].text,"P\0");
    board[8][2].jump_x=8;
    board[8][2].jump_y=2;


    board[1][8].tip= Boost;
    strcpy(board[1][8].text,"B\0");
    board[1][8].jump_x=1;
    board[1][8].jump_y=3;

    board[3][4].tip= Boost;
    strcpy(board[3][4].text,"B\0");
    board[3][4].jump_x=2;
    board[3][4].jump_y=0;

    board[5][0].tip= Boost;
    strcpy(board[5][0].text,"B\0");
    board[5][0].jump_x=4;
    board[5][0].jump_y=4;

    board[6][5].tip= Boost;
    strcpy(board[6][5].text,"B\0");
    board[6][5].jump_x=5;
    board[6][5].jump_y=9;

    board[7][1].tip= Boost;
    strcpy(board[7][1].text,"B\0");
    board[7][1].jump_x=6;
    board[7][1].jump_y=3;



    board[9][9].tip= Start;
    strcpy(board[9][9].text,"Start\0");

    board[0][9].tip= Finish;
    strcpy(board[0][9].text,"Finish\0");

}

int zar_at(){
    /*1 ile 6 arasi random zar atar*/
    int zar=rand()%6+1;
    return zar ;
}

void displayGame(block board[10][10]){

    /*bu fonskiyon boardi ekrana bastirir*/
    int i=0,j=0;
    while(i<10){

        while(j<10){

            if (board[i][j].tip!=Normal  && board[i][j].tip!=Start && board[i][j].tip!=Finish && board[i][j].tip!= Traps){

                printf("%s{%d} \t",board[i][j].text,board[board[i][j].jump_x][board[i][j].jump_y].data);
            }

            else if (board[i][j].tip == Start || board[i][j].tip == Finish || board[i][j].tip == Traps){
                printf("%s \t",board[i][j].text);
            }
            else
                printf("%d \t",board[i][j].data);
            j++;
        }
        printf("\n\n");
        j=0;
        i++;
    }
}

oyuncu oyna(block board[][10],oyuncu p1){
    /*recursion olarak oyunu oynar */
    int i,j;

    p1.dice = zar_at();
    p1.path+=p1.dice;
    printf("zar number : %d\n",p1.dice);
    printf("path: %d\n",p1.path);
    if(p1.path==100)
        return p1;
    if (p1.path>100){
        printf("buyuk\n");
        p1.path-=p1.dice;
        return  oyna(board,p1);
    }



    for (i = 0; i <10; ++i)
    {
        for (j = 0; j <10 ; ++j)
        {
            if (board[i][j].data==p1.path)
            {
                p1.Current=board[i][j];
                i=10;j=10;
            }
        }
    }

   printf("data: %d\n",p1.Current.data);



    if (p1.Current.tip != Normal && p1.Current.tip != Start && p1.Current.tip != Finish )
    {
        p1=Stairs_or_Snake_or_Traps_Boost(board,p1);
    }

    return oyna(board,p1);


}

void oyna_multi(block board[][10]){
    oyuncu p1,p2;
    int flag =1 ;		

    
    p1.path=0;
    p2.path=0;
    while(flag){
      	p1.dice = zar_at();
      	 printf("\np1 Zar : %d\n\n",p1.dice);
         /*path toplam gittigi yoldur 
         ve baslangicte 0 atanmistir. atilan her zar pathe aktarilir
         eger path 100 ise oyun kazanilir
         degilse devam eder*/
    	p1.path+=p1.dice;
    	if (p1.path==100)
    	{
    		printf("Player 1 WON the game !!! \n");
    		break;
    	}
    	else if (p1.path>100)
    	{
    		p1.path-=p1.dice;
    	}
    	else{
    		printf("p1 ");
    		printf("%d\n",p1.path);
    	
	    	p1=play_player(board,p1);
    	}



	    p2.dice = zar_at();
	    printf("\np2 Zar : %d\n\n",p2.dice);
        /*path toplam gittigi yoldur 
         ve baslangicte 0 atanmistir. atilan her zar pathe aktarilir
         eger path 100 ise oyun kazanilir
         degilse devam eder*/

    	p2.path+=p2.dice;
    	if (p2.path==100){
    		printf("Player 2 WON the game !!! \n");
    		break;
    	}
    	else if (p2.path>100){
    		p2.path-=p2.dice;
    	}
    	else{
    		printf("p2 ");
    		printf("%d\n",p2.path);
     		
   	    	p2=play_player(board,p2);
    	}
			
    }
 





}

oyuncu Stairs_or_Snake_or_Traps_Boost(block board[][10],oyuncu p){
    /*oyuncuya bakilir ve konumu alinir hareket edecegi yere bakilir
     ve eger gidecegi yerde tuzak gibi seyler varsa hamlesi yeniden yonlendirilir*/

    p.Current=board[p.Current.jump_x][p.Current.jump_y];
    p.path=p.Current.data;

    return p;

}

oyuncu play_player(block board[][10],oyuncu p){
	int i,j;

    for (i = 0; i <10; ++i){
    	for (j = 0; j <10 ; ++j){
       		if (board[i][j].data==p.path){
                p.Current=board[i][j];
                i=10;j=10;
       		}
    	}
	}

	   printf("data: %d\n",p.Current.data);



    if (p.Current.tip != Normal && p.Current.tip != Start && p.Current.tip != Finish ){
        p=Stairs_or_Snake_or_Traps_Boost(board,p);
    }
    return p;
}