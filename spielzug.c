#include <stdlib.h>
#include <stdio.h>
#include "spielerKIHeader.h"
#include "spielzugHeader.h"

/*
* Ruft die Funktion auf die zum akutellen Spieler geh�rt und den Spielzug ausf�hrt
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* mark ist das Zeichen des Spielers (X/O)
* player ist ein int mit '1' f�r Spieler 1 oder '2' f�r Spieler 2
* playType gibt wer am zug ist mit (p/l/s) f�r (Person/Leichter Computergegner/Schwerer Computergegner)
*/
void gameMove(char board[3][3], char mark, int player, char playerType) {

    if (playerType == 's') {//Spielzug des Schweren Gegners
        printf("Spieler %d\n", player);
        kiHard(board, mark);
    }
    else if (playerType == 'l')//Spielzug des leichten Gegners
    {
        printf("Spieler %d\n", player);
        kiSimple(board, mark);
    }
    else//Spielzug einer Person
    {
        playerMove(board, mark, player);
    }


}
