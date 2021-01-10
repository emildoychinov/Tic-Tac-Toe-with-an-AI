#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#define f_size 10
typedef struct ttt{
    int pos;
    int comp_move;
    int p_move;
    char field[f_size][f_size];
}tictactoe;
void acquirechar(char field[f_size][f_size]){
    for(int j=1; j<f_size; j++){
        strcpy(field[j], "*");
    }
}
void print(char field[f_size][f_size], int n){
for(int i=1; i<f_size; i++){
    printf("%s", field[i]);
    if(i%n==0){
        printf("\n");
    }
}
}
int getmove(tictactoe *ttt){
    scanf("%d", &ttt->pos);
    while(ttt->pos>9 || ttt->pos<=0){
        printf("invalid position, please insert a new one : \n");
        scanf("%d", &ttt->pos);
    }
    while(strcmp(ttt->field[ttt->pos], "*")!=0){
	    printf("invalid position, please insert a new one : \n");
	    scanf("%d", &ttt->pos);
    }
	return ttt->pos;
}
int game_ended(tictactoe *ttt){
    int WinningPos=0;
    int WinningPosArr[10][10]={{1,2,3},{4,5,6}, {7,8,9}, {1,4,7}, {2,5,8}, {3,6,9}, {1,5,9}, {3,5,7}};
    for (int i=0; i<9; ++i){
        if(strcmp(ttt->field[WinningPosArr[i][WinningPos]], "X")==0 && strcmp(ttt->field[WinningPosArr[i][WinningPos+1]], "X" )==0 && 
            	strcmp(ttt->field[WinningPosArr[i][WinningPos+2]], "X" )==0){
                return 1;
            }
	else if(strcmp(ttt->field[WinningPosArr[i][WinningPos]], "O")==0 && strcmp(ttt->field[WinningPosArr[i][WinningPos+1]], "O" )==0 && 
            strcmp(ttt->field[WinningPosArr[i][WinningPos+2]], "O" )==0){
                return -1;
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
	int i;
	int moveScore;
	for(i=1; i<=9; ++i){
		if(strcmp(ttt.field[i], "*")==0){
			strcpy(ttt.field[i], (pl==1) ? "X" : "O");
			moveScore=(ttt.comp_move==-1) ? minimax(ttt, -pl) : -minimax(ttt, -pl);
			if(moveScore>score){
				score=moveScore;
				move=i;
			}
			strcpy(ttt.field[i], "*");
		}
	}
	if(move==-10){
		return 0;
	}
	return score;

}
int makeMove(tictactoe ttt){
	char sign[1];
	int score=-10;
	int move;
	int j;
	int thisScore;
	(ttt.comp_move==2) ? strcpy(sign, "O") : strcpy(sign, "X");
	for(j=1; j<=9; j++){
		if(strcmp(ttt.field[j], "*")==0){
			strcpy(ttt.field[j], sign);
			int thisScore = (ttt.comp_move==-1) ? minimax(ttt, ttt.p_move) : -minimax(ttt, ttt.p_move);
			strcpy(ttt.field[j], "*");
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
		case 1:
			printf("The game has ended. Player 1 wins!\n");
			break;
		case -1:
			printf("The game has ended. Player 2 wins!\n");
			break;
		case 0:
			printf("The game has ended. It is a draw!\n");
			break;
	}
}
int main(void){
	srand(time(0));
	tictactoe ttt;
	int steps=0;
	acquirechar(ttt.field);
	printf("hi, player! do you want to be first or second?(1/2)");
	scanf("%d", &ttt.p_move);
    	if(ttt.p_move==1){
		ttt.comp_move=-1;
    	}
    	else {
		ttt.comp_move=1;
		ttt.p_move=-1;
	}
    	for(steps; game_ended(&ttt)==0 && steps<9; ++steps){
        	print(ttt.field, 3);
        	if(steps%2==0){ 
			printf("player one, enter a position : \n");
			if(ttt.p_move==1){
				getmove(&ttt);
			}
			else {
				if(steps>1){
					ttt.pos=makeMove(ttt);
				}
				else {
					ttt.pos=rand()%9;
				}
				printf("\n%d\n", ttt.pos);
			}
		}
        	else{ 
			printf("player two, enter a position : \n");
			if(ttt.p_move==-1){
				getmove(&ttt);
			}
			else{
				ttt.pos=makeMove(ttt);
				printf("\n%d\n", ttt.pos);
			}
		}
    	if(steps%2==0){ 
        	strcpy(ttt.field[ttt.pos], "X"); 
	}
    	else {
        	strcpy(ttt.field[ttt.pos], "O"); 
	}
	}
	whoWins(&ttt);
     	printf("The final board is : \n");
     	print(ttt.field, 3);
     	getch();
}
