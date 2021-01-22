#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define f_size 10
typedef struct ttt{
    int pos;
    int comp_move;
    int p_move;
    char comp_sign;
    char p_sign;
    char chr;
    char diff;
    char field[f_size];
}tictactoe;
void acquirechar(tictactoe *ttt){
	for(int j=1; j<f_size; j++){
        	ttt->field[j]=ttt->chr;
	}
}
void print(char field[f_size], int n){
	printf("\t");
	for(int i=1; i<f_size; i++){
    		printf("%c ", field[i]);
    		if(i%n==0 && i!=pow(n,2)){
        		printf("\n\t");
		}
	}
}
int getmove(tictactoe *ttt){
	scanf("%d", &ttt->pos);
    	while(ttt->pos>9 || ttt->pos<=0){
        	printf("invalid position, please insert a new one : \n");
        	scanf("%d", &ttt->pos);
	}	
    	while(ttt->field[ttt->pos]!=ttt->chr){
	    	printf("invalid position, please insert a new one : \n");
	    	scanf("%d", &ttt->pos);
    	}
	return ttt->pos;
}
int game_ended(tictactoe *ttt){
	int WinningPos=0;
    	int WinningPosArr[10][10]={{1,2,3},{4,5,6}, {7,8,9}, {1,4,7}, {2,5,8}, {3,6,9}, {1,5,9}, {3,5,7}};
    	for (int i=0; i<9; ++i){
		if(ttt->field[WinningPosArr[i][WinningPos]]==ttt->field[WinningPosArr[i][WinningPos+1]] && ttt->field[WinningPosArr[i][WinningPos]]==ttt->field[WinningPosArr[i][WinningPos+2]]){
			if(ttt->field[WinningPosArr[i][WinningPos]]==ttt->p_sign){
				return -1;
			}
		else if(ttt->field[WinningPosArr[i][WinningPos]]==ttt->comp_sign){
			return 1;
		}
		}
	}
	return 0;
}
int minimax(tictactoe ttt, int pl){
	int win=game_ended(&ttt);
	if(win!=0){
		return win*pl;
	}
	int score=-10;
	int move=-10;
	int moveScore;
	for(int i=1; i<=9; ++i){
		if(ttt.field[i]==ttt.chr){
			ttt.field[i]=(pl==-1) ? ttt.p_sign : ttt.comp_sign;
			moveScore=-minimax(ttt, -pl);
			if(moveScore>score){
				score=moveScore;
				move=i;
			}
			ttt.field[i]=ttt.chr;
		}
	}
	if(move==-10){
		return 0;
	}
	return score;

}
int makeMove(tictactoe ttt){
	int score=-10;
	int move;
	int thisScore;
	for(int j=1; j<=9; j++){
		if(ttt.field[j]==ttt.chr){
			ttt.field[j]=ttt.comp_sign;
			int thisScore = -minimax(ttt, -ttt.comp_move);
			ttt.field[j]=ttt.chr;
			if(thisScore>score){
				score=thisScore;
				move=j;
			}
		}
	}
	return move;
}
void whoWins(tictactoe *ttt){
	switch (game_ended(ttt)){
		case -1:
			printf("\nThe game has ended. The player wins!\n");
			break;
		case 1:
			printf("\nThe game has ended. The computer wins!\n");
			break;
		case 0:
			printf("\nThe game has ended. It is a draw!\n");
			break;
	}
}
int main(void){
	srand(time(0));
	tictactoe ttt;
	printf("\nHi, player! Do you want your game to be (e)asy or (h)ard? " );
	scanf(" %c", &ttt.diff);
	printf("Please choose a character for the board to be made of : ");
	scanf(" %c", &ttt.chr);
	while(ttt.chr=='X' || ttt.chr=='O'){
		printf("Invalid character, please enter a new one : ");
		scanf(" %c", &ttt.chr);
	}
	acquirechar(&ttt);
	printf("\nDo you want to be first or second?(1/2) ");
	scanf("%d", &ttt.p_move);
	while(ttt.p_move>2 || ttt.p_move<1){
		printf("You can't be %d, there is no such turn! Please enter a valid position (1/2) ", ttt.p_move);
		scanf("%d", &ttt.p_move);
	}
	ttt.p_sign = (ttt.p_move==1) ? 'X' : 'O';
	ttt.comp_sign = (ttt.p_move==1) ? 'O' : 'X';
    	ttt.comp_move=1;
	ttt.p_move=-1;
	printf("\n");
    	for(int steps=0; game_ended(&ttt)==0 && steps<9; ++steps){
        	print(ttt.field, 3);
        	if(steps%2==0){ 
			printf("\nPlayer one, enter a position : ");
			if(ttt.p_sign=='X'){
				getmove(&ttt);
			}
			else {
				ttt.pos=(ttt.diff=='e') ? rand()%9 : makeMove(ttt);
				 while(ttt.field[ttt.pos]!=ttt.chr){
					 ttt.pos=rand()%9;
				 }
				printf(" %d\n", ttt.pos);
			}
		}
        	else{ 
			printf("\nPlayer two, enter a position : \t");
			if(ttt.p_sign=='O'){
				getmove(&ttt);
			}
			else{
				ttt.pos=(ttt.diff=='e') ? rand()%9 : makeMove(ttt);
				while(ttt.field[ttt.pos]!=ttt.chr){
					ttt.pos=rand()%9;
				}
				printf(" %d\n", ttt.pos);
			}
		}
    	if(steps%2==0){ 
        	ttt.field[ttt.pos]='X'; 
	}
    	else {
        	ttt.field[ttt.pos]='O'; 
	}
	}
	whoWins(&ttt);
     	printf("The final board is \n\n");
     	print(ttt.field, 3);
     	getch();
}
