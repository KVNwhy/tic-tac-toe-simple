#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "spielerKIHeader.h"

/*
* F�hrt den Spielzug des leichten Computergegner mittels Zufallszahlen aus.
* Um gerade zu ende Ende eines Spiels die Laufszeit zu begrenzen wird dieser Weg h�hstens 10 mal versucht.
* Ansonsten wird das n�chste freie Feld gew�hlt
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* mark ist das Zeichen des Computers (X/O)
*
* return '0' sobald der Zug gemacht wurde
*/

int kiSimple(char board[3][3], char mark) {

    time_t t;
    int randomFeld = 0;
    int check = 0;
    int attempt = 0;

    srand((unsigned)time(&t));
    randomFeld = (rand() % 9) + 1;
    printf("\nZug von leichter KI \n");

    while ((check != 1) & (attempt <= 10)) { // 10 versuche um Zuf�llig ein freies Feld zufinden

        srand((unsigned)time(&t));
        randomFeld = (rand() % 9) + 1; //erzeugt eine Zufallszahl
                                      // durch mod9 werden es nur Zahlen zwischen 0-8 und durch +1 zu 1-9
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (3 * i + j + 1 == randomFeld) { //rechnet die Zahl zwischen 1-9 in die indezes i und j um
                    if (board[i][j] == '-') { // check ob des Feld frei ist

                        board[i][j] = mark;
                        check = 1;
                        break;

                    }
                }
            }
        }

        attempt++;

    }

    while (check != 1) { //Falls in 10 versuchen kein feld gefunden wird
                         //Wird durch das Board gelaufen und das erste freie Feld genommen
        randomFeld++;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {             
                if (board[i][j] == '-') {
                    board[i][j] = mark;
                    check = 1;
                    return 0;
                }
            }
        }
    }

    return 0;
}