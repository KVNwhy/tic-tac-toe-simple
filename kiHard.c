#include <stdlib.h>
#include <stdio.h>
#include "spielerKIHeader.h"


/*
* Hauptfunktion des Schweren Gegners. Ruft die Funktionen zur Berechnung der MinMax Werte auf
* und entscheidet den n�chsten Zug und f�hrt ihn durch
*
* maximale Max wert ist der beste eigene Zug
* maximale Min Wert ist der beste Zug des Gegners
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* mark ist das Zeichen des Computers (X/O)
*
* Der return ist '0' sobald der Zug gemacht wurde
*/
int kiHard(char board[3][3], char mark) {

    int maxValue[3][3];
    int minValue[3][3];

    printf("\nZug von schwerer KI \n");

    for (int i = 0; i < 3; i++) {//berechnung der Min/Max Werte aller leeren Felder 
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {//leeres Feld

                maxValue[i][j] = minMaxValue(board, i, j, 0, mark); //max Wert f�r das Feld i j
                minValue[i][j] = minMaxValue(board, i, j, 1, mark); //min Wert f�r das Feld i j

            }
            else { //belegetes Feld

                minValue[i][j] = -1;
                maxValue[i][j] = -1;
            }
        }
    }

    int highestTmpV = -1;
    int bestRow, bestColum;

    /*
    * Suche nach dem besten Spielzugs anhand der Min/Max Werte.
    * Es wird nach einem Spielzug gesucht die Sofort gewinnen.
    * Falls keiner gefunden wird nachen einem gesucht mit dem der gegner sofort gewinnt.
    * Traf keiner der F�lle zu wird des Zug mit der gr��ten Summe aus Min und Max gew�hlt
    */

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (maxValue[i][j] != -1) {     //ignorieren der belegten Felder

                if (maxValue[i][j] >= 10) {//Ein feld mit einem Max wert gr��er 10 ist ein Spielzug mit dem der Computer sofort gewinnt

                    board[i][j] = mark;
                    return 0;

                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (maxValue[i][j] != -1) {
                if (minValue[i][j] >= 10) { //Ein feld mit einem Min wert gr��er 10 ist ein Spielzug mit dem der Gegerner sofort gewinnt w�rde und den der Computer verhindert

                    board[i][j] = mark;
                    return 0;

                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (maxValue[i][j] != -1) {
                if (maxValue[i][j] + minValue[i][j] > highestTmpV) { //Der Zug mit der gr��ten Summe aus Min und Max. Der Zug der den Computer am weitesten bringt w�hrend der gegner am weitesten zur�ck geworfen wird   

                    highestTmpV = maxValue[i][j] + minValue[i][j];
                    bestRow = i;
                    bestColum = j;

                }
            }
        }
    }
    board[bestRow][bestColum] = mark;
    return 0;
}

/*
* Ruft alle Funktionen, zur berechnung des Min/Max Werts eines Feldes, auf.
* Es werden sich die Zeile/Spalte/diagonalen des Feldes angeschaut.
* Es wird gesaucht, ob diese frei von Zeichen des Gegners sind und wie viele eigne Zeichen auf ihnen liegen.
* Je mehr das die Zeile/Spalte/diagonalen erf�llen desto h�cher ist der Min/max wert
*
* F�r den Min Wert werden die Zeichen O/X vertauscht und selben berechnungen wie beim Max wert
* Der Min wert ist sozusagen der 'Max wert des Gegners'
*
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* row ist die Zeile des Feldes
* col ist die Spalte des Feldes
* minMax gibt an ob der min(1) oder max(0) Wert berechnet wird
* mark ist das Zeichen des Computergegners Schwer
*
* return ist der Min oder Max Wert des Feldes board[row][colum]
*/
int minMaxValue(char board[3][3], int row, int col, int minMax, char mark) {

    int tmpValue;

    tmpValue = horizontCheck(board, row, minMax, mark);
    tmpValue += verticalCheck(board, col, minMax, mark);
    tmpValue += diagonal_R_Check(board, row, col, minMax, mark);
    tmpValue += diagonal_L_Check(board, row, col, minMax, mark);

    return tmpValue;
}

/*
* falls n�tig vertauscht die Zeichen O/X zur Min berechnung
* signs[2] Speicherort f�r die Zeichen O/X 
* type gibt an ob Min oder Max Wert berechnet wird
* mark ist das Zeichen des Computers
* 
* der return ist das array im dem Zeichen des Computer auf sings[0] und dem Zeichen des Gegners auf signs[1] und f�r die Min berechnert ist die Anordnung vertauscht
*/
void ownOppositeSign(char signs[2], int type, char mark) {

    char own = mark;
    char opposite;

    if (mark == 'X') {
        opposite = 'O';
    }
    else {
        opposite = 'X';
    }

    if (type == 1) {
        own = opposite;
        opposite = mark;
    }

    signs[0] = own;
    signs[1] = opposite;

}

/*
* Gibt den Min/Max wert einer Zeile zur�ck
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* row die Zeile die Bewerte wird
* type gibt an ob Min oder Max wert berechnet wird
* mark ist das Zeichen des Computers
*
* Der Return ist der Min oder Max Wert der Zeile
*/
int horizontCheck(char board[3][3], int row, int type, char mark) {

    char signs[2];

    ownOppositeSign(signs, type, mark);//Setzen der Zeichen X/O

    int noEnemySign = 0;
    int ownSign = 0;

    for (int i = 0; i < 3; i++) {

        if (board[row][i] != signs[1]) {//Anzahl der Felder ohne gegner Zeichen
            noEnemySign++;

            if (board[row][i] == signs[0])//Anzahl der eignen Zeichnen
            {
                ownSign++;

            }

        }
    }

    if (noEnemySign == 3) {//Zeile frei vom Zeichen des Gegners
        if (ownSign == 2) {//Mit der Zeile kann sofort gewonnen werden da bereit zwei eigne Zeichen auf ihr liegen
            ownSign = 10;
        }
        else
        {
            ownSign++;
        }
    }
    else {//Auf der Zeile liegt bereits ein Zeichen des Gegners und kann somit nicht mehr benutzt werden um zu gewinnen
        ownSign = 0;
    }

    return ownSign;
}

/*
* Analog zu horizontCheck
* hier wird der Min/Max Wert der Spalte col berechnet
*/
int verticalCheck(char board[3][3], int col, int type, char mark) {

    char signs[2];

    ownOppositeSign(signs, type, mark);

    int noEnemySign = 0;
    int ownSign = 0;

    for (int i = 0; i < 3; i++) {

        if (board[i][col] != signs[1]) {
            noEnemySign++;
            if (board[i][col] == signs[0])
            {
                ownSign++;
            }

        }
    }

    if (noEnemySign == 3) {
        if (ownSign == 2) {
            ownSign = 10;
        }
        else
        {
            ownSign++;
        }

    }
    else
    {
        ownSign = 0;
    }

    return ownSign;
}

/*
* Analog zu horizontCheck
* hier wird der Min/Max Wert der Diagonale von oben links nach unten rechts
*
* Nicht jedes Feld liegt auf der Diagonale.
* Das wird zus�tzlich �berpr�ft
*/
int diagonal_L_Check(char board[3][3], int row, int col, int type, char mark) {

    char signs[2];

    ownOppositeSign(signs, type, mark);

    int noEnemySign = 0;
    int ownSign = 0;

    if (row == col) {//�berpr�ft ob das �bergene Feld auf der Diagonale liegt
        for (int i = 0; i < 3; i++) {

            if (board[i][i] != signs[1]) {
                noEnemySign++;
                if (board[i][i] == signs[0])
                {
                    ownSign++;
                }

            }
        }
    }

    if (noEnemySign == 3) {
        if (ownSign == 2) {

            ownSign = 10;
        }
        else
        {
            ownSign++;
        }

    }
    else
    {
        ownSign = 0;
    }

    return ownSign;
}


/*
* Analog zu diagonal_L_Check
* hier wird der Min/Max Wert der Diagonale von oben rechts nach unten links
*
* Nicht jedes Feld liegt auf der Diagonale.
* Das wird zus�tzlich �berpr�ft
*/
int diagonal_R_Check(char board[3][3], int row, int col, int type, char mark) {

    char signs[2];

    ownOppositeSign(signs, type, mark);

    int noEnemySign = 0;
    int ownSign = 0;
    int onDiagonal = 0;

    for (int i = 0; i < 3; i++) {

        if ((i == row) & (col == 2 - i)) {//�berpr�ft ob das �bergene Feld auf der Diagonale liegt
            onDiagonal = 1;
        }

        if (board[i][2 - i] != signs[1]) {
            noEnemySign++;
            if (board[i][2 - i] == signs[0])
            {
                ownSign++;
            }

        }
    }


    if ((noEnemySign == 3) & (onDiagonal == 1)) {
        if (ownSign == 2) {
            ownSign = 10;
        }
        else
        {
            ownSign++;
        }

    }
    else
    {
        ownSign = 0;
    }

    return ownSign;
}