
#include <stdio.h>
#include <stdlib.h>

#define WEIGHT 10
#define HEIGHT 15
#define n_tetramini 20

typedef struct tetramino{
    char type;
    int rotation;
    int height;
    int weight;
}tetramino_t;

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
tetramino_t *i_type ;
tetramino_t *j_type ;
tetramino_t *l_type ;
tetramino_t *o_type ;
tetramino_t *s_type ;
tetramino_t *t_type ;
tetramino_t *z_type ;

tetramino_t rotate_tetramino(int rotation, tetramino_t tetramino){

}
/**
 * funzione che ritorna l'ultimo tetramino disponibile
 * @param type
 * @return
 */

tetramino_t get_LastTetramino(char type){ /* ho scelto di partire dalla fine per svuotare l'array di ogni tipo di tetraminio (prendo ogni volta l'utlimo) così posso fare -- e così so che quando la size arriva a 0 ho finito quei tetramini a disposizione*/
    switch(type){
        case 'i':
            i_type=realloc(i_type, --i_size);
            return i_type[i_size];

        case 'j':
            j_type=realloc(j_type, --j_size);
            return i_type[j_size];
        case 'l':
            j_type=realloc(j_type, --l_size);
            return j_type[j_size];
        case 'o':
            o_type=realloc(o_type, --o_size);
            return o_type[o_size];

        case 's':
            s_type=realloc(s_type, --s_size);
            return s_type[s_size];
        case 't':
            t_type=realloc(t_type, --t_size);
            return i_type[t_size];
        case 'z':
            z_type=realloc(z_type, --z_size);
            return i_type[z_size];
        default:
            printf("Rotto");
            break;
    }


}



void add_tetramino(char type, int rotation) {
    tetramino_t da_inserire;
    if (type != 'i' && type != 'z' && type != 't' && type != 's' && type != 'l' && type != 'o' && type != 'j') {
        printf("\nSelezione non valida\n");
        return;
    }
    if (rotation < 1 || rotation > 4) {
        printf("\nRotazione non valida\n");
        return;
    }
    da_inserire = get_LastTetramino(type);
    da_inserire = rotate_tetramino(rotation, da_inserire);
    /* valutare se fare in modo dinamico con un for o con uno siwtch.
    *Se fatta con il for è necessario definire nella struct del tetramino un vettore "celle" dove
    * x è la cella vuota e # quella piena, così e possibile farsi ritornare il tetramino girato dalla rotate.
    *
    * Se si usa lo switch allora bisogna stare a fare caso per caso a mano, personalmente NON credo sia la miglior scelta per ruotare. Perchè nel momento del effettivo posizionamento sono necessari dei controlli
     * e per farli serve avere un effettivo "oggetto tetramino" che sia "concreto".
    */
}







/**
 * stampa il capo di gioco
 * @param matrix
 */


void print_field( int matrix[HEIGHT][WEIGHT]){
    int i,j;

    for(i = 0; i < WEIGHT; i++)
        printf("%d\t", i);
    printf("\n\n\n");

    for(i = 0; i < HEIGHT; ++i){
        for(j = 0; j < WEIGHT; j++){
            switch(matrix[i][j]){
                case 0:
                    printf("x\t");
                    break;
            }

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
tetramino_t* assign_values(tetramino_t *v, int size, char type, int height, int weight){
    /* FARE UN PICCOLO CONTROLLO PERCHè CREDO CHE NON VADA AD INZIALIZZARE TUTTI E 20 I PEZZI DELL'ARRAY
     * MA CICLI 20, ANDANDO A MODIFICARE SEMPRE E SOLO LA PRIMA CELLA DELL'ARRAY. */
    int i;
    for(i = 0; i< size; i++){
        v->type = type;
        v->rotation = 0;
        v->height=height;
        v->weight=weight;
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


void print_tetramini(char type, int size){
    switch(type){
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
    int i, j, win = 0, lose = 0,rotation_selection;
    char type_selection;

    /* NUMERO DI TETRAMINI PER TIPO A DISPOSIZIONE */



    i_type = malloc(n_tetramini * sizeof(*i_type));
    j_type = malloc(n_tetramini * sizeof(*j_type));
    l_type = malloc(n_tetramini * sizeof(*l_type));
    o_type = malloc(n_tetramini * sizeof(*o_type));
    s_type = malloc(n_tetramini * sizeof(*s_type));
    t_type = malloc(n_tetramini * sizeof(*t_type));
    z_type = malloc(n_tetramini * sizeof(*z_type));



    assign_values(i_type, i_size, 'i',1,4);
    assign_values(j_type, j_size, 'j',2,2);
    assign_values(l_type, l_size, 'l',2,3);
    assign_values(o_type, o_size, 'o',2,2);
    assign_values(s_type, s_size, 's',2,3);
    assign_values(t_type, t_size, 't',2,3);
    assign_values(z_type, z_size, 'z',2,3);

    int field[HEIGHT][WEIGHT];
    for(i = 0; i < HEIGHT; ++i){
        for(j = 0; j < WEIGHT; j++){
            field[i][j] = 0;
        }
    }

    /* CAMPO DA GIOCO  */
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
    add_tetramino(type_selection,rotation_selection);




    /* }*/




    return 0;

}
