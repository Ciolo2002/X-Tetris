#define  WIDTH 10
#define  HEIGHT  15
#define  n_tetramini_per_type 20
#define TETRAMINO_LATO  4
#define TETRAMINO_TYPES 7

/*COLORI*/
#define ANSI_COLOR_RED     "\e[0;101m"
#define ANSI_COLOR_GREEN   "\e[0;102m"
#define ANSI_COLOR_YELLOW  "\e[0;103m"
#define ANSI_COLOR_BLUE    "\e[0;104m"
#define ANSI_COLOR_MAGENTA "\e[0;105m"
#define ANSI_COLOR_CYAN    "\e[0;106m"
#define ANSI_COLOR_WHITE   "\e[43m"
#define ANSI_COLOR_BLACK   "\e[40m"
#define ANSI_COLOR_RESET   "\x1b[0m"


const int I[4][4] = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
};

const int J[4][4] = {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {2, 2, 0, 0}
};

const int L[4][4] = {
        {0, 0, 0, 0},
        {3, 0, 0, 0},
        {3, 0, 0, 0},
        {3, 3, 0, 0}
};

const int O[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {4, 4, 0, 0},
        {4, 4, 0, 0}
};

const int S[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 5, 5, 0},
        {5, 5, 0, 0}
};

const int T[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {6, 6, 6, 0},
        {0, 6, 0, 0}
};

const int Z[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {7, 7, 0, 0},
        {0, 7, 7, 0}
};


typedef struct player {
    unsigned int points;
    int field[HEIGHT][WIDTH];
    int deleted_rows;


} player_t;


typedef struct tetramino {
    char type;
    int rotation;
    int pieces[TETRAMINO_LATO][TETRAMINO_LATO];
} tetramino_t;


typedef struct game {
    player_t *players;
} game_t;

/**
 * Stampa il logo di X-Tetris(ascii art)
 */
void printLogo(){

 printf("    ██╗  ██╗  ████████╗███████╗████████╗██████╗ ██╗███████╗ \n");
 printf("    ╚██╗██╔╝  ╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝ \n");
 printf("     ╚███╔╝█████╗██║   █████╗     ██║   ██████╔╝██║███████╗ \n");
 printf("     ██╔██╗╚════╝██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║ \n");
 printf("    ██╔╝ ██╗     ██║   ███████╗   ██║   ██║  ██║██║███████║ \n");
 printf("    ╚═╝  ╚═╝     ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝ \n");

}


/**
 * funzione che ritorna un carattere random tra i,j,l,o,s,t,z per la CPU
 * @return un carattere tra i,j,l,o,s,t,z
 */
char randomType(){
    srand(time(NULL));
    int r= rand() % 8 - 1;
    char type;
    switch(r){
        case 0:
            type = 'i';
            break;
        case 1:
            type = 'j';
            break;
        case 2:
            type = 'l';
            break;
        case 3:
            type = 'o';
            break;
        case 4:
            type = 's';
            break;
        case 5:
            type = 't';
            break;
        case 6:
            type = 'z';
            break;
        default:
            type = ' ';
            break;
    }
    return type;
}
/**
 * funzione che ritorna un numero random da 1 a 4 per la rotazione del tetramino scelto dalla CPU
 * @return un numero random da 1 a 4
 */
int randomRotation(){
    srand(time(NULL));
    int r = rand() % 4 + 1;
    return r;
}

/**
 * funzione che ritorna la colonna random in cui la CPU va a posizionare un tetramino
 * @return una colonna random tra 0 e 9
 */
int randomColumn(){
    srand(time(NULL));
    int r = rand() % 10;
    return r;
}

/**
 * se vengono eliminate 3 o più righe nello stesso istante il campo dell’avversario viene modificato invertendo il corrispondente
 * numero di linee nella parte più bassa del campo di gioco
 * @param deleted_rows
 * @param opponent
 */
void swapRows(int deleted_rows, player_t *opponent) {
    int i, j;
    if (deleted_rows >= 3) {
        for (i = HEIGHT - 1; i > (HEIGHT - 1 - deleted_rows); --i) {
            for (j = 0; j < WIDTH; j++) {
                if (opponent->field[i][j] == 0) {
                    opponent->field[i][j] = 1; /* se vuoi mettere i colori questo 1 può dare probblemi, metti tipo 9 e fai un colore speciale */
                } else {
                    opponent->field[i][j] = 0;
                }
            }
        }
    }
}

/**
 * cambia il giocatore che sta giocando con il suo avversario per prepararsi al turno successivo
 * @param game_type
 * @param player_selector
 * @return il numero relativo al giocatore che giocherà nel prossimo round
 */
int changePlayer(int game_type, int player_selector) {
    if (game_type == 1) {  /* selettore del giocatore */
        player_selector = 0;
    } else {
        if (player_selector == 0) {
            player_selector = 1;
        } else {
            player_selector = 0;
        }
    }
    return player_selector;
}

/**
 * controlla se il giocatore finisce tutti i suoi tetramini e quindi è destinato a perdere la partita
 * @param player
 * @param avaiable_tetramini
 * @return 0 se il giocatore ha finito i tetramini a disposizione o 1 se ha ancora tetramini disponibili
 */
int youLose(player_t *player, int *avaiable_tetramini) {
    int i, temp=0;
    for (i = 0; i < TETRAMINO_TYPES; i++) {
        if (avaiable_tetramini[i] != 0) {
            temp=1;
            break;
        }
    }
    if(temp==0){
        free(avaiable_tetramini);
        printf("\nYOU HAVE FINISHED ALL OF YOUR TETRAMINI\n");
    }
    return temp;
}

/**
 * Se i giocatori hanno finito i tetramini vince chi ha il punteggio maggiore
 * @param game
 * @param player_selector
 * @param avaiable_tetramini
 * @param game_type
 */
int checkLose( game_t game, int player_selector, int * avaiable_tetramini, int game_type){
    int loser = 1;
    loser = youLose(&game.players[player_selector], avaiable_tetramini);
    if (loser == 0) {

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
        return loser;
    }
    return loser;
}


/**
 * Questa funzione spinge il tutto quello che c'è nella matrice giù di 1 riga rispetto alla riga indicata.
 * Viene utilizzata quando il giocatore completa una riga che quindi deve essere svuotata.
 * @param campo
 * @param col
 */
void pushFieldDown(int campo[HEIGHT][WIDTH], int col) {
    int temp[WIDTH] = {0};
    int i = 0;
    int col_tmp;
    for (col_tmp = col; col_tmp > 0; col_tmp--) {
        for (i = 0; i < WIDTH; i++) {
            temp[i] = campo[col_tmp][i];
            campo[col_tmp][i] = campo[col_tmp - 1][i];
            campo[col_tmp - 1][i] = temp[i];
        }
    }

}

/**
 *Questa funzione cerca le righe del campo da gioco dove non ci sono 0
 * come nel gioco del vero tetris in quel caso, l'intera riga viene elimata ed il resto di campo di gioco spostato in basso
 * @param campo
 * @return  Il numero di righe che sono state eliminate, utile per calcolare il punteggio.
 */
int deleteRows(int campo[HEIGHT][WIDTH]) {
    int i, j, fullRow = 1, deleted_rows = 0;

    for (i = HEIGHT ; i >= 0; i--) {
        fullRow = 1;
        for (j = WIDTH - 1; j >= 0; j--) { /** ciclo di controllo, se la riga è completamente piena*/
            if (campo[i][j] == 0) {
                fullRow = 0;
            }
        }
        if (fullRow) {
            for (j = WIDTH - 1; j >= 0; j--) {
                campo[i][j] = 0;
            }
            pushFieldDown(campo, i); /* FA IN MODO CHE IL RESTO DI MATRICE DEL CAMPO VENGA SPOSTATA IN BASSO */
            i = HEIGHT ; /* nel caso in cui ci sia stata una riga eliminata, la matrice è cambiata e quindi devo ripetere il controllo dall'inizio!!!! */
            ++deleted_rows;
        }
    }
    return deleted_rows;
}

/**
 * Va a tutti gli effetti a piazzare il tetramino nel campo da gioco
 * @param pField
 * @param pTetramino
 * @param colonna
 * @param riga
 */
void place_tetramino(int pField[HEIGHT][WIDTH], tetramino_t *pTetramino, int colonna, int riga, int player_selector) {
    int i, j, bool_placed = 0;
    for (i = TETRAMINO_LATO - 1; i >= 0; i--) {
        for (j = TETRAMINO_LATO - 1; j >= 0; j--) {
            if (pTetramino->pieces[i][j] != 0) {
                pField[riga][j + colonna] = pTetramino->pieces[i][j];
                bool_placed = 1;
            }
        }
        if (bool_placed) { /** posizionamento della riga superiore del campo da gioco*/
            if(riga<0){
                /** il giocatore ha sforato in altezza il campo da gioco quindi ha perso*/
                if(player_selector == 0)
                    printf("\n\nGAME OVER, PLAYER 2 WON");
                else
                    printf("\n\nGAME OVER, PLAYER 1 WON");

                exit(0);
            }
            riga--;
        }
        bool_placed = 0;
    }
}


/**
 * ritorna la maggiore lunghezza del tetramino che riceve in base alla sua rotazione attuale
 * @param pTetramino
 * @return la lunghezza maggiore possibile del tetramino in base alla sua rotazione
 */
int maxTetraminoWidth(tetramino_t *pTetramino) {
    int max_tetramino_width = 0, i, j, j_record = -1;
    for (j = 0; j < TETRAMINO_LATO; j++) {
        for (i = 0; i < TETRAMINO_LATO; i++) {
            if (pTetramino->pieces[i][j] != 0) {
                if (j_record != j) {
                    max_tetramino_width++;
                    j_record = j;
                }
            }
        }
    }


    return max_tetramino_width;
}


/**
 * Controlla che la scelta del giocatore non porti fuori a destra o a sinistra il tetramino dal campo da gioco, poi
 * controlla se un tetramino ci sta nel campo da gioco ed eventualmente in quale riga andarlo a piazzare,
 * dopodichè una volta trovata la riga chiama place_tetramino e lo piazza oppure fa perdere il giocatore
 * @param da_inserire
 * @param field
 * @param col
 */
void addTetramino(tetramino_t *da_inserire, int field[HEIGHT][WIDTH], int col, int player_selector) {

    int i, j, z, temp = -1, calcomagicoastrale = 0;


    for (i = 0; i < HEIGHT; i++) { /*riga campo da gioco*/
        temp = -1;
        for (j = TETRAMINO_LATO - 1; j >= 0; j--) { /*riga tetramino*/
            for (z = TETRAMINO_LATO - 1; z >= 0; z--) { /*colonna tetramino*/
                calcomagicoastrale = (i - ((TETRAMINO_LATO - 1) - j));
                if(calcomagicoastrale>=0){
                    if ((field[calcomagicoastrale][z + col] == 0 || da_inserire->pieces[j][z] == 0)) {  /** controllo che l'intero tetramino ci sta all'interno del campo di gioco, se non ci sta controllo la riga superiore del campo da gioco */
                    } else {
                        temp = i;
                    }
                }
                }
            }

        if (temp != -1) { /** una volta trovata la riga dove posizionare il tetramino, lo vado effettivamente ad inserire nel campo da gioco*/
            place_tetramino(field, da_inserire, col, i-1, player_selector);
            return;
        }
    }
    place_tetramino(field, da_inserire, col, i-1, player_selector);
    return;

}


/**
 * Porta i valori del tetramino giù di 1 riga nella matrice che lo contiene
 * @param tetramino
 * @return il tetramino
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
 * @return il tetramino
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
 * @return 1 se tutta l'ultima riga del tetramino è composta di soli 0, sennò ritorna 0
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
 * @return 1 se la prima colonna del tetramino è composta di soli 0, sennò ritorna 0
 */
int checkEmptyLeftColumn(tetramino_t tetramino) {
    int cnt;
    for (cnt = 0; cnt < TETRAMINO_LATO; cnt++) {
        if (tetramino.pieces[cnt][0] != 0)
            return 0;
    }
    return 1;
}

/**
 * ruota il tetramino in base alla sua rotazione
 * @param tetramino1
 * @return il tetramino ruotato
 */
tetramino_t rotateTetramino(tetramino_t tetramino1) {
    tetramino_t temp = tetramino1;
    int i, j;
    int rotation = tetramino1.rotation;


    if (tetramino1.type == 'o' || tetramino1.rotation == 1) {
        return tetramino1;
    }
    /* se il tetramino è di tipo I, S o Z e la rotazione è 3 ritorna il tetramino di partenza */
    if ((tetramino1.type == 'i' || tetramino1.type == 's' || tetramino1.type == 'z') && tetramino1.rotation == 3) {
        return tetramino1;
    }
    while (rotation > 1) {
        for (i = 0; i < TETRAMINO_LATO; i++) {
            for (j = 0; j < TETRAMINO_LATO; j++) {
                temp.pieces[i][j] = tetramino1.pieces[TETRAMINO_LATO - j - 1][i];
            }
        }
        rotation--;
        tetramino1 = temp;
    }

    return tetramino1;
}

/**
 * Copia un tetramino sorgente in un effettivo tetramino utilizzato nel gioco
 * @param copy
 * @param source
 */
void copyTetramino(tetramino_t *copy, const int source[TETRAMINO_LATO][TETRAMINO_LATO]) {
    int i, j;
    for (i = 0; i < TETRAMINO_LATO; i++) {
        for (j = 0; j < TETRAMINO_LATO; j++) {
            copy->pieces[i][j] = source[i][j];
        }
    }
}

/**
 * controlla se sono disponibili tetramini del tipo inserito, se sì decrementa il numero di tetramini disponibili, se no ritorna 0
 * @param da_inserire
 * @param type
 * @param player
 * @param avaiable_tetramini
 * @param game_type
 * @param player_selector
 * @return 1 se il tetramino di tipo type è disponibile, 0 se non è disponibile
 */
int getLastTetramino(tetramino_t *da_inserire, char type, player_t *player, int * avaiable_tetramini, int game_type, int player_selector) {
    int isOkay = 1;
    switch (type) {
        case 'i':
            if (avaiable_tetramini[0] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }
                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, I);
            --avaiable_tetramini[0];
            break;
        case 'j':
            if (avaiable_tetramini[1] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, J);
            --avaiable_tetramini[1];
            break;
        case 'l':
            if (avaiable_tetramini[2] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, L);
            --avaiable_tetramini[2];
            break;
        case 'o':
            if (avaiable_tetramini[3] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, O);
            --avaiable_tetramini[3];
            break;
        case 's':
            if (avaiable_tetramini[4] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, S);
            --avaiable_tetramini[4];
            break;
        case 't':
            if (avaiable_tetramini[5] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, T);
            --avaiable_tetramini[5];
            break;
        case 'z':
            if (avaiable_tetramini[6] <= 0) {
                if(game_type != 3 || player_selector == 0) {
                    printf("\nI tetramini a disposizione di tipo %c sono finiti\n", type);
                }                isOkay = 0;
                break;
            }
            copyTetramino(da_inserire, Z);
            --avaiable_tetramini[6];
            break;
        default:
            printf("Rotto");
            break;
    }
    return isOkay;
}

/**
 * Funzione che crea effettivamente il tetramino
 * @param type
 * @param rotation
 * @param player
 * @param da_inserire
 * @return il tetramino
 */
tetramino_t edit_tetramino(char type, int rotation, player_t *player, tetramino_t da_inserire) {
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
void printField(int matrix[HEIGHT][WIDTH]) {
    int i, j;


    printf("\n");

    for (i = 0; i < HEIGHT; ++i) {
        printf("\t\t\t%d\t", i);
        for (j = 0; j < WIDTH; j++) {
            switch (matrix[i][j]) {
                case 0:
                    printf(ANSI_COLOR_BLACK   "   "     ANSI_COLOR_RESET);
                    break;
                case 1:
                    printf(ANSI_COLOR_CYAN    "   "     ANSI_COLOR_RESET );
                    break;
                case 2:
                    printf(ANSI_COLOR_BLUE     "   "     ANSI_COLOR_RESET );
                    break;
                case 3:
                    printf(ANSI_COLOR_WHITE     "   "     ANSI_COLOR_RESET );
                    break;
                case 4:
                    printf(ANSI_COLOR_YELLOW    "   "     ANSI_COLOR_RESET );
                    break;
                case 5:
                    printf(ANSI_COLOR_GREEN     "   "     ANSI_COLOR_RESET );
                    break;
                case 6:
                    printf(ANSI_COLOR_MAGENTA     "   "     ANSI_COLOR_RESET );
                    break;
                case 7:
                    printf(ANSI_COLOR_RED       "   "     ANSI_COLOR_RESET );
                    break;
            }
        }
        printf("\n");
    }

    printf("\t\t\t\t");
    for (i = 0; i < WIDTH; i++)
        printf(" %d ", i);

}

/**
 * Funzione che stampa la forma di un dato tetramino e quanti restano a disposizione del player
 * @param type
 * @param size
 *
 */
void print_tetramini(char type, int size) {
    switch (type) {
        case 'i':
            printf("i\n");
            printf(ANSI_COLOR_CYAN"            "ANSI_COLOR_RESET " : %d\n\n", size);
            break;

        case 'j':
            printf("j\n");
            printf("   " ANSI_COLOR_BLUE "   " ANSI_COLOR_RESET "\n"
                   "   "ANSI_COLOR_BLUE "   " ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_BLUE"      " ANSI_COLOR_RESET "\t\t: %d\n\n" , size);
            break;
        case 'l':
            printf("l\n");
            printf(ANSI_COLOR_WHITE"   "ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_WHITE"   "ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_WHITE"      "ANSI_COLOR_RESET "\t\t: %d\n\n", size);
            break;
        case 'o':
            printf("o\n");
            printf(ANSI_COLOR_YELLOW"      " ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_YELLOW"      " ANSI_COLOR_RESET "\t\t: %d\n\n", size);
            break;
        case 's':
            printf("s\n");
            printf("   " ANSI_COLOR_GREEN "      " ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_GREEN "      " ANSI_COLOR_RESET "\t\t:%d\n\n", size);
            break;
        case 't':
            printf("t\n");
            printf("   " ANSI_COLOR_MAGENTA "   " ANSI_COLOR_RESET "\n"
                   ANSI_COLOR_MAGENTA "         " ANSI_COLOR_RESET "\t:%d\n\n", size);
            break;
        case 'z':
            printf("z\n");
            printf(ANSI_COLOR_RED "      " ANSI_COLOR_RESET "\n"
                   "   " ANSI_COLOR_RED "      " ANSI_COLOR_RESET "\t:%d\n\n", size);
            break;
    }
}

/**
 * la funzione ritorna 1 se il tipo o la rotazione dati al tetramino non sono validi, sennò ritorna 0
 * @param type
 * @param rotation
 * @param game_type
 * @param player_selector
 * @return 1 o 0
 */
int exception_t_r(char type, int rotation, int game_type, int player_selector) {
    if (type != 'i' && type != 'z' && type != 't' && type != 's' && type != 'l' && type != 'o' && type != 'j') {
        if(game_type != 3 || player_selector == 0) {
            printf("\nSelezione non valida\n");
        }
        return 1;
    }
    if (rotation < 1 || rotation > 4) {
        if(game_type != 3 || player_selector == 0) {
            printf("\nRotazione non valida\n");
        }
        return 1;
    }
    return 0;
}


/**
 * la funzione gestisce l'errore in caso un tetramino venga posizionato al di fuori del campo a destra o a sinistra,
 * inoltre incrementa la quantità di tetramini a disposizione per il tipo indicato, dato che verrebbe decrementata senza posizionare nessun tetramino
 * @param da_inserire
 * @param col
 * @param avaiable_tetramini
 * @return 1 o 0
 */
int exception_width(tetramino_t * da_inserire, int col, int * avaiable_tetramini, int game_type, int player_selector) {
    int lunghezza_max_tetramino;
    lunghezza_max_tetramino = maxTetraminoWidth(da_inserire);
    if ((col + lunghezza_max_tetramino) > WIDTH || (col + lunghezza_max_tetramino) <= 0) {
        if(game_type != 3 || player_selector == 0) {
            printf("\nNon puoi posizione un tetramino fuori dal campo di gioco.\n");
        }


        switch(da_inserire->type){
            case 'i':
                ++avaiable_tetramini[0];
                break;
            case 'j':
                ++avaiable_tetramini[1];
                break;
            case 'l':
                ++avaiable_tetramini[2];
                break;
            case 'o':
                ++avaiable_tetramini[3];
                break;
            case 's':
                ++avaiable_tetramini[4];
                break;
            case 't':
                ++avaiable_tetramini[5];
                break;
            case 'z':
                ++avaiable_tetramini[6];
                break;
        }

        return 1;
    }
    return 0;
}


/**
 * incrementa i punti del giocatore in base a quante righe sono state eliminate
 * @param result
 * @param cnt
 */
void increment_points(unsigned int *result, int *cnt) {
    switch (*cnt) {
        case 1:
            *result += 1;
            break;
        case 2:
            *result += 3;
            break;
        case 3:
            *result += 6;
            break;
        case 4:
            *result += 12;
            break;
    }
}