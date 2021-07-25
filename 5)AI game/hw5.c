/*king modulu eksik ve seri yeme eksik gerisi tam*/


#include <math.h>
#include <stdio.h>

#define ROWS 8
#define COLS 8


typedef enum {empty=0,white_man, black_man, white_king, black_king} piece;
typedef enum {white = 10, black = 20} player;

int check_move_direction(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_player(piece board[][8],int from_x,int from_y,player p);
void init_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
//void sample_game_2();
int check_if_edible(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p);




int main(int argc, char const *argv[])
{
    sample_game_1();
    sample_game_2();



        return 0;
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){

    if (check_player(board,from_x,from_y,p)==0)
        return -1;
    if(check_move_direction(board,from_x,from_y,to_x,to_y,p)==0)
        return -2;
    int n=0;
    if (abs(from_x-to_x > 1  || abs(from_y-to_y) > 1))
        n=check_if_edible(board,from_x,from_y,to_x,to_y,p);
    if (n!=0)
        return n;

    board[to_x][to_y]=board[from_x][from_y];
    board[from_x][from_y]=empty;

    return 1;
}
int check_move_direction(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){
    if(p == black){
        if(to_x-from_x<0)
            return 0;
    }
    if (p==white){
        if(to_x-from_x>0)
            return 0;
    }
    if(from_x-to_x==0){
        if(to_y>7)
            return 0;
        if (to_y<0)
            return 0;
    }
    if (board[to_x][to_y]!=empty)
        return 0;

    return 1;
}

int check_player(piece board[][8],int from_x,int from_y,player p){

    if((board[from_x][from_y]==white_man || board[from_x][from_y]== white_king)  && p== white){
        return 1;
    }
    else if((board[from_x][from_y]==black_man || board[from_x][from_y]== black_king ) && p== black){
        return 1;
    }
    return 0;
}

void display_board(piece board[][8]){
int i,j;
    for (i = 0; i <ROWS ; ++i) {
        for (j = 0; j <COLS ; ++j) {
            switch (board[i][j]) {
                case empty:
                    printf("-");
                    break;
                case white_man:
                    printf("w");
                    break;
                case white_king:
                    printf("W");
                    break;
                case black_man:
                    printf("b");
                    break;
                case black_king:
                    printf("B");
                    break;

            }

        }
        printf("\n");
    }

}

void init_board(piece board[][8]){
	int i,j;
    for (i = 0; i <ROWS ; ++i) {
        for (j = 0; j <COLS ; ++j) {
            if (i==5 || i==6)
                board[i][j]=white_man;

            else if (i==1 || i==2)
                board[i][j]=black_man;

            else
                board[i][j]=empty;

        }
    }




}

int check_end_of_game(piece board[][8]){
    int flag_white=0,flag_black=0,i,j;

    for (i = 0; i <ROWS ; ++i) {
        for (j = 0; j <COLS ; ++j) {
            if (board[i][j]== white_man || board[i][j] == white_king )
                flag_black=1;
            if (board[i][j]== black_man || board[i][j] == black_king )
                flag_white=1;

        }
    }
    if (flag_white==0)
        return white;
    if (flag_black==0)
        return black;


    return -1;

}

void sample_game_1(){

    int a,b,c,d,n;
    piece my_board[ROWS][COLS];


    init_board(my_board);

    display_board(my_board);


    for ( ; check_end_of_game(my_board)==-1 ; ) {

        do {

            printf("white tas ve hareket sec ve oyuncu sec :");
            scanf(" %d %d %d %d", &a, &b, &c, &d);
            n = move(my_board, a, b, c, d, 10);


            printf("n=%d\n",n);
            display_board(my_board);
        }while(n<0);


        do {

            printf("black tas ve hareket sec ve oyuncu sec :");
            scanf(" %d %d %d %d", &a, &b, &c, &d);
            n = move(my_board, a, b, c, d, 20);


            printf("n=%d\n",n);

            display_board(my_board);
        }while(n<0);


    }


    display_board(my_board);

}

void sample_game_2(){
    piece my_board[ROWS][COLS]={
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
            {empty,empty,empty,empty,empty,empty,empty,empty},
    };

}

int check_if_edible(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p){

    int my_x=from_x,my_y=from_y,counter=0,coordinate=0,arr[32],i;

    for (;to_x != my_x || to_y != my_y ;) {
        if (my_y - to_y < 0 && board[my_x][my_y + 2] == empty && board[my_x][my_y + 1] != p &&
            board[my_x][my_y + 1] != empty) {
           board[my_x][my_y]=empty;

            my_y += 2;
            arr[coordinate]=my_x;
            coordinate++;
            arr[coordinate]=my_y-1;
            coordinate++;
            if (p==black)
                board[my_x][my_y]=black_man;
            else
                board[my_x][my_y]=white_man;
            counter++;
        }
        else if (my_y - to_y > 0 && board[my_x][my_y -2 ] == empty && board[my_x][my_y - 1] != p &&
                   board[my_x][my_y - 1] != empty) {
            board[my_x][my_y]=empty;
            my_y -= 2;
            arr[coordinate]=my_x;
            coordinate++;
            arr[coordinate]=my_y+1;
            coordinate++;
            if (p==black)
                board[my_x][my_y]=black_man;
            else
                board[my_x][my_y]=white_man;
            counter++;
        }
        else if (my_x - to_x > 0 && board[my_x-2][my_y] == empty && board[my_x-1][my_y] != p &&
                 board[my_x-1][my_y] != empty) {
            //board[my_x-1][my_y]=empty;
            board[my_x][my_y]=empty;

            my_x -= 2;
            arr[coordinate]=my_x+1;
            coordinate++;
            arr[coordinate]=my_y;
            coordinate++;
            if (p==black)
                board[my_x][my_y]=black_man;
            else
                board[my_x][my_y]=white_man;
            counter++;
        }
        else if (my_x - to_x < 0 && board[my_x+2][my_y] == empty && board[my_x+1][my_y] != p &&
                 board[my_x+1][my_y] != empty) {
            //board[my_x+1][my_y]=empty;
            board[my_x][my_y]=empty;


            my_x += 2;
            arr[coordinate]=my_x-1;
            coordinate++;
            arr[coordinate]=my_y;
            coordinate++;
            if (p==black)
                board[my_x][my_y]=black_man;
            else
                board[my_x][my_y]=white_man;
            counter++;
        } else{
            if (p==black)
                board[from_x][from_y]=black_man;
            else
                board[from_x][from_y]=white_man;
            board[my_x][my_y]=empty;

            return 0;
        }


    }
    for (i = 0; i <coordinate ; i+=2) {
        board[arr[i]][arr[i+1]]=empty;
    }

    if (p==black){
        if (my_x==7)
            board[my_x][my_y]=black_king;
        else
            board[my_x][my_y]=black_man;


    }

    else{
        if(my_x==0)
            board[my_x][my_y]=white_king;
        else
            board[my_x][my_y]=white_man;

    }


    return counter;
}
