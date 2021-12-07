
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  /* SE SI USA CLION INSERIRE NEL FILE CMakeList.txt --> target_link_libraries(X_Tetris_first PRIVATE m)  */

#define WIDTH 10
#define HEIGHT 15
#define TETRAMINO_LATO 4
#define n_tetramini 20


int i_size = n_tetramini;
int j_size = n_tetramini;
int l_size = n_tetramini;
int o_size = n_tetramini;
int s_size = n_tetramini;
int t_size = n_tetramini;
int z_size = n_tetramini;


int I[4][4] = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
};

int J[4][4] = {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {2, 2, 0, 0}
};

int L[4][4] = {
        {0, 0, 0, 0},
        {3, 0, 0, 0},
        {3, 0, 0, 0},
        {3, 3, 0, 0}
};

int O[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {4, 4, 0, 0},
        {4, 4, 0, 0}
};

int S[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 5, 5, 0},
        {5, 5, 0, 0}
};

int T[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {6, 6, 6, 0},
        {0, 6, 0, 0}
};

int Z[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {7, 7, 0, 0},
        {0, 7, 7, 0}
};


typedef struct tetramino {
    char type;
    int rotation;
    int pieces[TETRAMINO_LATO][TETRAMINO_LATO];
} tetramino_t;


/**
 * Porta i valori del tetramino giù di 1 riga nella matrice che lo contiene
 * @param tetramino
 * @return
 */
tetramino_t pushTetraminoDown(tetramino_t tetramino) {
    int swapCount = 1;
    int col = 0, row = 0, j = 0, check = 0;
    int temp[TETRAMINO_LATO];
    for (col = TETRAMINO_LATO - 1; col > 0; col--) {
        for (row = 0; row < TETRAMINO_LATO; row++) {
            temp[row] = tetramino.pieces[col][row];
            tetramino.pieces[col][row] = tetramino.pieces[col - 1][row];
            tetramino.pieces[col - 1][row] = temp[row];
        }
    }


    return tetramino;
}


tetramino_t pushTetraminoLeft(tetramino_t tetramino) { /* TODO debuggare: non mi mantiene la forma originale del tetramino */
    int i, j;
    int tmp[TETRAMINO_LATO][TETRAMINO_LATO];

    for(i = 0; i < TETRAMINO_LATO ; i++){
        for(j = 0; j < TETRAMINO_LATO; j++){
            tmp[i][j] = tetramino.pieces[i][j + 1];
        }
    }

    for(i = 0; i < TETRAMINO_LATO; i++){
        for(j = 0; j < TETRAMINO_LATO; j++){
            tetramino.pieces[i][j] = tmp[i][j];
        }
    }


    return tetramino;
}


/**
 * Ritorna 1 se tutta l'ultima riga del tetramino è composta di soli 0
 * @param tetramino
 * @return
 */
int checkEmptyLastRow(tetramino_t tetramino) {
    int bool = 1, cnt;
    for (cnt = 0; cnt < TETRAMINO_LATO; cnt++) {
        if (tetramino.pieces[TETRAMINO_LATO - 1][cnt] != 0)
            bool = 0;

    }
    return bool;

}


int checkEmptyLeftColumn(tetramino_t tetramino) {
    int bool = 1, cnt;
    for (cnt = 0; cnt < TETRAMINO_LATO; cnt++) {
        if (tetramino.pieces[cnt][0] != 0)
            bool = 0;

    }
    return bool;

}

tetramino_t rotateTetramino(tetramino_t tetramino1) {
    tetramino_t temp = tetramino1;
    int i, j;
    int rotation = tetramino1.rotation;
    if (tetramino1.type == 'o' || (tetramino1.rotation == 1)) {
        return tetramino1;
    }
    /* se il tetramino è di tipo I, S o Z e la rotazione è 3 ritorna il tetramino di partenza */
    if ((tetramino1.type == 'i' || tetramino1.type == 's' || tetramino1.type == 'z') && tetramino1.rotation == 3) {
        return tetramino1;
    }
    while (rotation > 1) {
        for (i = 0; i < TETRAMINO_LATO; i++) {
            for (j = 0; j <
                        TETRAMINO_LATO; j++) { /*TODO debuggare, edit: debuggato e tolto un cicli per migliore le prestazioni */

                temp.pieces[i][j] = tetramino1.pieces[TETRAMINO_LATO - j - 1][i];
            }
        }
        rotation--;
        tetramino1 = temp;
    }
    return tetramino1;
}

/**
 * stampa l'effettivo tetramino, si può usare anche solo per fare i test e poi per giocare usariamo l'altra print che è più carina.
 * @param tetramino
 */
void print_realTetramino(tetramino_t tetramino) {
    int i, j;
    for (i = 0; i < TETRAMINO_LATO; i++) {
        for (j = 0; j < TETRAMINO_LATO; j++) {
            printf("%d", tetramino.pieces[i][j]);
        }
        printf("\n");
    }
}
/*
 * Funzione che crea effettivamente il tetramino e decrementa la quantità di tetramini a disposizione
 */

tetramino_t add_tetramino(char type, int rotation) {
    tetramino_t da_inserire;
    int isOkay = 1, i, j;
    if (type != 'i' && type != 'z' && type != 't' && type != 's' && type != 'l' && type != 'o' && type != 'j') {
        printf("\nSelezione non valida\n");
        exit(0);
    }
    if (rotation < 1 || rotation > 4) {
        printf("\nRotazione non valida\n");
        exit(0);
    }
    /*da_inserire = get_LastTetramino(type)  ;*/

    switch (type) {
        case 'i':
            if(i_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = I[i][j];
                }
            }
            --i_size;

            break;
        case 'j':
            if(j_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = J[i][j];
                }
            }

            --j_size;
            break;
        case 'l':
            if(l_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = L[i][j];
                }
            }

            --l_size;
            break;
        case 'o':
            if(o_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = O[i][j];
                }
            }

            --o_size;
            break;
        case 's':
            if(s_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = S[i][j];
                }
            }

            --s_size;
            break;
        case 't':
            if(t_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = T[i][j];
                }
            }

            --t_size;
            break;
        case 'z':
            if(z_size == 0){
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            for(i = 0; i < TETRAMINO_LATO; i++){
                for(j = 0; j < TETRAMINO_LATO; j++){
                    da_inserire.pieces[i][j] = Z[i][j];
                }
            }

            --z_size;
            break;
        default:
            printf("Rotto");
            break;
    }

    if(isOkay == 0){
        exit(0);
    }

    da_inserire.type = type;
    da_inserire.rotation = rotation;
    da_inserire = rotateTetramino(da_inserire);

    print_realTetramino(da_inserire);
    printf("\n");

    while (checkEmptyLastRow(da_inserire)) { /*finchè l'ultima la più in basso della matrice è fatta di soli 0 porto il tetramino in basso*/
        da_inserire = pushTetraminoDown(da_inserire);
    }


    print_realTetramino(da_inserire);
    printf("\n");


    while(checkEmptyLeftColumn(da_inserire)){
        da_inserire= pushTetraminoLeft(da_inserire);
    }



    return da_inserire;
}

/**
 * stampa il campo di gioco
 * @param matrix
 */
void print_field(int matrix[HEIGHT][WIDTH]) {
    int i, j;

    for (i = 0; i < WIDTH; i++)
        printf("%d\t", i);
    printf("\n\n\n");

    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; j++) {
            switch (matrix[i][j]) {
                case 0:
                    printf("x\t");
                    break;
            }

        }
        printf("\n\n");
    }
    printf("\n");
    for (i = 0; i < WIDTH; i++)
        printf("%d\t", i);

}

/**
 * Funzione che stampa la forma di un tetrsamino e quanti te ne restano a disposizione
 * @param type
 * @param size
 *
 */
void print_tetramini(char type, int size) {
    switch (type) {
        case 'i':
            printf("# # # #\t: %d\n\n", size);
            break;

        case 'j':
            printf("#\n"
                   "# # #\t: %d\n\n", size);
            break;
        case 'l':
            printf("\t#\n"
                   "# # #\t: %d\n\n", size);
            break;
        case 'o':
            printf("# #\n"
                   "# #\t\t: %d\n\n", size);
            break;
        case 's':
            printf("  # #\n"
                   "# #\t\t: %d\n\n", size);
            break;
        case 't':
            printf("  #\n"
                   "# # #\t: %d\n\n", size);
            break;
        case 'z':
            printf("# #\n"
                   "  # #\t: %d\n\n", size);
            break;
    }
}

//TODO: ruotare i tetramini
//TODO: posizionare i tatrmini
//TODO: decrementare il numero di tetramini a disposizione


int main() {
    int i, j, win = 0, lose = 0, rotation_selection;
    int field[HEIGHT][WIDTH];
    char type_selection;

/* CAMPO DA GIOCO  */

    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; j++) {
            field[i][j] = 0;
        }
    }

    /* while(win == 0 && lose == 0){*/
printf("Ciao\n");
    printf("TETRAMINI A DISPOSIZIONE: \n");

    /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */

    print_tetramini('i', i_size);
    print_tetramini('j', j_size);
    print_tetramini('l', l_size);
    print_tetramini('o', o_size);
    print_tetramini('s', s_size);
    print_tetramini('t', t_size);
    print_tetramini('z', z_size);

    printf("\n\n------------ GAME FIELD: ------------\n\n");



    /* SELEZIONE TETRAMINO    */



    print_field(field);

    printf("\n\n\nSeleziona un tetramino (inserisci un carattere tra i, j, l, o, s, t, z): ");
    scanf("%c", &type_selection);
    printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
    scanf("%d", &rotation_selection);
    tetramino_t inserito = add_tetramino(type_selection, rotation_selection);

    print_realTetramino(inserito) ;
    /*TODO fare la funzione che sposta il tetramino il più in basso a sx possibile  */

    /* }*/


    return 0;

}
