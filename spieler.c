#include <stdlib.h>
#include <stdio.h>
#include "spielerKIHeader.h"

/*
* F�hrt den Spielzug eines Spielers durch
* Der Spieler muss eingeben welches Feld er ausw�hlt
* und die Eingabe wird auf g�ltigkeit gepr�ft und Ausgeben
*
* board[3][3] ist das Spielfeld indem alle bisheringen gespielten Zeichen Gespeichtert sind
* mark ist das Zeichen des Spielers (X/O)
* player ist ein int mit '1' f�r Spieler 1 oder '2' f�r Spieler 2
*/
void playerMove(char board[3][3], char mark, int player) {

    int number = 0;
    int check = 0;
    int scanResult;

    printf("Zug von Spieler %d \n", player);

    while (check != 1) {


        while (1) {//Scanen der Eingabe und �berpr�fen der G�ltigkeit
            printf("Freies Feld waehlen: \n");
            scanResult = scanf_s(" %d", &number);
            if (scanResult < 1) {
                printf("Keine gueltige Eingabe\n");
                char del;
                scanf_s("%c", &del, 1);
            }
            else if ((number <= 9) & (number >= 1)) {
                break;
            }
            else {
                printf("Kein Feld mit dieser Nummer\n");
            }
        }


        for (int i = 0; i < 3; i++) { //�berpr�ft ob das gew�hlte Feld frei ist
            for (int j = 0; j < 3; j++) {
                if (3 * i + j + 1 == number) {
                    if (board[i][j] == '-') {

                        board[i][j] = mark;
                        check = 1;
                        break;

                    }
                }
            }
        }
        if (check != 0) {
            printf("Feld nicht frei\n");
        }
    }

}