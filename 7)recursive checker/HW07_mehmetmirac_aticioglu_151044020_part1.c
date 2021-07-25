/*king modulu eksik */
/*recursion olarak yerken cift yonlı yiyecek tas varsa ilk kullacnıya soruyor hangisi yenemcekse*/
/*geri kalan her sey tamam*/
/*151044020 */

#include <math.h>
#include <stdio.h>

#define ROWS 8
#define COLS 8

typedef enum{false,true}BOOL;
typedef enum {empty=0,white_man, black_man, white_king, black_king} piece;
typedef enum {white = 10, black = 20} player;

int check_move_direction(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_player(piece board[][8],int from_x,int from_y,player p);
void init_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p,BOOL must_eat);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
//void sample_game_2();
int check_if_edible(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p);
int recur_eating(piece board[][8],int from_x,int from_y,player p);
void scan_board(piece board[][8],player p,int edible_arr[]);



int main(int argc, char const *argv[])
{
    sample_game_1();
    // sample_game_2();



    return 0;
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p,BOOL must_eat){
    int n=0;

    if (check_player(board,from_x,from_y,p)==0)
        return -1;
    if(check_move_direction(board,from_x,from_y,to_x,to_y,p)==0)
        return -2;

    if (must_eat==true){
        if (abs(from_x-to_x)==2 || abs(from_y-to_y)== 2)
        {
            piece p_type=white_man;
            if (p==black){
                p_type=black_man;
            }


            if (check_if_edible(board,from_x,from_y,from_x+2,from_y,p)==1){

                board[from_x][from_y] = empty;
                board[from_x+2][from_y] = p_type;
                board[from_x+1][from_y] = empty;
                from_x=from_x+2;

            }
            else if (check_if_edible(board,from_x,from_y,from_x-2,from_y,p)==1){
                board[from_x][from_y] = empty;
                board[from_x-2][from_y] = p_type;
                board[from_x-1][from_y] = empty;
                from_x=from_x-2;



            }
            else if (check_if_edible(board,from_x,from_y,from_x,from_y+2,p)==1){
                board[from_x][from_y] = empty;
                board[from_x][from_y+2] = p_type;
                board[from_x][from_y+1] = empty;
                from_y=from_y+2;

            }
            else if (check_if_edible(board,from_x,from_y,from_x,from_y-2,p)==1){
                board[from_x][from_y] = empty;
                board[from_x][from_y-2] = p_type;
                board[from_x][from_y-1] = empty;
                from_y=from_y-2;

            }
            else{
                n=0;
                return n;
            }
        }

        n=1;

    }

    n+=recur_eating(board,from_x,from_y,p);
    if (must_eat==true && n<=0)
        return -1;


    /*
    if (abs(from_x-to_x )> 1  || abs(from_y-to_y) > 1)
        n=recur_eating(board,from_x,from_y,p);

    if (n!=0)
        return n;*/

    if(n==0)  {
        board[to_x][to_y]=board[from_x][from_y];
        board[from_x][from_y]=empty;

    }


    return n;
}

int recur_eating(piece board[][8],int from_x,int from_y,player p){

    piece p_type=white_man;
    if (p==black){
        p_type=black_man;
    }
    display_board(board);
    if (from_x==0 || from_x==7)
        return 0;
    if (check_if_edible(board,from_x,from_y,from_x+2,from_y,p)==1){

        board[from_x][from_y] = empty;
        board[from_x+2][from_y] = p_type;
        board[from_x+1][from_y] = empty;
        return  1+recur_eating(board, from_x+2, from_y, p);
    }
    if (check_if_edible(board,from_x,from_y,from_x-2,from_y,p)==1){
        board[from_x][from_y] = empty;
        board[from_x-2][from_y] = p_type;
        board[from_x-1][from_y] = empty;

        return  1+recur_eating(board, from_x-2, from_y, p);
    }
    if (check_if_edible(board,from_x,from_y,from_x,from_y+2,p)==1){
        board[from_x][from_y] = empty;
        board[from_x][from_y+2] = p_type;
        board[from_x][from_y+1] = empty;

        return  1+recur_eating(board, from_x, from_y+2,  p);
    }
    if (check_if_edible(board,from_x,from_y,from_x,from_y-2,p)==1){
        board[from_x][from_y] = empty;
        board[from_x][from_y-2] = p_type;
        board[from_x][from_y-1] = empty;

        return  1+recur_eating(board, from_x, from_y-2, p);
    }

    return 0;

}
int check_if_edible(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p){

    if (board[to_x][to_y]!=empty)
        return 0;
    if (p==black){
        if (from_x-to_x<0 && (board[from_x+1][from_y] == white_man ))
            return 1;
        if (from_y-to_y<0 && (board[from_x][from_y+1] == white_man ))
            return 1;
        if (from_y-to_y>0 && (board[from_x][from_y-1] == white_man ))
            return 1;
    }
    if (p==white){
        if (from_x-to_x>0 && (board[from_x-1][from_y] == black_man ))
            return 1;
        if (from_y-to_y<0 && (board[from_x][from_y+1] == black_man ))
            return 1;
        if (from_y-to_y>0 && (board[from_x][from_y-1] == black_man ))
            return 1;
    }
    return 0;

}
void scan_board(piece board[][8],player p,int edible_arr[]){
    int i,k,j,counter=0;
    for (k = 0; k <32 ; ++k) {
        edible_arr[k]=0;
    }
    piece p_type=white_man;
    if (p==black){
        p_type=black_man;
    }
    for (i = 0; i <8 ; ++i) {
        for (j = 0; j <8 ; ++j) {
            if(board[i][j]==p_type){
                if (j<6 &&  check_if_edible(board,i,j,i,j+2,p) == 1){
                    edible_arr[counter]=i;
                    counter++;
                    edible_arr[counter]=j;
                    counter++;
                }
                else if ( j>1 && check_if_edible(board,i,j,i,j-2,p) == 1){
                    edible_arr[counter]=i;
                    counter++;
                    edible_arr[counter]=j;
                    counter++;
                }
                else if (p==black && i<6 &&  check_if_edible(board,i,j,i+2,j,p) == 1 ) {
                    edible_arr[counter]=i;
                    counter++;
                    edible_arr[counter]=j;
                    counter++;
                }
                else if(p==white && i>1 && check_if_edible(board,i,j,i-2,j,p )== 1){
                    edible_arr[counter]=i;
                    counter++;
                    edible_arr[counter]=j;
                    counter++;
                }
            }
        }
    }
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
    if (abs(from_x-to_x) >= 1 && abs(from_y-to_y) >= 1)
        return 0;
    if (abs(to_x-from_x)>2 )
        return 0;
    if (abs(to_y-from_y)>2 )
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
    
    int a,b,c,d,n,edible_arr[32]={0},i,j;
  /*  piece my_board[ROWS][COLS]=
        {{empty,empty,empty,empty,empty,empty,empty,empty},
         {black_man,black_man,black_man,black_man,black_man,black_man,black_man,black_man},
         {black_man,empty,empty,black_man,black_man,black_man,black_man,black_man},
         {white_man,empty,empty,empty,empty,empty,empty,empty},
         {empty,white_man,empty,empty,empty,empty,empty,empty},
         {white_man,empty,empty,white_man,white_man,white_man,white_man,white_man},
         {white_man,white_man,white_man,white_man,white_man,white_man,white_man,white_man},
         {empty,empty,empty,empty,empty,empty,empty,empty},
        };  */
    BOOL must_eat=false;

    init_board(my_board);

    display_board(my_board);


    for ( ; check_end_of_game(my_board)==-1 ; ) {

        do {
            if (must_eat ==false )
                scan_board(my_board,10,edible_arr);
            

            printf("white tas ve hareket sec ve oyuncu sec :");
            scanf(" %d %d %d %d", &a, &b, &c, &d);
            if (edible_arr[0]!=0){
                must_eat=true;
                for ( i = 0; i <31 ; i+=2) {
                    if(edible_arr[i] == a && edible_arr [i+1] == b)
                        break;
                }
                if (i>=32){
                    

                    n=-1;

                    printf("tas yemek mecburi!!!!!\n");
                    j=0;
                    while(j<31){
                        
                        if(edible_arr[j] !=0 || edible_arr[j+1] != 0)
                            printf("%d : %d \n",edible_arr[j],edible_arr[j+1]);
                        else
                            break;
                        j+=2;
                    }
                    continue;
                }


            }
            n = move(my_board, a, b, c, d, 10,must_eat);


            printf("n=%d\n",n);
            

            display_board(my_board);
        }while(n<0);

        must_eat=false;
        do {
            if (must_eat ==false )
                scan_board(my_board,20,edible_arr);

            

            printf("black tas ve hareket sec ve oyuncu sec :");
            scanf(" %d %d %d %d", &a, &b, &c, &d);

            if (edible_arr[0]!=0){
                must_eat=true;
                for ( i = 0; i <31 ; i+=2) {
                    if(edible_arr[i] == a && edible_arr [i+1] == b)
                        break;
                }
                if (i>=32){
                    

                    n=-1;

                    printf("tas yemek mecburi!!!!!\n");
                    j=0;
                    while(j<31){
                        

                        if(edible_arr[j] !=0 || edible_arr[j+1] != 0)
                            printf("%d : %d \n",edible_arr[j],edible_arr[j+1]);
                        j+=2;
                    }
                    continue;

                }

            }
            n = move(my_board, a, b, c, d, 20,must_eat);


            printf("n=%d\n",n);
            

            display_board(my_board);
        }while(n<0);
        must_eat=false;

    }
    

    display_board(my_board);
}
