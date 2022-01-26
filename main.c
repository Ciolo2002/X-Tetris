#include <stdio.h>
#include <stdlib.h>
#include "tetralib.h"


/* LISTA DEI BUG/COSE DA FARE:
 *  1. Se non riesco a posizionare un tetramino perchè vado fuori a (dx, sx) il contatore di quel dato tetramino si decrementa: non deve decrementarsi
 *  2. testare il funzionamento della vittoria grazie ai punti
 *  3.  abbellire le stampe del campo
 *  4. mettere in una funzione quello che che trovi tra ////////////////// e fare anche un altra funnzione per la stampa del logo
 *  5. sistemare la documentazione secondo gli standard Doxygen (Spanò ha scritto una mail a riguardo dove indica dove andare a vedere come si fa a commentare )
 *  6. Segnalare all'utente che la sua mossa non è valida e quindi va ripetuta (correlato al punto 1.)
 *  7. Distinguere visivamente (colori o testo diverso) chi sta giocando
 *  8. Scelta randomica dei tetramini: non più scelta manuale-> il programma ti fornisce un tetramino random tra i disponibili e tu puoi solo scegliere come girarlo e dove metterlo
 *  9. implementare la cpu posiziona random: occhio ai casi limite anche lei deve poter ripetere la mossa se va fuori a destra e sinistra
 *  10. togliere commenti inutili e sopratutto quelli fatti con //
 *  11. Fare la relazione*/

int main() {
    int i, j, win = 0, lose = 0, rotation_selection, colonna, player_selector = 0;
    int looser = 0;
    int cnt_rows_deleted = 0;
    int *avaiable_tetramini;
    tetramino_t da_inserire = {0, 0, {0}};
    int game_type;
    char type_selection;
    game_t game;


    player_t empty_player = {0, {0},0};


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






//////////////////
    if (game_type != 1 && game_type != 2 && game_type != 3) {
        printf(" La modalita' %d arriverà presto!!", game_type);
        exit(0);
    }

    avaiable_tetramini=(int*)malloc(sizeof(int)*TETRAMINO_TYPES);
    if(avaiable_tetramini==NULL){
        exit(EXIT_FAILURE);
    }
    if (game_type == 1) {
        game.players = (player_t *) malloc(sizeof(player_t));
        if(game.players==NULL){
            exit(EXIT_FAILURE);
        }
        game.players[0] = empty_player;
        for(i=0;i<TETRAMINO_TYPES;i++){
            avaiable_tetramini[i]=n_tetramini_per_type;
        }
    } else {
        game.players = (player_t *) malloc(sizeof(player_t) * 2);
        if(game.players==NULL){
            exit(EXIT_FAILURE);
        }
        game.players[0] = empty_player;
        game.players[1] = empty_player;

        for(i=0;i<TETRAMINO_TYPES;i++){
            avaiable_tetramini[i]=n_tetramini_per_type*2;
        }
    }

//////////////////





    while (1) {



        /////////////////////////////
        looser = youLose(&game.players[player_selector],avaiable_tetramini);
        if (looser == 0) {

            if (game_type != 1) {
                if (game.players[0].points == game.players[1].points) {
                    printf("\nPareggio");
                } else if (game.players[0].points > game.players[1].points) {
                    printf("\nHa vinto il giocatore 1");
                } else {
                    printf("\nHa vinto il giocatore 2");
                }
            }
            free(game.players);
            exit(0);
        }
        /////////////////////////////



        /*ENTRAMBI DOVREBBERO PESCARE DALLO STESSO INSIEME DI TETRAMIMI: WORKAROUND -> COPIO I TETRAMIINI DI UNO NELL'ALTRO */
        printf("TETRAMINI A DISPOSIZIONE: \n");
        /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */
        print_tetramini('i', avaiable_tetramini[0]);
        print_tetramini('j', avaiable_tetramini[1]);
        print_tetramini('l', avaiable_tetramini[2]);
        print_tetramini('o', avaiable_tetramini[3]);
        print_tetramini('s', avaiable_tetramini[4]);
        print_tetramini('t', avaiable_tetramini[5]);
        print_tetramini('z', avaiable_tetramini[6]);

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
            if (getLastTetramino(&da_inserire, type_selection, &game.players[player_selector],avaiable_tetramini) != 0) {
                da_inserire = edit_tetramino(type_selection, rotation_selection, &game.players[player_selector],
                                             da_inserire);
                if (exception_width(&da_inserire, colonna) == 0) {
                    addTetramino(&da_inserire, game.players[player_selector].field, colonna);
                    game.players[player_selector].deleted_rows = (deleteRows(game.players[player_selector].field));
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


            /* creare una struct giocatore e fare in modo che abbia come attributi il punteggio e il "proprio campo da gioco"
              questo perchè dobbiamo tenere conto dei punti e oltretutto ci sono due giocatori che hanno due campi da gioco distinti */

        }

    }
    printf("Fine");
    return 0;
}





