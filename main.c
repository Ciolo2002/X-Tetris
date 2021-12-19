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


int deleteRows(int campo[15][10]);

typedef struct tetramino {
    char type;
    int rotation;
    int pieces[TETRAMINO_LATO][TETRAMINO_LATO];
} tetramino_t;


/**
 * Va a tutti gli effetti a piazzare il tetramino nel campo da gioco
 * @param pField
 * @param pTetramino
 * @param colonna
 * @param riga
 */
void place_tetrimino(int pField[HEIGHT][WIDTH], tetramino_t *pTetramino, int colonna, int riga) {
    int i, j, bool_placed = 0;
    for (i = TETRAMINO_LATO - 1; i >= 0; i--) {
        for (j = TETRAMINO_LATO - 1; j >= 0; j--) {
            if (pTetramino->pieces[i][j] != 0) {
                printf(" filed %d  tetramino %d \n", pField[riga][j + colonna], pTetramino->pieces[i][j]);
                pField[riga][j + colonna] = pTetramino->pieces[i][j];
                bool_placed = 1;
            }
        }
        if (bool_placed) { /** posizionamento della riga superiore del campo da gioco*/
            riga--;
        }
        bool_placed = 0;
    }
    printf("\n");
}


/**
 * ritorna maggiore lunghezza del tetramino che riceve in base alla sua rotazione attuale
 * @param pTetramino
 * @return
 */
int maxTetraminoWidth(tetramino_t *pTetramino) {
    int lunghezza_max_tetramino = 0, temp, i, j;
    for (i = 0; i < TETRAMINO_LATO; i++) {
        temp = 0;
        for (j = 0; j < TETRAMINO_LATO; j++) {
            if (pTetramino->pieces[i][j] != 0) {
                temp++;
            }
        }
        if (temp >= lunghezza_max_tetramino) {
            lunghezza_max_tetramino = temp;
        }
    }
    return lunghezza_max_tetramino;
}


/**
 * Controlla che la scelta del giocatore non porti fuori a destra o a sinistra il tetramino dal campo da gioco, poi
 * controlla se un tetramino ci sta nel campo da gioco ed eventalmete in quale riga andarlo a piazzare,
 * dopodichè una volta trovata la riga chiama place_tetramino e lo piazza oppure fa perdere il giocatore
 * @param da_inserire
 * @param field
 * @param col
 */
void addTetramino(tetramino_t *da_inserire, int field[HEIGHT][WIDTH], int col) {

    int lunghezza_max_tetramino, i, j, z, temp = -1, calcomagicoastrale = 0;
    lunghezza_max_tetramino = maxTetraminoWidth(da_inserire);
    if ((col + lunghezza_max_tetramino) > WIDTH || (col + lunghezza_max_tetramino) <= 0) {
        printf("Non puoi posizione un tetramino fuori dal campo di gioco!!!");
        exit(0); /* TODO: non terminare il programma ma far ripetere la scelta */
    }

    for (i = HEIGHT - 1; i >= 0; i--) { /*riga campo da gioco*/
        temp = -1;
        for (j = TETRAMINO_LATO - 1; j >= 0; j--) { /*riga tetramino*/
            for (z = TETRAMINO_LATO - 1; z >= 0; z--) { /*colonna tetramino*/
                calcomagicoastrale = (i - ((TETRAMINO_LATO - 1) - j));
                if (field[calcomagicoastrale][z + col] == 0 || da_inserire->pieces[j][z] == 0) {  /** controllo che l'intero tetramino ci sta all'interno del campo di gioco, se non ci sta controllo la riga superiore del campo da gioco */
                } else {
                    temp = i;
                }


                if (calcomagicoastrale < 0) { /* TODO: controllare che la riga 0 sia consentita, il giocatore deve perdere dalla -1 in su */
                    /** il giocatore ha sforato in altezza il campo da gioco quindi ha perso*/
                    printf("Sei arrivato in alto hai perso!!!");
                    exit(0);
                }
            }
        }
        if (temp == -1) { /** una volta trovata la riga dove posizionare il tetramino, lo vado effettivamente ad inserire nel campo da gioco*/
            place_tetrimino(field, da_inserire, col, i);
            return;
        }
    }
    place_tetrimino(field, da_inserire, col, i);
    return;

}


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

/**
 * Porta i valori del tetramino a sinistra di 1 riga nella matrice che lo contiene
 * @param tetramino
 * @return
 */
tetramino_t
pushTetraminoLeft(tetramino_t tetramino) {
    int i, j;
    int tmp[TETRAMINO_LATO][TETRAMINO_LATO] = {0};

    for (i = 0; i < TETRAMINO_LATO; i++) {
        for (j = 0; j < TETRAMINO_LATO; j++) {
            if (j + 1 < TETRAMINO_LATO) {  /* nel caso ad esempio  J 3 senza questo if si buggava */
                tmp[i][j] = tetramino.pieces[i][j + 1];
            }
        }
    }
    for (i = 0; i < TETRAMINO_LATO; i++) {
        for (j = 0; j < TETRAMINO_LATO; j++) {
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
    int cnt;
    for (cnt = 0; cnt < TETRAMINO_LATO; cnt++) {
        if (tetramino.pieces[TETRAMINO_LATO - 1][cnt] != 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * Ritorna 1 se la prima colonna del tetramino è composta di soli 0
 * @param tetramino
 * @return
 */
int checkEmptyLeftColumn(tetramino_t tetramino) {
    int cnt;
    for (cnt = 0; cnt < TETRAMINO_LATO; cnt++) {
        if (tetramino.pieces[cnt][0] != 0)
            return 0;
    }
    return 1;
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
                        TETRAMINO_LATO; j++) {
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

/**
 * Copia un tetramino sorgente in un effettivo tetramino utilizzato nel gioco
 * @param copy
 * @param source
 */
void copyTetramino(tetramino_t *copy, int source[TETRAMINO_LATO][TETRAMINO_LATO]) {
    int i, j;
    for (i = 0; i < TETRAMINO_LATO; i++) {
        for (j = 0; j < TETRAMINO_LATO; j++) {
            copy->pieces[i][j] = source[i][j];
        }
    }
}

int getLastTetramino(tetramino_t *da_inserire, char type) {
    int isOkay = 1;
    switch (type) {
        case 'i':
            if (i_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, I);
            --i_size;
            break;
        case 'j':
            if (j_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, J);
            --j_size;
            break;
        case 'l':
            if (l_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, L);
            --l_size;
            break;
        case 'o':
            if (o_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, O);
            --o_size;
            break;
        case 's':
            if (s_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, S);
            --s_size;
            break;
        case 't':
            if (t_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, T);
            --t_size;
            break;
        case 'z':
            if (z_size <= 0) {
                printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, Z);
            --z_size;
            break;
        default:
            printf("Rotto");
            break;
    }
    return isOkay;
}


/**
 * Funzione che crea effettivamente il tetramino e decrementa la quantità di tetramini a disposizione
 */
tetramino_t edit_tetramino(char type, int rotation) {
    int isOkay = 0;
    tetramino_t da_inserire;

    if (type != 'i' && type != 'z' && type != 't' && type != 's' && type != 'l' && type != 'o' && type != 'j') {
        printf("\nSelezione non valida\n");
        exit(0);
    }
    if (rotation < 1 || rotation > 4) {
        printf("\nRotazione non valida\n");
        exit(0);
    }

    isOkay = getLastTetramino(&da_inserire, type);

    if (isOkay == 0) {
        exit(0);
    }
    da_inserire.type = type;
    da_inserire.rotation = rotation;
    da_inserire = rotateTetramino(da_inserire);

    while (checkEmptyLastRow(
            da_inserire)) { /*finchè l'ultima la più in basso della matrice è fatta di soli 0 porto il tetramino in basso*/
        da_inserire = pushTetraminoDown(da_inserire);
    }

    while (checkEmptyLeftColumn(da_inserire)) {
        da_inserire = pushTetraminoLeft(da_inserire);
    }

    return da_inserire;
}

/**
 * stampa il campo di gioco
 * @param matrix
 */
void print_field(int matrix[HEIGHT][WIDTH]) {
    int i, j;

    printf("\t\t");
    for (i = 0; i < WIDTH; i++) {
        printf("%d\t", i);
    }
    printf("\n\n\n");

    for (i = 0; i < HEIGHT; ++i) {
        printf("%d\t\t", i);
        for (j = 0; j < WIDTH; j++) {
            switch (matrix[i][j]) {
                case 0:
                    printf("x\t");
                    break;
                default:
                    printf("[]\t");
                    break;
            }
        }
        printf("\n\n");
    }
    printf("\n");
    printf("\t\t");
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


int main() {
    int i, j, win = 0, lose = 0, rotation_selection, colonna, giallo;
    tetramino_t da_inserire;
    int field[HEIGHT][WIDTH] = {0};
    char type_selection;


    while (/*win == 0 && lose == 0*/ giallo < 5) {

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
        scanf(" %c", &type_selection);
        printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
        scanf("%d", &rotation_selection);
        printf("\nSeleziona la colonna dove posizionare il tetramino (inserisci un numero tra 0 e 9): ");
        scanf("%d", &colonna);
        da_inserire = edit_tetramino(type_selection, rotation_selection);
        addTetramino(&da_inserire, field, colonna);

        /* todo creare una struct giocatore e fare in modo che abbia come attributi il punteggio e il "proprio campo da gioco"
          questo perchè dobbiamo tenere conto dei punti ed oltretutto ci sono due giocatori che hanno due campi da gioco distinti */
        while(deleteRows(field)){
                printf("Ho elimanto righe" );
        }


        giallo++;


    }


    return 0;

}




/**
 *Questa funnzione cerca le righe del campo da gioco dove non ci sono 0
 * come nel gioco del vero tetris in quel caso, l'intera riga viene elimata ed il resto di campo di gioco spostato in basso
 * @param campo
 * @return  Il numero di righe che sono state eliminate, utile per calcolare il putenggio.
 */
int deleteRows(int campo [HEIGHT][WIDTH]) {
    int i,j, fullRow=0, deletedRows_counter=0;
    for(i=HEIGHT-1;i>=0;i--){
        fullRow=1;
        for(j=WIDTH-1;j>=0;j--){ /** ciclo di controllo, se la riga è completamente piena*/
            if(campo[i][j]==0){
                fullRow=0;
            }
        }
        if(fullRow){
            deletedRows_counter++;
            for(j=WIDTH-1;j>=0;j--){ /** dove azzero tutta la riga*/
               campo[i][j]=0;
            }
            /* TODO FAR IN MODO CHE IL RESTO DI MATRICE VENGA SPOSTATA IN BASSO */


            i=HEIGHT-1; /* nel caso in cui ci sia stata una riga eliminata, la matrice è cambiata e quindi devo ripetere il controllo dall'inizio!!!! */
        }
    }
    return deletedRows_counter;
}





