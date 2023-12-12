#include <stdio.h>
#define COLONNE 7
#define LINE 7

void printGame(const char board[LINE][COLONNE]);
void game(int* joueur, char board[LINE][COLONNE]);
int highestPos(int colonne,char board[LINE][COLONNE]);
int status(char board[LINE][COLONNE]);
int winner(char board[LINE][COLONNE]);

int main() {

    int joueur = 1;
    char gameboard[LINE][COLONNE] = {
            ' ',' ',' ',' ',' ',' ',' ',
            ' ',' ',' ',' ',' ',' ',' ',
            ' ',' ',' ',' ',' ',' ',' ',
            ' ',' ',' ',' ',' ',' ',' ',
            ' ',' ',' ',' ',' ',' ',' ',
            ' ',' ',' ',' ',' ',' ',' ',
    };

    game(&joueur, gameboard);

    return 0;
}

void printGame(const char board[LINE][COLONNE]) {
    printf("---------------\n| Puissance 4 |\n---------------\n  0   1   2   3   4   5   6");
    for(int i = 0; i < LINE-1; i++) {
        printf("\n+---+---+---+---+---+---+---+\n|");
        for(int j = 0; j < COLONNE; j++) {
            printf(" %c |", board[i][j]);
        }
    }
    printf("\n+---+---+---+---+---+---+---+\n  0   1   2   3   4   5   6\n");
}

void game(int* joueur, char board[LINE][COLONNE]) {
    char lettre = *joueur == 1 ? 'O' : 'X';
    int colonne = 0;

    printGame(board);
    printf("Joueur %d\nSur quelle colonne voulez vous poser votre pion ? ", *joueur);
    scanf("%d", &colonne);

    int pos = highestPos(colonne, board);

    if(pos == 404) {
        printf("La colonne que vous avez séléctionnée est remplie\n");
        game(joueur, board);
    } else {
        board[pos][colonne] = lettre;
        if(status(board) == 1) {
            printGame(board);
            printf("Le joueur %d a gagné !\n", *joueur);
        } else if(status(board) == 2) {
            printGame(board);
            printf("Aucun joueur n'a gagné, match nul !");
        } else {
            if (*joueur == 1) {
                *joueur = 2;
            } else {
                *joueur = 1;
            }
            game(joueur, board);
        }
    }
}

int highestPos(int colonne,char board[LINE][COLONNE]) {
    if(colonne < 0 || colonne > 6) return 404;
    for(int i = 0; i < LINE; i++) {
        if(board[i][colonne] != 32) {
            return i-1;
        }
    }
    return 404;
}

int status(char board[LINE][COLONNE]) {

    if(winner(board) == 1) {
        return 1;
    }

    int occ[COLONNE] = {0};
    for(int i = 0; i < LINE; i++) {
        for(int j = 0; j < COLONNE; j++) {
            if (board[i][j] != 32) {
                occ[j]++;
            }
        }
    }

    for(int k = 0; k < LINE; k++) {
        if(occ[k] < 6) {
            return 0;
        }
    }

    return 2;
}

int winner(char board[LINE][COLONNE]) {

    for(int i = 0; i < LINE; i++) {
        for(int j = 0; j < COLONNE; j++) {
            if(board[i][j] == 88 || board[i][j] == 79) {
                if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                    board[i][j] == board[i][j + 3]) {
                    if(j+1 > COLONNE || j+2 > COLONNE || j+3 > COLONNE) return 0;
                    return 1;
                }
                if (board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j] &&
                    board[i][j] == board[i - 3][j]) {
                    if(i-1 > LINE || i-2 > LINE || i-3 > LINE) return 0;
                    return 1;
                }
                if (board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] &&
                    board[i][j] == board[i - 3][j + 3]) {
                    if(i-1 > LINE || j+1 > COLONNE || i-2 > LINE || j+2 > COLONNE || i-3 > LINE || j+3 > COLONNE) return 0;
                    return 1;
                }
                if (board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] &&
                    board[i][j] == board[i - 3][j - 3]) {
                    if(i-1 > LINE || j-1 > COLONNE || i-2 > LINE || j-2 > COLONNE || i-3 > LINE || j-3 > COLONNE) return 0;
                    return 1;
                }
            }
        }
    }

    return 0;
}