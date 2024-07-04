#include <stdlib.h>
#include <stdio.h>
#include "boardHeader.h"
#include "spielzugHeader.h"

int main() {

    char board[3][3] = { '-', '-', '-', '-', '-', '-', '-', '-', '-' };
    char tmpWinner;
    char reply;
    char player1 = 'p', player2;
    char gameHistory[] = "Zuege in vergangen Spielen:\n\n";
    int p1Win = 0, p2Win = 0, pDraw = 0, moves1 = 0, moves2 = 0;
    int moves1All = 0, moves2All = 0;
    int gameCount = 1;
    int clean;
    int scanR;
    int games = 0;


    int* gameMoves1 = malloc(1 * sizeof(int));
    int* gameMoves2 = malloc(1 * sizeof(int));

    printf("-----------------------------\n\n");
    printf("TicTacToe\n\n");


    while (1) {//Schleife solange gespielt wird 

        printf("Auswahl des Mitspielers\n\n");
        printf("p -Person\nl -Leichter Computergegner\ns -Schwerer Computergegner\n\n");


        while (1) { //Abfrage gegen welchen Gegener gespielt wird
            printf("Auswahl fuer Spieler 2 'O' (p/l/s): \n");
            scanR = scanf_s(" %c", &player2, 1);
            if (scanR < 1) {
                printf("Keine gueltige Eingabe\n");
                scanf_s("%d", &clean);
            }
            else if ((player2 == 'p') | (player2 == 'l') | (player2 == 's')) {
                break;
            }
            else {
                printf("Kein verfuegbarer Spieler typ\n");
            }
        }

        resetBoard(board);
        printf("-----------------------------\n\n");
        printf("Ziffern der Felder:\n\n");
        drawBoardN(board);
        printf("--------Start der Runde------\n");
        drawBoard(board);
        while (1)  //Schleife einens Spiels
        {

            gameMove(board, 'X', 1, player1);     //Spielzug von Spieler 1
            drawBoard(board);                     //Spielbrett wird ausgegeben
            moves1++;                             //Z�hlt die Z�ge von Spieler 1
            if (freeSlots(board) == 0) {          //�berpr�fen ob platz auf dem Board, anstonsten ist es ein unentschieden 
                                                  //Ein Unendtschieden kann nur im Zug von Spieler 1 entstehen
                printf("\n");
                printf("Unentschieden\n");
                printf("\n");
                pDraw++;                          //Z�hlt die unentschieden
                break;                            //beendet d�e Schleife des Spiels
            }

            tmpWinner = winningCondition(board);  //�berpr�fen ob ein Zeichen dreimal in einer Reihe/Zeile/diagonalen vorkommt
            if (tmpWinner == 'X') {               //Nach einem Zug von 'X' kann nur 'X' gewinnen. tmpWinner gibt '-' bei keinem Gewinner zur�ck
                drawBoard(board);
                printf("\n");
                printf("Spieler 1 hat gewonnen \n");
                printf("\n");
                p1Win++;                          //Z�hlt die gewonnen Spiele von Spieler 1
                break;                            //beendet d�e Schleife des Spiels
            }
            //Spielablauf von Spieler 2 analog zu Spieler 1 
            gameMove(board, 'O', 2, player2);
            drawBoard(board);
            moves2++;
            tmpWinner = winningCondition(board);
            if (tmpWinner == 'O') {
                drawBoard(board);
                printf("\n");
                printf("Spieler 2 hat gewonnen \n");
                printf("\n");
                p2Win++;
                break;
            }
        }

        //Spiechern und Ausgeben der Z�ge der Spieler
        gameMoves1[games] = moves1;
        gameMoves2[games] = moves2;


        moves1All += moves1;
        moves2All += moves2;

        printf("\nZuege im Spiel:\n\n");
        printf("Spiel  | Spieler 1 | Spieler 2\n");

        for (int i = 0; i <= games; i++) {
            printf("Spiel %d:    %d        %d\n", (i + 1), gameMoves1[i], gameMoves2[i]);
        }

        games++;
        gameMoves1 = realloc(gameMoves1, (games + 1) * sizeof(int));
        gameMoves2 = realloc(gameMoves2, (games + 1) * sizeof(int));

        printf("insgesamt:  %d        %d\n", moves1All, moves2All);
        printf("\n");

        moves1 = 0;
        moves2 = 0;
        //Statistiken der gewonnen/verlorenen/unentschiedenen Spiele
        printf("-----------------------------");
        printf("\nStats:\n\n");
        printf("Spieler 1:\n\n");
        printf("Gewonnen: %d\n", p1Win);
        printf("Verloren: %d\n", p2Win);
        printf("Unentschieden: %d\n\n", pDraw);
        printf("Spieler 2:\n\n");
        printf("Gewonnen: %d\n", p2Win);
        printf("Verloren: %d\n", p1Win);
        printf("Unentschienden: %d\n\n", pDraw);

        while (1) { //Abfrage,einlesen und pr�fen, ob ein neues Spiel gestartet werden soll
            printf("Neues Spiel starten?(j/n): ");
            scanR = scanf_s(" %c", &reply, 1);
            if (scanR < 1) {
                printf("Keine gueltige Eingabe\n");
                scanf_s("%d", &clean);
            }
            else if ((reply == 'j') | (reply == 'n')) {
                break;
            }
            else {
                printf("Kein gueltige Auswahl\n");
            }
        }

        printf("\n");
        if (reply == 'n') {//Spiel beenden
            break;
        }
    }
    free(gameMoves1);
    free(gameMoves2);
    return 0;
}
