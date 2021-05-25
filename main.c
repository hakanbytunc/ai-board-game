
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 20

void fillBoard(int pieces, char board[7][7]);
void printBoard(char board[7][7]);
int getAvailableMoves(char board[7][7], int posX, int posY);
int getTotalUserMoves(char board[7][7], int arrUser, int numPieces);
void moveUser(char board[7][7], int playerNum, int limit);		
//int calculate(char board[7][7], int playerNum, int limit);
int getTotalMovesOfX(char board[7][7]);
int getTotalMovesOfO(char board[7][7]);
bool isTerminal(char board[7][7], int limit);
int calculateForO(char board[7][7], int playerNum, int limit, int height);
int calculateForX(char board[7][7], int playerNum, int limit, int height);

int main(){
	char board[7][7];
	int result;
	int limit;
	int numPieces;
	int playerNum;
	int i,j;
	
	bool userStarts;
	printf("Enter the turn limit: ");
	scanf("%d", &limit);
	printf("Enter the number of pieces: ");
	scanf("%d", &numPieces);
	printf("Enter 1 to be first, otherwise enter 2: ");
	scanf("%d", &playerNum);
	int height = limit*2;
	int limit2 = limit*2;
	if(playerNum == 1){
		userStarts = true;
	}
	else if(playerNum == 2){
		userStarts = false;
	}
	else{
		printf("\n INVALID USER NUMBER. PLEASE ENTER 1 OR 2!\n");
		return -1;
	}

	fillBoard(numPieces, board);
	printBoard(board);
/*
	if(userStarts){
		int bestValue;
		while(limit2 > 0){
			moveUser(board, playerNum, limit);
			printBoard;
			bestValue = calculateForO(board, playerNum, limit, height);
			limit--;
			if(isTerminal){
				printf("\n GAME OVER \n");
				return 0;
			}
		}
	}

	if(!userStarts){
		int bestValue;
		while(limit2 > 0){
			calculateForX(board, playerNum, limit2, height);
			printBoard;
			moveUser(board, playerNum, limit);
			printBoard;
			limit--;
			if(isTerminal){
				printf("\n GAME OVER \n");
				return 0;
			}
		}
	}
*/

	moveUser(board, playerNum, limit);
	printBoard(board);
	int test;
	height=limit*2-1;
	limit2=limit*2-1;
	test = calculateForO(board, playerNum, limit2, height);
	printf("\n CALCULATION RESULT FOR 'O' : %d \n", test);
	printBoard(board);

	return 0; 
}

int calculateForO(char board[7][7], int playerNum, int limit2, int height){
	int i,j;
	char tmpBoard[7][7];
	if(limit2 == 0){
		return getTotalMovesOfO(board);
	}
	if(playerNum == 1){
		int bestValue = -9999;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(board[i][j] == 'O'){
					if(j != 0 && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 2, limit2-1, height);
						if(value > bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								
								memcpy(board, tmpBoard, 7*7*sizeof(char));	//Tree'den gelen en yüksek değerin bulunduğu ve
																			   //depth'i en az olan node'daki hamleyi board'a
																				//kopyalamaya çalıştım (ai için sıradaki hamle)
																				//ama olmadı.
							}
						}
					}
					if(i != 6 && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 2, limit2-1, height);
						if(value > bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(j != 6 && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 2, limit2-1, height);
						if(value > bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 0 && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i-1][j] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 2, limit2-1, height);
						if(value > bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
				}
			}
		}
		return bestValue;
	}
	if(playerNum == 2){
		int bestValue = 9999;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(board[i][j] == 'X'){
					if(j != 0 && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 1, limit2-1, height);
						if(value < bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 6 && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 1, limit2-1, height);
						if(value < bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(j != 6 && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 1, limit2-1, height);
						if(value < bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 0 && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i-1][j] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForO(tmpBoard, 1, limit2-1, height);
						if(value < bestValue){
							bestValue = value;
							printBoard(tmpBoard);
							if(height-1 == limit2){
								printBoard(tmpBoard);
								memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
				}
			}
		}
		return bestValue;
	}
}
int calculateForX(char board[7][7], int playerNum, int limit, int height){
	int i,j;
	char tmpBoard[7][7];
	if(limit == 0){
		return getTotalMovesOfX(board);
	}
	if(playerNum == 1){
		int bestValue = 9999;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(board[i][j] == 'O'){
					if(j != 0 && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 2, limit-1, height);
						if(value < bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 6 && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 2, limit-1, height);
						if(value < bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(j != 6 && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 2, limit-1, height);
						if(value < bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 0 && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i-1][j] = 'O';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 2, limit-1, height);
						if(value < bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
				}
			}
		}
		return bestValue;
	}
	if(playerNum == 2){
		int bestValue = -9999;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(board[i][j] == 'X'){
					if(j != 0 && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 1, limit-1, height);
						if(value > bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 6 && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 1, limit-1, height);
						if(value > bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(j != 6 && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 1, limit-1, height);
						if(value > bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
					if(i != 0 && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i-1][j] = 'X';
						tmpBoard[i][j] = '-';
						int value = calculateForX(tmpBoard, 1, limit-1, height);
						if(value > bestValue){
							bestValue = value;
							if(height == limit){
								//printBoard(tmpBoard);
								//memcpy(board, tmpBoard, 7*7*sizeof(char));
							}
						}
					}
				}
			}
		}
		return bestValue;
	}
}
void moveUser(char board[7][7], int playerNum, int limit){
	//safe_flush();
	int posX, posY;
	int posXnext, posYnext;
        char currLoc[MAX_LIMIT];
        char nextLoc[MAX_LIMIT];
	int tmpX, tmpY;
	char tmpToken;

	printf("Enter piece index to move  \n");
	scanf("%s", currLoc);
	printf("Enter where to move:");
	scanf("%s", nextLoc);

	
	if(strcmp(currLoc, "a1") == 0){posY = 0; posX = 0;}
	if(strcmp(currLoc, "a2") == 0){posY = 1; posX = 0;}
	if(strcmp(currLoc, "a3") == 0){posY = 2; posX = 0;}
	if(strcmp(currLoc, "a4") == 0){posY = 3; posX = 0;}
	if(strcmp(currLoc, "a5") == 0){posY = 4; posX = 0;}
	if(strcmp(currLoc, "a6") == 0){posY = 5; posX = 0;}
	if(strcmp(currLoc, "a7") == 0){posY = 6; posX = 0;}
	if(strcmp(currLoc, "b1") == 0){posY = 0; posX = 1;}
	if(strcmp(currLoc, "b2") == 0){posY = 1; posX = 1;}
	if(strcmp(currLoc, "b3") == 0){posY = 2; posX = 1;}
	if(strcmp(currLoc, "b4") == 0){posY = 3; posX = 1;}
	if(strcmp(currLoc, "b5") == 0){posY = 4; posX = 1;}
	if(strcmp(currLoc, "b6") == 0){posY = 5; posX = 1;}
	if(strcmp(currLoc, "b7") == 0){posY = 6; posX = 1;}
	if(strcmp(currLoc, "c1") == 0){posY = 0; posX = 2;}
	if(strcmp(currLoc, "c2") == 0){posY = 1; posX = 2;}
	if(strcmp(currLoc, "c3") == 0){posY = 2; posX = 2;}
	if(strcmp(currLoc, "c4") == 0){posY = 3; posX = 2;}
	if(strcmp(currLoc, "c5") == 0){posY = 4; posX = 2;}
	if(strcmp(currLoc, "c6") == 0){posY = 5; posX = 2;}
	if(strcmp(currLoc, "c7") == 0){posY = 6; posX = 2;}
	if(strcmp(currLoc, "d1") == 0){posY = 0; posX = 3;}
	if(strcmp(currLoc, "d2") == 0){posY = 1; posX = 3;}
	if(strcmp(currLoc, "d3") == 0){posY = 2; posX = 3;}
	if(strcmp(currLoc, "d4") == 0){posY = 3; posX = 3;}
	if(strcmp(currLoc, "d5") == 0){posY = 4; posX = 3;}
	if(strcmp(currLoc, "d6") == 0){posY = 5; posX = 3;}
	if(strcmp(currLoc, "d7") == 0){posY = 6; posX = 3;}
	if(strcmp(currLoc, "e1") == 0){posY = 0; posX = 4;}
	if(strcmp(currLoc, "e2") == 0){posY = 1; posX = 4;}
	if(strcmp(currLoc, "e3") == 0){posY = 2; posX = 4;}
	if(strcmp(currLoc, "e4") == 0){posY = 3; posX = 4;}
	if(strcmp(currLoc, "e5") == 0){posY = 4; posX = 4;}
	if(strcmp(currLoc, "e6") == 0){posY = 5; posX = 4;}
	if(strcmp(currLoc, "e7") == 0){posY = 6; posX = 4;}
	if(strcmp(currLoc, "f1") == 0){posY = 0; posX = 5;}
	if(strcmp(currLoc, "f2") == 0){posY = 1; posX = 5;}
	if(strcmp(currLoc, "f3") == 0){posY = 2; posX = 5;}
	if(strcmp(currLoc, "f4") == 0){posY = 3; posX = 5;}
	if(strcmp(currLoc, "f5") == 0){posY = 4; posX = 5;}
	if(strcmp(currLoc, "f6") == 0){posY = 5; posX = 5;}
	if(strcmp(currLoc, "f7") == 0){posY = 6; posX = 5;}
	if(strcmp(currLoc, "g1") == 0){posY = 0; posX = 6;}
	if(strcmp(currLoc, "g2") == 0){posY = 1; posX = 6;}
	if(strcmp(currLoc, "g3") == 0){posY = 2; posX = 6;}
	if(strcmp(currLoc, "g4") == 0){posY = 3; posX = 6;}
	if(strcmp(currLoc, "g5") == 0){posY = 4; posX = 6;}
	if(strcmp(currLoc, "g6") == 0){posY = 5; posX = 6;}
	if(strcmp(currLoc, "g7") == 0){posY = 6; posX = 6;}
	
	if(playerNum == 1){
		if(board[posX][posY] == 'X'){
			printf("\n		CHECK PASSED	\n");
			tmpToken = 'X';
		}
	}
	else if(playerNum == 2){
		if(board[posX][posY] == 'O'){
			printf("\n		CHECK PASSED	\n");
			tmpToken = 'O';
		}
	}
	else{
		printf("!!!!!!! TOKEN UNMATCH !!!!!!!!");
	}
	tmpX = posX;
	tmpY = posY;
	
	if(strcmp(nextLoc, "a1") == 0){posY = 0; posX = 0;}
	if(strcmp(nextLoc, "a2") == 0){posY = 1; posX = 0;}
	if(strcmp(nextLoc, "a3") == 0){posY = 2; posX = 0;}
	if(strcmp(nextLoc, "a4") == 0){posY = 3; posX = 0;}
	if(strcmp(nextLoc, "a5") == 0){posY = 4; posX = 0;}
	if(strcmp(nextLoc, "a6") == 0){posY = 5; posX = 0;}
	if(strcmp(nextLoc, "a7") == 0){posY = 6; posX = 0;}
	if(strcmp(nextLoc, "b1") == 0){posY = 0; posX = 1;}
	if(strcmp(nextLoc, "b2") == 0){posY = 1; posX = 1;}
	if(strcmp(nextLoc, "b3") == 0){posY = 2; posX = 1;}
	if(strcmp(nextLoc, "b4") == 0){posY = 3; posX = 1;}
	if(strcmp(nextLoc, "b5") == 0){posY = 4; posX = 1;}
	if(strcmp(nextLoc, "b6") == 0){posY = 5; posX = 1;}
	if(strcmp(nextLoc, "b7") == 0){posY = 6; posX = 1;}
	if(strcmp(nextLoc, "c1") == 0){posY = 0; posX = 2;}
	if(strcmp(nextLoc, "c2") == 0){posY = 1; posX = 2;}
	if(strcmp(nextLoc, "c3") == 0){posY = 2; posX = 2;}
	if(strcmp(nextLoc, "c4") == 0){posY = 3; posX = 2;}
	if(strcmp(nextLoc, "c5") == 0){posY = 4; posX = 2;}
	if(strcmp(nextLoc, "c6") == 0){posY = 5; posX = 2;}
	if(strcmp(nextLoc, "c7") == 0){posY = 6; posX = 2;}
	if(strcmp(nextLoc, "d1") == 0){posY = 0; posX = 3;}
	if(strcmp(nextLoc, "d2") == 0){posY = 1; posX = 3;}
	if(strcmp(nextLoc, "d3") == 0){posY = 2; posX = 3;}
	if(strcmp(nextLoc, "d4") == 0){posY = 3; posX = 3;}
	if(strcmp(nextLoc, "d5") == 0){posY = 4; posX = 3;}
	if(strcmp(nextLoc, "d6") == 0){posY = 5; posX = 3;}
	if(strcmp(nextLoc, "d7") == 0){posY = 6; posX = 3;}
	if(strcmp(nextLoc, "e1") == 0){posY = 0; posX = 4;}
	if(strcmp(nextLoc, "e2") == 0){posY = 1; posX = 4;}
	if(strcmp(nextLoc, "e3") == 0){posY = 2; posX = 4;}
	if(strcmp(nextLoc, "e4") == 0){posY = 3; posX = 4;}
	if(strcmp(nextLoc, "e5") == 0){posY = 4; posX = 4;}
	if(strcmp(nextLoc, "e6") == 0){posY = 5; posX = 4;}
	if(strcmp(nextLoc, "e7") == 0){posY = 6; posX = 4;}
	if(strcmp(nextLoc, "f1") == 0){posY = 0; posX = 5;}
	if(strcmp(nextLoc, "f2") == 0){posY = 1; posX = 5;}
	if(strcmp(nextLoc, "f3") == 0){posY = 2; posX = 5;}
	if(strcmp(nextLoc, "f4") == 0){posY = 3; posX = 5;}
	if(strcmp(nextLoc, "f5") == 0){posY = 4; posX = 5;}
	if(strcmp(nextLoc, "f6") == 0){posY = 5; posX = 5;}
	if(strcmp(nextLoc, "f7") == 0){posY = 6; posX = 5;}
	if(strcmp(nextLoc, "g1") == 0){posY = 0; posX = 6;}
	if(strcmp(nextLoc, "g2") == 0){posY = 1; posX = 6;}
	if(strcmp(nextLoc, "g3") == 0){posY = 2; posX = 6;}
	if(strcmp(nextLoc, "g4") == 0){posY = 3; posX = 6;}
	if(strcmp(nextLoc, "g5") == 0){posY = 4; posX = 6;}
	if(strcmp(nextLoc, "g6") == 0){posY = 5; posX = 6;}
	if(strcmp(nextLoc, "g7") == 0){posY = 6; posX = 6;}
	
	posXnext = posX;
	posYnext = posY;
	posX = tmpX;
	posY = tmpY;
	int neighbor = 0;
	if((posY != 0) && board[posX][posY-1] == board[posXnext][posYnext]){		//		IS NEIGHBOR?
		neighbor = 1;
	}
	if((posX != 6) && board[posX+1][posY] == board[posXnext][posYnext]){
		neighbor = 1;
	}
	if((posY != 6) && board[posX][posY+1] == board[posXnext][posYnext]){
		neighbor = 1;
	}
	if((posX != 0) && board[posX-1][posY] == board[posXnext][posYnext]){
		neighbor = 1;
	}
	int isEmpty = 0;
	if(board[posXnext][posYnext] == '-'){
		isEmpty = 1;
	}
	if(neighbor && isEmpty){
		if(board[posX][posY] == tmpToken){				//  SAFE TO EXECUTE RELOCATION
			board[posXnext][posYnext] = tmpToken;
			board[posX][posY] = '-';
			limit--;
			printf("\n****	PIECE MOVED	FROM %s to %s	****\n", currLoc, nextLoc);
		}
	}
}
void fillBoard(int pieces, char board[7][7]){
	int i,j;
	int a;
	int randomNum, randomNum2;
	srand(time(NULL));
	randomNum = (rand() % 7);
	randomNum2 = (rand() % 7);
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			board[i][j] = '-';
		}
	}
	for(a=0; a<(pieces*2); a++){		
		if(a%2){
			board[randomNum][randomNum2] = 'X';
		}
		else{
			board[randomNum][randomNum2] = 'O';
		}	
		while(board[randomNum][randomNum2] != '-'){
			randomNum = (rand() % 7);
			randomNum2 = (rand() % 7);
		}		
	}
}
void printBoard(char board[7][7]){
	int i,j;
	printf("\n  1 2 3 4 5 6 7\n");
	for(i=0;i<7;i++){
		switch(i){
			case 0:
				printf("a ");
				break;
			case 1:
				printf("b ");
				break;
			case 2:
				printf("c ");
				break;
			case 3:
				printf("d ");
				break;
			case 4:
				printf("e ");
				break;
			case 5:
				printf("f ");
				break;
			case 6:
				printf("g ");
				break;
		}
		for(j=0;j<7;j++){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
int getAvailableMoves(char board[7][7], int posX, int posY){
	int moveCount = 0;
	if((posY != 0) && board[posX][posY-1] == '-'){
		moveCount++;
	}
	if((posX != 6) && board[posX+1][posY] == '-'){
		moveCount++;
	}
	if((posY != 6) && board[posX][posY+1] == '-'){
		moveCount++;
	}
	if((posX != 0) && board[posX-1][posY] == '-'){
		moveCount++;
	}
	return moveCount;			
}
int getTotalMoves(char board[7][7], int playerNum){
	char token;
	int i,j;
	int moveCount;
	int totalMove;
	if(playerNum == 1){token = 'X';}
	else{token = 'O';}
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			moveCount = 0;
			if(board[i][j] == token){
				if((j != 0) && board[i][j-1] == '-'){
					moveCount++;
				}
				if((i != 6) && board[i+1][j] == '-'){
					moveCount++;
				}
				if((j != 6) && board[i][j+1] == '-'){
					moveCount++;
				}
				if((i != 0) && board[i-1][j] == '-'){
					moveCount++;
				}
			}
			totalMove = totalMove + moveCount;
		}
	}
	return totalMove;
}
int getTotalMovesOfX(char board[7][7]){
	int i,j;
	int totalMove = 0;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if(board[i][j] == 'X'){
				if((j != 0) && board[i][j-1] == '-'){
					totalMove++;
				}
				if((i != 6) && board[i+1][j] == '-'){
					totalMove++;
				}
				if((j != 6) && board[i][j+1] == '-'){
					totalMove++;
				}
				if((i != 0) && board[i-1][j] == '-'){
					totalMove++;
				}
			}
		}
	}
	return totalMove;
}
int getTotalMovesOfO(char board[7][7]){
	int i,j;
	int totalMove = 0;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if(board[i][j] == 'O'){
				if((j != 0) && board[i][j-1] == '-'){
					totalMove++;
				}
				if((i != 6) && board[i+1][j] == '-'){
					totalMove++;
				}
				if((j != 6) && board[i][j+1] == '-'){
					totalMove++;
				}
				if((i != 0) && board[i-1][j] == '-'){
					totalMove++;
				}
			}
		}
	}
	return totalMove;
}
bool isTerminal(char board[7][7], int limit){
	if(limit == 0){
		return true;
	}
	if(getTotalMovesOfX(board) == 0){
		return true;
	}
	if(getTotalMovesOfO(board) == 0){
		return true;
	}	
	return false;
}

//!!!!!!	FILL THIS	!!!!! int calculateForX(char board[7][7], int playerNum, int limit, int height){}




/*

int calculate(char board[7][7], int playerNum, int limit){
	int i,j;
	int bestValue;
	char tmpBoard[7][7];
	if(limit == 0){
		return getTotalMovesOfO(board);
	}
	if(playerNum == 1){
		bestValue = -999;
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(board[i][j] == 'O'){
					if((j != 0) && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'O';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 2, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue > bestValue){
							bestValue = currValue;
						}
					}
					if((i != 6) && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'O';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 2, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue > bestValue){
							bestValue = currValue;
						}
					}
					if((j != 6) && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'O';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 2, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue > bestValue){
							bestValue = currValue;
						}
					}
					if((i != 0) && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, limit-1);
						tmpBoard[i-1][j] = 'O';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 2, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue > bestValue){
							bestValue = currValue;
						}
					}
				}
			}
		}
		printf("\nreturned best value from 1 : %d \n",bestValue);
		return bestValue;

	}
	if(playerNum == 2){
		bestValue = 999;
		for(i=0;i<7;i++){
			for(i=0;i<7;i++){
				if(board[i][j] == 'X'){
					if((j != 0) && board[i][j-1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j-1] = 'X';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 1, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue < bestValue){
							bestValue = currValue;
						}
					}
					if((i != 6) && board[i+1][j] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i+1][j] = 'X';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 1, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue < bestValue){
							bestValue = currValue;
						}
					}
					if((j != 6) && board[i][j+1] == '-'){
						memcpy(tmpBoard, board, 7*7*sizeof(char));
						tmpBoard[i][j+1] = 'X';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 1, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue < bestValue){
							bestValue = currValue;
						}
					}
					if((i != 0) && board[i-1][j] == '-'){
						memcpy(tmpBoard, board, limit-1);
						tmpBoard[i-1][j] = 'X';
						tmpBoard[i][j] = '-';
						int currValue = calculate(tmpBoard, 1, limit-1);
						printf("\n current value = %d\tbest value = %d\tlimit = %d",currValue, bestValue, limit);
						if(currValue < bestValue){
							bestValue = currValue;
						}
					}
				}
			}
		}
		printf("\nreturned best value from 2 : %d \n",bestValue);
		return bestValue;
	}
}

*/

