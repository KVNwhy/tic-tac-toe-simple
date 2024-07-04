#include <stdlib.h>
#include <stdio.h>
#include "boardHeader.h"

/*
* Gibt das Board in der Konsole aus
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
*/
void drawBoard(char board[3][3]) {
    char tmp;
    printf("\n");
    printf("|---|---|---|");
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            tmp = board[i][j];
            printf(" %c ", tmp);

            printf("|");
        }
        printf("\n");
        printf("|---|---|---|");
        printf("\n");
    }

    printf("\n");
}

/*
* Analog zu DrawBoard, nur die platzhalter Zeichen "-"
* werden durch die NUmmer des Feldes ersetzt.
* Die Felder werden von 1-9 nummeriert
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
*/
void drawBoardN(char board[3][3]) {
    char tmp;
    printf("\n");
    printf("|---|---|---|");
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            tmp = board[i][j];
            if (tmp == '-') {
                printf(" %d ", 3 * i + j + 1);// 3*i+j+1 bestimmt die Nummer des Feldes
            }
            else {
                printf(" %c ", tmp);
            }
            printf("|");
        }
        printf("\n");
        printf("|---|---|---|");
        printf("\n");
    }

    printf("\n");

}

/*
* L�scht alles Zeichen vom Spielfeld und ersetzt sie durch '-'
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
*/
void resetBoard(char board[3][3]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
        }
    }

}


/*
* Z�hlt wie viele Platzhalter/Freie felder noch auf dem Spiel feld sind
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
*
* Der return gibt die Anzahl an freien Felder zur�ck
*/
int freeSlots(char board[3][3]) {

    int freeSpace = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                freeSpace++;
            }
        }
    }

    return freeSpace;

}

/*
*  �berpr�ft ob ein Zeichen drei mal in einer Zeile, in einer Spalte oder in einer Diagonale liegt.
*  Wenn es ein gewinner gibt wird dieser Zur�ckgegeben
*  anstonsten der Platzhalter
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
*
* Der return ist das gewinner Zeichen oder der Platzhalter
*/
char winningCondition(char board[3][3]) {
    char tmpChar;
    int winner;
    //�berpr�ft die Zeilen
    for (int i = 0; i < 3; i++) {
        winner = 1;
        tmpChar = board[i][0];
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != tmpChar) {
                winner = 0;
            }
        }
        if ((winner == 1) & (tmpChar != '-')) {
            return  tmpChar;
        }
    }
    //�berpr�ft die Spalten
    for (int i = 0; i < 3; i++) {
        winner = 1;
        tmpChar = board[0][i];
        for (int j = 0; j < 3; j++) {
            if (board[j][i] != tmpChar) {
                winner = 0;
            }
        }
        if ((winner == 1) & (tmpChar != '-')) {
            return  tmpChar;
        }
    }

    //check diagonal
    if ((board[0][0] == board[1][1]) & (board[1][1] == board[2][2]) & (board[0][0] != '-')) {
        return  board[0][0];
    }

    if ((board[0][2] == board[1][1]) & (board[1][1] == board[2][0]) & (board[0][2] != '-')) {
        return  board[0][2];
    }

    //no winner
    return '-';
}