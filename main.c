
#include <stdio.h>
#include <stdlib.h>

#define WEIGHT 10
#define HEIGHT 15

typedef struct tetramino{
    char type;
    int rotation;
}tetramino_t;




void add_tetraminio(char type, int rotation){
        if(type!='i'&&type!='z'&&type!='t'&&type!='s'&&type!='l'&&type!='o'&&type!='j'){
            printf("\nSelezione non valida\n");
            return;
        }
        if(rotation<1 || rotation >4) {
            printf("\nRotazione non valida\n");
            return;
        }
}

/**
 * stampa il capo di gioco
 * @param matrix
 */


void print_field( char matrix[HEIGHT][WEIGHT]){
    int i,j;

    for(i = 0; i < WEIGHT; i++)
        printf("%d\t", i);
    printf("\n\n\n");

    for(i = 0; i < HEIGHT; ++i){
        for(j = 0; j < WEIGHT; j++){
            printf("%c\t", matrix[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");
    for(i = 0; i < WEIGHT; i++)
        printf("%d\t", i);

}

/**
 * dato un array di tetramini assegna il tipo e inizializza a 0 la rotazione
 * @param v
 * @param size
 * @param type
 * @return
 */
tetramino_t* assign_values(tetramino_t *v, int size, char type){
    int i;
    for(i = 0; i< size; i++){
        v->type = type;
        v->rotation = 0;
    }

    return v;
}



void print_array(tetramino_t *v, int size){
    printf("\n\n");
    int i;
    for(i = 0; i < size; i++){
        printf("%c %d %d\n", v->type, v->rotation, i);
    }
}


/**
 * Funzione che stampa la forma di un tetrsamino e quanti te ne restano a disposizione
 * @param type
 * @param size
 *
 */


void print_tetramini(int type, int size){
    switch(type){
        case 1:
            printf("# # # #\t: %d\n\n", size);
            break;

        case 2:
            printf("#\n"
                   "# # #\t: %d\n\n", size);
            break;
        case 3:
            printf("\t#\n"
                     "# # #\t: %d\n\n", size);
            break;
        case 4:
                printf("# #\n"
                       "# #\t\t: %d\n\n", size);
            break;
        case 5:
                printf("  # #\n"
                       "# #\t\t: %d\n\n", size);
            break;
        case 6:
            printf("  #\n"
                   "# # #\t: %d\n\n", size);
            break;
        case 7:
            printf("# #\n"
                   "  # #\t: %d\n\n", size);
            break;
    }
}

//TODO: ruotare i tetramini
//TODO: posizionare i tatrmini
//TODO: decrementare il numero di tetramini a disposizione


int main() {
    int i, j, n_tetramini = 20, win = 0, lose = 0, rotation_selection;
    char type_selection;
    int i_size = n_tetramini, j_size = n_tetramini, l_size = n_tetramini, o_size = n_tetramini, s_size = n_tetramini, t_size = n_tetramini, z_size = n_tetramini;

    /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */



    tetramino_t *i_type = malloc(n_tetramini * sizeof(*i_type));
    tetramino_t *j_type = malloc(n_tetramini * sizeof(*j_type));
    tetramino_t *l_type = malloc(n_tetramini * sizeof(*l_type));
    tetramino_t *o_type = malloc(n_tetramini * sizeof(*o_type));
    tetramino_t *s_type = malloc(n_tetramini * sizeof(*s_type));
    tetramino_t *t_type = malloc(n_tetramini * sizeof(*t_type));
    tetramino_t *z_type = malloc(n_tetramini * sizeof(*z_type));



    assign_values(i_type, n_tetramini, 'i');
    assign_values(j_type, n_tetramini, 'j');
    assign_values(l_type, n_tetramini, 'l');
    assign_values(o_type, n_tetramini, 'o');
    assign_values(s_type, n_tetramini, 's');
    assign_values(t_type, n_tetramini, 't');
    assign_values(z_type, n_tetramini, 'z');

    char field[HEIGHT][WEIGHT];
    for(i = 0; i < HEIGHT; ++i){
        for(j = 0; j < WEIGHT; j++){
            field[i][j] = 'x';
        }
    }

    /* prove
    print_array(i_type, n_tetramini);
    print_array(j_type, n_tetramini);
    print_array(l_type, n_tetramini);
    print_array(o_type, n_tetramini);
    print_array(s_type, n_tetramini);
    print_array(t_type, n_tetramini);
    print_array(v_type, n_tetramini);

    */

    /* TETRAMINI

    printf("\n--------- TETRAMINI: ---------\n\n");

    for(i = 1; i < 8; i++){
        printf("Tetramino numero %d:", i);
        printf("\n");
        print_tetramino(i);
        printf("\n");
    }*/

    /* CAMPO DA GIOCO  */
   /* while(win == 0 && lose == 0){*/
        printf("TETRAMINI A DISPOSIZIONE: \n");

        print_tetramini(1, i_size);
        print_tetramini(2, j_size);
        print_tetramini(3, l_size);
        print_tetramini(4, o_size);
        print_tetramini(5, s_size);
        print_tetramini(6, t_size);
        print_tetramini(7, z_size);

        printf("\n\n------------ GAME FIELD: ------------\n\n");



        /* SELEZIONE TETRAMINO  */



        print_field(field);

        printf("\n\n\nSeleziona un tetramino (inserisci un carattere tra i, j, l, o, s, t, z): ");
        scanf("%c", &type_selection);
        printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
        scanf("%d", &rotation_selection);
        add_tetraminio(type_selection,rotation_selection);




    /* }*/




    return 0;

}


