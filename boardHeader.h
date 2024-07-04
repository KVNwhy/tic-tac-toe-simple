#ifndef board_H_   
#define board_H_

void drawBoard(char board[3][3]);
void drawBoardN(char board[3][3]);
void resetBoard(char board[3][3]);
int freeSlots(char board[3][3]);
char winningCondition(char board[3][3]);

#endif
