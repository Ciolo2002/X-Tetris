

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  /* SE SI USA CLION INSERIRE NEL FILE CMakeList.txt --> target_link_libraries(X_Tetris_first PRIVATE m)  */

#define WIDTH 10
#define HEIGHT 15
#define TETRAMINO_LATO 4
#define n_tetramini 20

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
 * creo i tetramini come array globabili in modo da poterli prendere direttamente dentro alle funzioni
 */

int i_size = n_tetramini;
int j_size = n_tetramini;
int l_size = n_tetramini;
int o_size = n_tetramini;
int s_size = n_tetramini;
int t_size = n_tetramini;
int z_size = n_tetramini;
tetramino_t *i_type;
tetramino_t *j_type;
tetramino_t *l_type;
tetramino_t *o_type;
tetramino_t *s_type;
tetramino_t *t_type;
tetramino_t *z_type;


tetramino_t rotateTetramino(tetramino_t tetramino1);

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
 *
 * @param rotation
 * @param row
 * @param col
 * @param height
 * @param width
 * @return
 */

/*COPIATA DA VIO, SE RIESCI A TROVARE UN MODO PER FARLA DIVERSA MAGARI CON DEI FOR O CON DELLE FORMULE MATIMATICHE FIKE SAREBBE BELLO*/
int cella_rotazione(int rotation, int row, int col, int height, int width) {
    switch (rotation) {
        case 0:
            return row * width + col;
            break;
        case 1:
            return (height - col - 1) * width + row;
            break;
        case 2:
            return (height - row - 1) * width + (width - col - 1);
            break;
        case 3:
            return col * width + (width - row - 1);
            break;
    }
}

/*tetramino_t rotate_tetramino(int rotation, tetramino_t tetramino) {

    int aux = 0, i, j;
    tetramino_t temp = tetramino;
    tetramino.rotation = rotation;
    tetramino.pieces = malloc(sizeof(int) * tetramino.height * tetramino.width);
    if (rotation == 2 || rotation == 4) {
        aux = tetramino.height;
        tetramino.height = tetramino.width;
        tetramino.width = aux;
    }
    temp = tetramino;
    for (i = 0; i < tetramino.height; i++) {
        for (j = 0; j < tetramino.width; j++) {
            aux = cella_rotazione(tetramino.rotation, i, j, tetramino.height, tetramino.width);
            temp.pieces[i * tetramino.width + j] = tetramino.pieces[aux];
        }
    }
    return temp;

}*/
/**
 * funzione che ritorna l'ultimo tetramino disponibile
 * @param type
 * @return
 */
//TODO: fare il controllo di non aver esuarito i pezzi per array di tetramino
tetramino_t get_LastTetramino(char type) { /* ho scelto di partire dalla fine per svuotare l'array di ogni tipo di tetraminio (prendo ogni volta l'utlimo) così posso fare -- e così so che quando la size arriva a
 * 0 ho finito quei tetramini a disposizione*/
    switch (type) {
        case 'i':
            i_type = realloc(i_type, --i_size);
            return i_type[i_size];
        case 'j':
            j_type = realloc(j_type, --j_size);
            return j_type[j_size];
        case 'l':
            l_type = realloc(l_type, --l_size);
            return l_type[l_size];
        case 'o':
            o_type = realloc(o_type, --o_size);
            return o_type[o_size];
        case 's':
            s_type = realloc(s_type, --s_size);
            return s_type[s_size];
        case 't':
            t_type = realloc(t_type, --t_size);
            return t_type[t_size];
        case 'z':
            z_type = realloc(z_type, --z_size);
            return z_type[z_size];
        default:
            printf("Rotto");
            break;
    }


}


tetramino_t add_tetramino(char type, int rotation) {
    tetramino_t da_inserire;
    if (type != 'i' && type != 'z' && type != 't' && type != 's' && type != 'l' && type != 'o' && type != 'j') {
        printf("\nSelezione non valida\n");
        exit(0);
    }
    if (rotation < 1 || rotation > 4) {
        printf("\nRotazione non valida\n");
        exit(0);
    }
    da_inserire = get_LastTetramino(type);


    da_inserire.rotation = rotation;
    da_inserire = rotateTetramino(da_inserire);

    return da_inserire;


    /* da_inserire = rotate_tetramino(rotation, da_inserire); */



    /* valutare se fare in modo dinamico con un for o con uno siwtch.
    *Se fatta con il for è necessario definire nella struct del tetramino un vettore "celle" dove
    * x è la cella vuota e # quella piena, così e possibile farsi ritornare il tetramino girato dalla rotate.
    *
    * Se si usa lo switch allora bisogna stare a fare caso per caso a mano, personalmente NON credo sia la miglior scelta per ruotare. Perchè nel momento del effettivo posizionamento sono necessari dei controlli
     * e per farli serve avere un effettivo "oggetto tetramino" che sia "concreto".
    */
}

tetramino_t rotateTetramino(tetramino_t tetramino1) {
    /*tetramino_t temp = tetramino1;*/
    int temp[TETRAMINO_LATO][TETRAMINO_LATO];
    int i, j, new_x, new_y;
    float rotation_degrees = (float)((tetramino1.rotation-1 ) * 90);
    int rotation = tetramino1.rotation;

    if (tetramino1.type == 'o' || (tetramino1.rotation==1)) {
        return tetramino1;
    }


    /* se il tetramino è di tipo I, S o Z la rotazione 3 ritorna il tetramino di partenza */
    if ((tetramino1.type == 'i' || tetramino1.type == 's' || tetramino1.type == 'z') && tetramino1.rotation == 3){
        return tetramino1;
    }

    while(rotation > 1) {

        for (i = 0; i < TETRAMINO_LATO; i++) {
            for (j = 0; j < TETRAMINO_LATO; j++) { /*TODO debuggare */
                /*
                new_x=abs((int) ((float)i * cosf(rotation_degrees) - (float)j * sinf(rotation_degrees)));
                new_y=abs((int) ((float)i * sinf(rotation_degrees) + (float)j * cosf(rotation_degrees)));
                printf("Colonna %d: \n",new_x);
                printf("Riga %d: \n",new_y);
                tetramino1.pieces[i][j] = temp.pieces[new_x][new_y];*/
                temp[i][j] = tetramino1.pieces[TETRAMINO_LATO - j - 1][i];
            }
        }

        rotation--;
    }

    for(i = 0; i < TETRAMINO_LATO; i++){
        for(j = 0; j < TETRAMINO_LATO; j++){
            tetramino1.pieces[i][j] = temp[i][j];
        }
    }

    return tetramino1;


}


/**
 * stampa il capo di gioco
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
 * dato un array di tetramini assegna il tipo e inizializza a 0 la rotazione
 * @param v
 * @param size
 * @param type
 * @return
 */
tetramino_t *assign_values(tetramino_t *v, int size, char type,/* int height, int width, */
                           int pieces[TETRAMINO_LATO][TETRAMINO_LATO]) {
    /* FARE UN PICCOLO CONTROLLO PERCHè CREDO CHE NON VADA AD INZIALIZZARE TUTTI E 20 I PEZZI DELL'ARRAY
     * MA CICLI 20, ANDANDO A MODIFICARE SEMPRE E SOLO LA PRIMA CELLA DELL'ARRAY.
     *
     * edit: MODIFICATO DA BIG_PANI
     * edit2: grazie hai spaccato
     * */
    int i, righe = 0, colonne = 0, cnt = 0;
    for (i = 0; i < size; i++) {
        v[i].type = type;
        v[i].rotation = 0;
        /*   v[i].height = height;
           v[i].width = width; */
        /* v[i].pieces = (int *) malloc(sizeof(int) * height * width); */





        for (colonne = 0; colonne < TETRAMINO_LATO; colonne++) {
            for (righe = 0; righe < TETRAMINO_LATO; righe++) {
                v[i].pieces[colonne][righe] = (int) pieces[colonne][righe]; /* si rompe qua, bisogna capire perchè non assegna bene i valori
                                                                               edit_ fixato passando la matrice tramite la sua dimensione dal buon sarto*/
            }
        }
    }
    return v;
}


void print_array(tetramino_t *v, int size) {
    printf("\n\n");
    int i;
    for (i = 0; i < size; i++) {
        printf("%c %d %d\n", v[i].type, v[i].rotation, i);
    }
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


    /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */




    i_type = malloc(n_tetramini * sizeof(*i_type));
    j_type = malloc(n_tetramini * sizeof(*j_type));
    l_type = malloc(n_tetramini * sizeof(*l_type));
    o_type = malloc(n_tetramini * sizeof(*o_type));
    s_type = malloc(n_tetramini * sizeof(*s_type));
    t_type = malloc(n_tetramini * sizeof(*t_type));
    z_type = malloc(n_tetramini * sizeof(*z_type));


    assign_values(i_type, i_size, 'i', /*4, 4,*/    I);
    assign_values(j_type, j_size, 'j',  /*4, 4,*/  J);
    assign_values(l_type, l_size, 'l',  /*4, 4,*/  L);
    assign_values(o_type, o_size, 'o',  /*4, 4,*/   O);
    assign_values(s_type, s_size, 's',  /*4, 4,*/   S);
    assign_values(t_type, t_size, 't',  /*4, 4,*/   T);
    assign_values(z_type, z_size, 'z',  /*4, 4,*/   Z);


    /* print_realTetramino(z_type[4]); */


    /* while(win == 0 && lose == 0){*/
    printf("TETRAMINI A DISPOSIZIONE: \n");

    print_tetramini('i', i_size);
    print_tetramini('j', j_size);
    print_tetramini('l', l_size);
    print_tetramini('o', o_size);
    print_tetramini('s', s_size);
    print_tetramini('t', t_size);
    print_tetramini('z', z_size);

    printf("\n\n------------ GAME FIELD: ------------\n\n");



    /* SELEZIONE TETRAMINO  */



    print_field(field);

    printf("\n\n\nSeleziona un tetramino (inserisci un carattere tra i, j, l, o, s, t, z): ");
    scanf("%c", &type_selection);
    printf("\nSeleziona una rotazione (inserisci un numero tra 1 e 4): ");
    scanf("%d", &rotation_selection);
    tetramino_t inserito = add_tetramino(type_selection, rotation_selection);

    print_realTetramino(inserito);
    /*TODO fare la funzione che sposta il tetramino il più in basso a sx possibile */

    /* }*/




    return 0;

}
