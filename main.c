#include <stdio.h>
#include <stdlib.h>
#include "tetralib.h"


int main() {
    int i, j, win = 0, lose = 0, rotation_selection, colonna, giallo = 0, player_selector = 0;
    int ciao = 0;
    int cnt_rows_deleted = 0;
    tetramino_t da_inserire = {0, 0, {0}};
    int game_type;
    char type_selection;
    game_t game;


    player_t empty_player = {0, {0}, {n_tetramini_per_type}};
    player_initializer(&empty_player);

    printf("    ▄       ▄               ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ \n");
    printf("   ▐░▌     ▐░▌             ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌\n");
    printf("    ▐░▌   ▐░▌               ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ \n");
    printf("     ▐░▌ ▐░▌                    ▐░▌     ▐░▌               ▐░▌     ▐░▌       ▐░▌     ▐░▌     ▐░▌          \n");
    printf("      ▐░▐░▌    ▄▄▄▄▄▄▄▄▄▄▄      ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄      ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌     ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄ \n");
    printf("       ▐░▌    ▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌\n");
    printf("      ▐░▌░▌    ▀▀▀▀▀▀▀▀▀▀▀      ▐░▌     ▐░█▀▀▀▀▀▀▀▀▀      ▐░▌     ▐░█▀▀▀▀█░█▀▀      ▐░▌      ▀▀▀▀▀▀▀▀▀█░▌\n");
    printf("     ▐░▌ ▐░▌                    ▐░▌     ▐░▌               ▐░▌     ▐░▌     ▐░▌       ▐░▌               ▐░▌\n");
    printf("    ▐░▌   ▐░▌                   ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄      ▐░▌     ▐░▌      ▐░▌  ▄▄▄▄█░█▄▄▄▄  ▄▄▄▄▄▄▄▄▄█░▌\n");
    printf("   ▐░▌     ▐░▌                  ▐░▌     ▐░░░░░░░░░░░▌     ▐░▌     ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌\n");
    printf("    ▀       ▀                    ▀       ▀▀▀▀▀▀▀▀▀▀▀       ▀       ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀ \n");
    printf("                                                                                                         \n");

    printf("\n\n\t\t\t\t\t\t\t  SINGLE PLAYER    - press 1"
           "\n\n\t\t\t\t\t\t\t  TWO PLAYERS      - press 2"
           "\n\n\t\t\t\t\t\t\t  PLAY AGAINST CPU - press 3\n"); //TODO per il momento per i test facciamo solo 1 e/o 2, quando sarà ora faremo la cpu

    scanf(" %d", &game_type);
    printf("\033[2J");



    if (game_type != 1 && game_type != 2 && game_type != 3) {
        printf(" La modalita' %d arriverà presto!!", game_type);
        exit(0);
    }

    if (game_type == 1) {
        game.players = (player_t *)malloc(sizeof(player_t));
        game.players[0] = empty_player;
    } else {
        game.players = (player_t *)malloc(sizeof(player_t) * 2);
        game.players[0] = empty_player;
        game.players[1] = empty_player;
    }


    while (/*win == 0 && lose == 0*/ giallo < 50) {


        youLose(&game.players[player_selector]);
        printf("TETRAMINI A DISPOSIZIONE: \n");
        /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */
        print_tetramini('i', game.players[player_selector].avaiable_tetramini[0]);
        print_tetramini('j', game.players[player_selector].avaiable_tetramini[1]);
        print_tetramini('l', game.players[player_selector].avaiable_tetramini[2]);
        print_tetramini('o', game.players[player_selector].avaiable_tetramini[3]);
        print_tetramini('s', game.players[player_selector].avaiable_tetramini[4]);
        print_tetramini('t', game.players[player_selector].avaiable_tetramini[5]);
        print_tetramini('z', game.players[player_selector].avaiable_tetramini[6]);

        printf("\n\n------------ GAME FIELD: ------------\n\n");
        /* SELEZIONE TETRAMINO    */



        printField(game.players[player_selector].field);

        printf("\nSCORE: %d", game.players[player_selector].points);
        printf("\nDELETED ROWS: %d", game.players[player_selector].deleted_rows);
        game.players[player_selector].deleted_rows = 0;




            printf("\n\n\nSeleziona un tetramino (inserisci un carattere tra i, j, l, o, s, t, z): ");
            scanf(" %c", &type_selection);
            printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
            scanf(" %d", &rotation_selection);
            printf("\nSeleziona la colonna dove posizionare il tetramino (inserisci un numero tra 0 e 9): ");
            scanf(" %d", &colonna);
            if (exception_t_r(type_selection, rotation_selection) == 0) {
                if (getLastTetramino(&da_inserire, type_selection, &game.players[player_selector])!= 0) {
                    da_inserire = edit_tetramino(type_selection, rotation_selection, &game.players[player_selector], da_inserire);
                    if (exception_width(&da_inserire, colonna) == 0) {
                        addTetramino(&da_inserire, game.players[player_selector].field, colonna);
                        game.players[player_selector].deleted_rows = (deleteRows(game.players[player_selector].field));
                        if(game.players[player_selector].deleted_rows!=0){
                            increment_points(&game.players[player_selector].points, &game.players[player_selector].deleted_rows);
                            if(game_type!=1){
                                if(player_selector==1){
                                    swapRows(game.players[player_selector].deleted_rows, &game.players[0]);
                                }else{
                                    swapRows(game.players[player_selector].deleted_rows, &game.players[1]);
                                }
                            }
                        }
                        player_selector = changePlayer(game_type, player_selector);
                    }
                }


            /* todo creare una struct giocatore e fare in modo che abbia come attributi il punteggio e il "proprio campo da gioco"
              questo perchè dobbiamo tenere conto dei punti ed oltretutto ci sono due giocatori che hanno due campi da gioco distinti */

        }

    }
    printf("Fine");
    return 0;
}





