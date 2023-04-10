#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const char OLAF = '0';
const char STITCH = 'S';
const char JASMIN = 'J';
const char RAYO_MCQUEEN = 'R';

const char TRINEO = 'T';
const char NAVE_ESPACIAL = 'N';
const char CAMION = 'C';
const char ALFOMBRA= 'A';
const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';
const int VALOR_TRINEO_NAVE_ESPACIAL = 10;
const int VALOR_CAMION_ALFOMBRA = 20;
const int VALOR_BOLAS_NIEVE = 3;
const int VALOR_PIUM_PIUM = 6;
const int VALOR_KUCHAU = 9;
const int VALOR_GENIO = 12;
const float LIMITE_HORAS_MAXIMA = 23.60f;
const float LIMITE_MINUTOS = 0.60f;
const int LIMITE_SUP_NOTA_PARCIAL = 10;
const int LIMITE_INF_NOTA_PARCIAL = 1;
const int LIMITE_HORAS_MINIMA = 0;

const int MAX_MULTIPLICADOR_BAJO = 3;
const int MULTIPLICADOR_BAJO = 1;

const int MAX_MULTIPLICADOR_MEDIO_BAJO = 6;
const int MULTIPLICADOR_MEDIO_BAJO = 2;

const int MAX_MULTIPLICADOR_MEDIO_ALTO = 8;
const int MULTIPLICADOR_ALTO = 4;

const int LIMITE_FRANJA_PUNTAJE = 41;
const int FRANJA_OLAF_STITCH = 1;
const int FRANJA_JAZMIN_RAYO = 2;
const int LIMITE_HORAS_LLEGADA_PARCIAL = 15;
const float LIMITE_MINUTOS_LLEGADA_PARCIAL = 0.31f;

//Pos: Introduce a la funcion al usuario
void introducir(){
    printf("Bienvenido al test de personalidad. Porfavor, responda las siguientes preguntas:\n");
    printf("\n");
    printf("Te levantas una mañana para ir a rendir un final a la facultad...\n");
}

//Pre:
//Pos:Devuelve un valor booleano true que muestra si el transporte ingresado es correcto (ref_medio_de_transporte = T || N || C || A) y false si es incorrecto
bool transporte_incorrecto(char medio_de_transporte){
    return((medio_de_transporte) != (TRINEO) && (medio_de_transporte) != NAVE_ESPACIAL && (medio_de_transporte) != CAMION && (medio_de_transporte) != ALFOMBRA);
}

//Pre:
//Pos: Devuelve un valor booleano true que muestra si el medio es correcto (ref_medio_de_atravesar_manifestacion = B || P || K || G) y false si no, por lo tanto, es incorrecto
bool medio_de_atravezar_manifestacion_incorrecto(char ref_medio_de_atravesar_manifestacion){
    return ((ref_medio_de_atravesar_manifestacion) != BOLAS_DE_NIEVE && (ref_medio_de_atravesar_manifestacion) != PIUM_PIUM && (ref_medio_de_atravesar_manifestacion) != KUCHAU &&
            (ref_medio_de_atravesar_manifestacion) != GENIO);
}

//Pre:
//Pos: Devuelve un valor booleano TRUE si el horario es correcto (0 <= HORAS < 24 && MINUTOS <=59) o FALSE si es incorrecto
bool horario_incorrecto(float hora_llegada_parcial){
    int horas = (int)((float)hora_llegada_parcial);
    float minutos = hora_llegada_parcial - (float)horas;

    return ((minutos >= LIMITE_MINUTOS) || (horas >= LIMITE_HORAS_MAXIMA) || (horas < LIMITE_HORAS_MINIMA));
}

//Pre:
//Pos: Devuelve un valor booleano TRUE si la nota ingresada es correcta (1 <= nota_parcial <= 10) y false si no
bool nota_parcial_incorrecto(int ref_nota_parcial){
    return (ref_nota_parcial < LIMITE_INF_NOTA_PARCIAL || ref_nota_parcial > LIMITE_SUP_NOTA_PARCIAL);
}

//Post Chequea si el transporte es valide y en caso de no serlo, lo pide otra vez
void chequear_respuesta_transporte(char* medio_de_transporte){
    while (transporte_incorrecto(*medio_de_transporte)){
        printf("Opcion ingresada invalida. Vuelva a intentar\n");
        scanf(" %c", &(*medio_de_transporte));
    }
}

//Pre:
//Pos: Interactua con el usuario hasta que este da una respuesta correcta y asigna el valor de la respuesta dada por el usuario, a la variable dada previamente (medio_de_transporte)
void preguntar_medio_transporte(char* medio_de_transporte){
    printf("1. Cuando estas saliendo de casa te enteras que hay paro de trenes. Que haces?\n");
    printf("Voy en: trineo (T), nave espacial (N), camion (C), alfombra (A) \n");
    scanf(" %c", &(*medio_de_transporte));

    chequear_respuesta_transporte(medio_de_transporte);
}

//Post Chequea si la respuesta del medio es válido y si no lo es lo pide otra vez
void chequear_respuesta_manifestacion(char* medio_de_atravesar_manifestacion){
    while (medio_de_atravezar_manifestacion_incorrecto(*medio_de_atravesar_manifestacion)){
        printf("Opcion ingresada invalida. Vuelva a intentar\n");
        scanf(" %c", &(*medio_de_atravesar_manifestacion));
    }
}

//Pre:
//Pos: Interactua con el usuario hasta que este da una respuesta correcta y asigna el valor de la respuesta dada por el usuario, a la variable dada previamente (medio_de_atravesar_manifestacion)
void preguntar_medio_de_atravesar_manifestacion(char* medio_de_atravesar_manifestacion){
    printf("2. Ahora resulta que en el medio del camino te encontras con una manifestacion. Que medio utilizas para deshacerte de ella?\n");
    printf("bolas de nieve (B), pium pium (P), kuchau (K), genio (G)\n");
    scanf(" %c", &(*medio_de_atravesar_manifestacion));

    chequear_respuesta_manifestacion(medio_de_atravesar_manifestacion);
}

//Post Chequea si el horario es válido y en caso de no serlo lo pide otra vez
void chequear_respuesta_horario(float* hora_llegada_parcial){
    while (horario_incorrecto(*hora_llegada_parcial)) {
        printf("Hora incorrecta, vuelva a intentar: ");
        scanf(" %f", hora_llegada_parcial);
    }
}

//Pre:
//Pos: Interactua con el usuario hasta que este da una respuesta correcta y asigna el valor de la respuesta dada por el usuario, a la variable dada previamente (hora_llegada_parcial)
void preguntar_hora_llegada_parcial(float* hora_llegada_parcial){
    printf("3. Lograste superar la manifestacion. A que hora llegaste a la universidad? Usar formato 24 horas.\n");
    scanf(" %f", hora_llegada_parcial);

    chequear_respuesta_horario(hora_llegada_parcial);
}

//Post Chequea si la nota es válida y en caso de no serla, la pide otra vez
void chequear_nota_parcial(int* nota_parcial){
    while (nota_parcial_incorrecto(*nota_parcial)){
        printf("Nota ingresada invalida. Vuelva a intentar\n");
        scanf(" %i", &*nota_parcial);
    }
}

//Pre:Una variable de tipo int para la respuesta a la pregunta
//Pos: Interactua con el usuario hasta que este da una respuesta correcta y asigna el valor de la respuesta dada por el usuario, a la variable dada previamente(nota_parcial)
void preguntar_nota_parcial(int* nota_parcial){
    printf("4.Por fin llego la nota del parcial! Del 1 al 10, que nota te sacaste?\n");
    scanf(" %i", &*nota_parcial);

    chequear_nota_parcial(nota_parcial);
}

//Pre: La variable correspondiente al medio de transporte debe ser  (T, N , C , A)
//Pos: Devuelve el puntaje del medio de transporte dado (10,20)
int calcula_puntaje_transporte(char medio_de_transporte) {
    int puntaje_transporte = VALOR_CAMION_ALFOMBRA;
    if(medio_de_transporte == TRINEO || medio_de_transporte == NAVE_ESPACIAL) puntaje_transporte = VALOR_TRINEO_NAVE_ESPACIAL;

    return puntaje_transporte;
}

//Pre: La variable correspondiente al medio antimanifestacion utilizado por el usuario. Debe ser de tipo char ( B, P, K, G)
//Pos: Devuelve el puntaje del medio antimanifestacion dado  (3,6,9,12)
int calcula_puntaje_de_medio_de_atravesar_manifestacion(char medio_de_atravesar_manifestacion){
    int puntaje_de_medio_de_atravesar_manifestacion;

    if(medio_de_atravesar_manifestacion == BOLAS_DE_NIEVE){
        puntaje_de_medio_de_atravesar_manifestacion = VALOR_BOLAS_NIEVE;
    }else if(medio_de_atravesar_manifestacion == PIUM_PIUM){
        puntaje_de_medio_de_atravesar_manifestacion = VALOR_PIUM_PIUM;
    } else if(medio_de_atravesar_manifestacion == KUCHAU){
        puntaje_de_medio_de_atravesar_manifestacion = VALOR_KUCHAU;
    } else{
        puntaje_de_medio_de_atravesar_manifestacion = VALOR_GENIO;
    }

    return puntaje_de_medio_de_atravesar_manifestacion;
}

//Pre: La variable correspondiente a la nota del parcial del usuario. Debe ser de tipo int (1 <= nota_parcial <= 10)
//Pos: Devuelve el puntaje acorde a la nota dada (1,2,3,4)
int calcula_puntaje_nota_parcial(int nota_parcial){
    int puntaje_nota_parcial;

    if(nota_parcial <= MAX_MULTIPLICADOR_BAJO){
        puntaje_nota_parcial = MULTIPLICADOR_BAJO;
    } else if(nota_parcial <= MAX_MULTIPLICADOR_MEDIO_BAJO){
        puntaje_nota_parcial = MULTIPLICADOR_MEDIO_BAJO;
    } else if(nota_parcial <= MAX_MULTIPLICADOR_MEDIO_ALTO) {
        puntaje_nota_parcial = MAX_MULTIPLICADOR_MEDIO_ALTO;
    } else{
        puntaje_nota_parcial = MULTIPLICADOR_ALTO;
    }

    return puntaje_nota_parcial;
}

//Pre: Deben ser dadas 3 variables de tipo int correspondientes al puntaje individual del transporte, medio antimanifestacion y nota del parcial dados por el usuario.
//Pos: Devuelve la franja (1,2) de los personajes entre los que se ubica el puntaje luego de utilizar la fórmula usando las 3 variables dadas en las precondiciones
int calcula_franja_puntaje(int puntaje_transporte, int puntaje_de_medio_de_atravesar_manifestacion, int puntaje_nota_parcial){
    int franja_puntaje = FRANJA_JAZMIN_RAYO;
    if (puntaje_transporte + (puntaje_de_medio_de_atravesar_manifestacion * puntaje_nota_parcial) <= LIMITE_FRANJA_PUNTAJE) franja_puntaje = FRANJA_OLAF_STITCH;

    return franja_puntaje;
}

//Devuelve true si el personaje es Olaf y false en caso contrario
bool es_olaf(int horas){
    return (horas > LIMITE_HORAS_LLEGADA_PARCIAL);
}

//Devuelve true si el personaje es Stitch y false en caso contrario
bool es_stitch(int horas){
    return (horas < LIMITE_HORAS_LLEGADA_PARCIAL);
}

//Devuelve true si el personaje es Olaf por empate y false en caso contrario
bool es_olaf_empate(float minutos){
    return (minutos < LIMITE_MINUTOS_LLEGADA_PARCIAL);
}

//Post Define si el persona es Olaf o Stitch
char definir_olaf_stitch(int horas, float minutos){
    char personaje;

    if (es_olaf(horas)){
        personaje = OLAF;
    } else if (es_stitch(horas)){
        personaje = STITCH;
    } else {
        if(es_olaf_empate(minutos)){
            personaje = OLAF;
        } else{
            personaje = STITCH;
        }
    }

    return personaje;
}

//Devuelve true si el personaje es Rayo y false en caso contrario
bool es_rayo(int horas){
    return (horas > LIMITE_HORAS_LLEGADA_PARCIAL);
}

//Devuelve true si el personaje es Jasmin y false en caso contrario
bool es_jasmin(int horas){
    return (horas < LIMITE_HORAS_LLEGADA_PARCIAL);
}

//Devuelve true si el personaje es Jasmin por empate y false en caso contrario
bool es_jasmin_empate(float minutos){
    return (minutos < LIMITE_MINUTOS_LLEGADA_PARCIAL);
}

//Post Define si el personaje es Rayo Mcqueen o Jasmin
char definir_jasmin_rayo(int horas, float minutos){
    char personaje;

    if(es_rayo(horas)) {
        personaje = RAYO_MCQUEEN;
    } else if(es_jasmin(horas)) {
        personaje = JASMIN;
    } else {
        if (es_jasmin_empate(minutos)){
            personaje = JASMIN;
        } else{
            personaje = RAYO_MCQUEEN;
        }
    }

    return personaje;
}

//Pre: Deben ser dadas la variable de franja y la variable correspondiente a la hora de llegada del usuario al parcial. La franja debe ser de tipo int (1, 2) y la hora de tipo float ( 0 <= hora <= 23.59)
//Pos: Devuelve la inicial del personaje correspondiente (O, S, J, R) dependiendo del valor de las variables dadas
char calcula_inicial_personaje (float hora_llegada_parcial, int franja){
    char personaje;
    int horas = (int)((float)hora_llegada_parcial);
    float minutos = hora_llegada_parcial - (float)horas;

    if (franja == FRANJA_OLAF_STITCH){
        personaje = definir_olaf_stitch(horas, minutos);
    } else {
        personaje = definir_jasmin_rayo(horas, minutos);
    }

    return personaje;
}

//Pre: Debe ser dada una variable que contenga la inicial de uno de los 4 personajes (O, J, S, R)
//Pos: Imprime en pantalla un texto personalizado segun la inicial dada en la variable inicial_personaje, acorde al personaje que corresponde la inicial.
void imprimir_mensaje_personaje(char inicial_personaje) {
    if (inicial_personaje == OLAF){
        printf("Tu personaje es -Olaf-. Este te ayudara durante tu aventura!\n");
    } else if(inicial_personaje == STITCH){
        printf("Tu personaje es -Stitch-. Este te ayudara durante tu aventura!\n");
    } else if(inicial_personaje == RAYO_MCQUEEN) {
        printf("Tu personaje es -Rayo McQueen-. Este te ayudara durante tu aventura!\n");
    } else{
        printf("Tu personaje es -Jasmín-. Este te ayudara durante tu aventura!\n");
    }
}

void ejecutar_test_personaje(char* ref_inicial_personaje_ayuda){
    char medio_de_transporte;
    char medio_de_atravesar_manifestacion;
    float hora_llegada_parcial;
    int nota_parcial;

    introducir();
    preguntar_medio_transporte(&medio_de_transporte);
    preguntar_medio_de_atravesar_manifestacion(&medio_de_atravesar_manifestacion);
    preguntar_hora_llegada_parcial(&hora_llegada_parcial);
    preguntar_nota_parcial(&nota_parcial);

    int puntaje_transporte = (char) calcula_puntaje_transporte(medio_de_transporte);
    int puntaje_de_medio_de_atravesar_manifestacion = (char) calcula_puntaje_de_medio_de_atravesar_manifestacion(medio_de_atravesar_manifestacion);
    int puntaje_nota_parcial = (char) calcula_puntaje_nota_parcial(nota_parcial);
    int franja = calcula_franja_puntaje(puntaje_transporte, puntaje_de_medio_de_atravesar_manifestacion, puntaje_nota_parcial);
    char inicial_personaje = calcula_inicial_personaje(hora_llegada_parcial, franja);

    (*ref_inicial_personaje_ayuda) = inicial_personaje;
    system("clear");
    imprimir_mensaje_personaje(inicial_personaje);
}