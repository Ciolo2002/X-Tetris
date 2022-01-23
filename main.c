#include <stdio.h>
#include <stdlib.h>
#include "tetralib.h"



int main() {
    int i, j, win = 0, lose = 0, rotation_selection, colonna, giallo = 0;
    int cnt_rows_deleted = 0 ;
    tetramino_t da_inserire;
    int game_type;
    char type_selection;
    player_t player_1 = {0, {0}, {n_tetramini_per_type}};
    player_t player_2 = {0, {0}, {n_tetramini_per_type}};


    player_initzializer(&player_1);
    player_initzializer(&player_2);

    printf("WELCOME IN X-TETRIS !!!!!! \n Seleziona la modalita' di gioco:"
           " \n - 1 per giocare in single-player,"
           " \n - 2 per gioca in multi-player "
           "\n - 3 per giocare contro CPU\n"); //TODO per il momento per i test facciamo solo 1 e/o 2, quando sarà ora faremo la cpu

    scanf(" %d", &game_type);

    if (game_type != 1 && game_type != 2 && game_type != 3) {
        printf(" La modalita' %d arriverà presto!!", game_type);
        exit(0);
    } else {
        printf("OKAY LET'S GO!");
    }


    while (/*win == 0 && lose == 0*/ giallo < 50) {

        printf("TETRAMINI A DISPOSIZIONE: \n");

        /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */

        print_tetramini('i', player_1.tetramino_avibles[0]);
        print_tetramini('j', player_1.tetramino_avibles[1]);
        print_tetramini('l', player_1.tetramino_avibles[2]);
        print_tetramini('o', player_1.tetramino_avibles[3]);
        print_tetramini('s', player_1.tetramino_avibles[4]);
        print_tetramini('t', player_1.tetramino_avibles[5]);
        print_tetramini('z', player_1.tetramino_avibles[6]);

        printf("\n\n------------ GAME FIELD: ------------\n\n");
        /* SELEZIONE TETRAMINO    */



        print_field(player_1.field);

        printf("\nSCORE: %d",player_1.points);
        printf("\nDELETED ROWS: %d",cnt_rows_deleted);

        while (1) {

            printf("\n\n\nSeleziona un tetramino (inserisci un carattere tra i, j, l, o, s, t, z): ");
            scanf(" %c", &type_selection);
            printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
            scanf(" %d", &rotation_selection);
            printf("\nSeleziona la colonna dove posizionare il tetramino (inserisci un numero tra 0 e 9): ");
            scanf(" %d", &colonna);
            if (exception_t_r(type_selection, rotation_selection) == 0) {
                da_inserire = edit_tetramino(type_selection, rotation_selection, &player_1);
                if (exception_width(&da_inserire, colonna) == 0) {
                    addTetramino(&da_inserire, player_1.field, colonna);
                    break;
                }
            }

        }
        /* todo creare una struct giocatore e fare in modo che abbia come attributi il punteggio e il "proprio campo da gioco"
          questo perchè dobbiamo tenere conto dei punti ed oltretutto ci sono due giocatori che hanno due campi da gioco distinti */
        cnt_rows_deleted+= (deleteRows(player_1.field)) ;


        increment_points(&player_1.points, &cnt_rows_deleted);




        giallo++;


    }


    return 0;

}





