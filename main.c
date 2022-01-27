#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetralib.h"

int main() {
    int i, rotation_selection, column, player_selector = 0, loser;
    int *available_tetramini;
    tetramino_t da_inserire = {0, 0, {0}};
    int game_type;
    char type_selection;
    game_t game;

    player_t empty_player = {0, {0},0};

    printLogo();

    printf("\n\n\t\t  SINGLE PLAYER    - press 1"
           "\n\n\t\t  TWO PLAYERS      - press 2"
           "\n\n\t\t  PLAY AGAINST CPU - press 3\n");

    scanf(" %d", &game_type);

    if (game_type != 1 && game_type != 2 && game_type != 3) {
        printf("%d mode: coming soon\n\n", game_type);
        exit(0);
    }

    available_tetramini=(int*)malloc(sizeof(int) * TETRAMINO_TYPES);
    if(available_tetramini == NULL){
        exit(EXIT_FAILURE);
    }
    if (game_type == 1) {
        game.players = (player_t *) malloc(sizeof(player_t));
        if(game.players==NULL){
            exit(EXIT_FAILURE);
        }
        game.players[0] = empty_player;
        for(i=0;i<TETRAMINO_TYPES;i++){
            available_tetramini[i]=n_tetramini_per_type;
        }
    } else{
        game.players = (player_t *) malloc(sizeof(player_t) * 2);
        if(game.players==NULL){
            exit(EXIT_FAILURE);
        }
        game.players[0] = empty_player;
        game.players[1] = empty_player;

        for(i=0;i<TETRAMINO_TYPES;i++){
            available_tetramini[i]= n_tetramini_per_type * 2;
        }
    }

    while (checkLose(game, player_selector, available_tetramini, game_type)) {

        if(game_type != 3 || player_selector == 0) {
            printf("\nAVAIABLE TETRAMINI: \n\n");
            /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */
            print_tetramini('i', available_tetramini[0]);
            print_tetramini('j', available_tetramini[1]);
            print_tetramini('l', available_tetramini[2]);
            print_tetramini('o', available_tetramini[3]);
            print_tetramini('s', available_tetramini[4]);
            print_tetramini('t', available_tetramini[5]);
            print_tetramini('z', available_tetramini[6]);

            printf("\n\n\n\n");

            printLogo();
            if (player_selector == 0) {
                printf("\n\t\t\t\t" ANSI_COLOR_RED  "PLAYER 1" ANSI_COLOR_RESET "\n");
            }
            else{
                printf("\n\t\t\t\t" ANSI_COLOR_BLUE "PLAYER 2" ANSI_COLOR_RESET "\n");
            }

            printField(game.players[player_selector].field);
            printf("\nSCORE: %d", game.players[player_selector].points);
            printf("\nDELETED ROWS: %d", game.players[player_selector].deleted_rows);
            game.players[player_selector].deleted_rows = 0;
        }

        if(game_type == 3 && player_selector == 1) {
            type_selection = randomType();
            rotation_selection = randomRotation();
            column = randomColumn();
        }
        else{
            printf("\n\n\nSELECT A TETRAMINO (ENTER A CHARACTER BETWEEN i, j, l, o, s, t, z): ");
            scanf(" %c", &type_selection);
            printf("\nSELECT THE ROTATION (ENTER A NUMBER BETWEEN 1, 2, 3, 4): ");
            scanf(" %d", &rotation_selection);
            printf("\nSELECT THE COLUMN WHERE YOU WANT TO INSERT THE TETRAMINO  (ENTER A NUMBER BETWEEN 0 AND 9): ");
            scanf(" %d", &column);
        }


        if (exception_t_r(type_selection, rotation_selection, game_type, player_selector) == 0) {
            if (getLastTetramino(&da_inserire, type_selection, &game.players[player_selector], available_tetramini, game_type, player_selector) != 0) {
                da_inserire = edit_tetramino(type_selection, rotation_selection, &game.players[player_selector],
                                             da_inserire);
                if (exception_width(&da_inserire, column, available_tetramini, game_type, player_selector) == 0) {
                    addTetramino(&da_inserire, game.players[player_selector].field, column, player_selector);
                    game.players[player_selector].deleted_rows = (deleteRows(game.players[player_selector].field));
                    if(game_type == 3 && player_selector == 1){
                        printf("\n");
                        printLogo();
                        printf( "\n\t\t\t\t" ANSI_COLOR_MAGENTA "CPU" ANSI_COLOR_RESET "\n" );
                        printField(game.players[player_selector].field);
                        printf("\n\n PRESS ENTER TO CONTINUE");
                        getchar();
                        getchar();
                    }
                    if (game.players[player_selector].deleted_rows != 0) {
                        increment_points(&game.players[player_selector].points,
                                         &game.players[player_selector].deleted_rows);
                        if (game_type != 1) {
                            if (player_selector == 1) {
                                swapRows(game.players[player_selector].deleted_rows, &game.players[0]);
                            } else {
                                swapRows(game.players[player_selector].deleted_rows, &game.players[1]);
                            }
                        }
                    }

                    player_selector = changePlayer(game_type, player_selector);
                }
            }
        }
    }
}





