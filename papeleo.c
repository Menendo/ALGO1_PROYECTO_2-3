#include "test_personalidad.h"
#include <stdio.h>
#include "papeleo.h"
#include <stdlib.h>
#include "coordenadas_random.h"
#include "utiles.h"

#define MAX_FILAS_PRIMER_NIVEL 22
#define MAX_COLUMNAS_PRIMER_NIVEL 22
#define MAX_FILAS_SEGUNDO_NIVEL 17
#define MAX_COLUMNAS_SEGUNDO_NIVEL 17
#define MAX_COLUMNAS_TERCER_NIVEL 12
#define MAX_FILAS_TERCER_NIVEL 12
#define MAX_TECLAS_VALIDAS 9

static const int PERDIDO = -1;
static const int GANADO = 1;
static const int JUGANDO = 0;

const int UNA_POSICION = 1;
const int DESFASAJE_NIVEL = 1;
const float TIEMPO_DE_CAIDA = 0.5;
const int LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL = 21;
const int LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL = 16;
const int LIMITE_POSICION_COLUMNAS_TERCER_NIVEL = 11;
const int LIMITE_POSICION_FILAS_PRIMER_NIVEL = 21;
const int LIMITE_POSICION_FILAS_SEGUNDO_NIVEL = 16;
const int LIMITE_POSICION_FILAS_TERCER_NIVEL = 11;
const int POSICION_PRIMER_PAPELEO = 0;
const int SIN_HERRAMIENTAS = 0;
const int POSICION_PRIMER_OBSTACULO = 0;
const int NO_HAY_FUEGO = -1;
const int POSICION_PRIMERA_PARED = 0;
const int ES_DIVISIBLE = 0;
const int CANTIDAD_TECLAS_VALIDAS = 8;
const int POSICION_ROTACION_HORARIO = 0;
const int POSICION_ROTACIOON_ANTIHORARIO = 1;
const int POSICION_USAR_EXTINTOR = 2;
const int POSICION_USAR_MARTILLO = 3;
const int POSICION_DERECHA = 4;
const int POSICION_IZQUIERDA = 5;
const int POSICION_ARRIBA = 6;
const int POSICION_ABAJO = 7;
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char IZQUIERDA = 'A';
const char DERECHA = 'D';
const char ROTAR_MAPA_HORARIO = 'E';
const char ROTAR_MAPA_ANTIHORARIO = 'Q';
const char USAR_MARTILLO = 'Z';
const char USAR_EXTINTOR = 'C';
const int CANTIDAD_TECLAS_VALIDAS_INICIALES = 6;
const int PRIMERA_FILA_JUGABLE = 1;
const int PRIMERA_COLUMNA_JUGABLE = 1;
const int ULTIMA_FILA_JUGABLE_PRIMER_NIVEL = 20;
const int ULTIMA_FILA_JUGABLE_SEGUNDO_NIVEL = 15;
const int ULTIMA_FILA_JUGABLE_TERCER_NIVEL = 10;
const int ULTIMA_COLUMNA_JUGABLE_PRIMER_NIVEL = 20;
const int ULTIMA_COLUMNA_JUGABLE_SEGUNDO_NIVEL = 15;
const int ULTIMA_COLUMNA_JUGABLE_TERCER_NIVEL = 10;
const int NO_CHOCO_PAPELEO = -1;
const int MOVIMIENTOS_PERDIDOS_POR_MEDIA = 10;
const int MOVIMIENTOS_GANADOS_POR_BOTELLA = 7;
const int MOVIMIENTOS_AL_CHOCAR_FUEGO = 0;
const int R_PRIMER_NIVEL = 7;
const int R_SEGUNDO_NIVEL = 5;
const int R_TERCER_NIVEL = 3;
const int MOVIMIENTOS_LIMITES_PARA_PAREDES_PRIMER_NIVEL = 41;
const int MOVIMIENTOS_LIMITES_PARA_PAREDES_SEGUNDO_NIVEL = 31;
const int MOVIMIENTOS_LIMITES_PARA_PAREDES_TERCER_NIVEL = 21;
const int NO_HAY_PARED = -1;

const char MIKE = 'W';
const int MOVIMIENTOS_INICIALES_PRIMER_NIVEL = 40;
const int MARTILLOS_INICIALES_PRIMER_NIVEL = 4;
const int MOVIMIENTOS_CON_RAYO_PRIMER_NIVEL = 50;
const int MARTILLOS_CON_JASMIN_PRIMER_NIVEL = 5;
const int EXTINTORES_PRIMER_NIVEL = 4;
const bool RANDALL_PRIMER_NIVEL_DESACTIVADO = false;
const int SIN_MOVIMIENTOS = 0;

const int CHOCO_MEDIA = 2;
const int CHOCO_FUEGO = 1;
const int CHOCO_BOTELLA = 1;
const int CHOCO_INTERRUPTOR = 2;
const int NO_CHOCO = 0;
const char MEDIAS = 'M';
const char BOTELLAS_GRITOS = 'G';
const char FUEGOS = 'F';
const char AHUYENTA_RANDALL = 'I';
const bool NO_RECOLECTADO = false;
const int ID_PRIMER_PAPELEO = 1;
const int PRIMER_NIVEL = 1;
const int SEGUNDO_NIVEL = 2;
const int TERCER_NIVEL = 3;
const int POSICION_PRIMER_NIVEL = 0;
const int POSICION_SEGUNDO_NIVEL = 1;
const int POSICION_TERCER_NIVEL = 2;

const int CANTIDAD_DE_FUEGOS_PRIMER_NIVEL = 10;
const int CANTIDAD_DE_OBSTACULOS_PRIMER_NIVEL = 15;
const int CANTIDAD_DE_BOTELLAS_PRIMER_NIVEL = 4;
const int CANTIDAD_DE_HERRAMIENTAS_PRIMER_NIVEL = 5;
const int CANTIDAD_DE_PAPELEOS_PRIMER_NIVEL = 2;
const int CANTIDAD_DE_FUEGOS_OLAF_PRIMER_NIVEL = 8;
const int CANTIDAD_DE_OBSTACULOS_OLAF_PRIMER_NIVEL = 13;

const int CANTIDAD_DE_MEDIAS_SEGUNDO_NIVEL = 4;
const int CANTIDAD_DE_OBSTACULOS_SEGUNDO_NIVEL = 9;
const int CANTIDAD_DE_BOTELLAS_SEGUNDO_NIVEL = 3;
const int CANTIDAD_DE_HERRAMIENTAS_SEGUNDO_NIVEL = 4;
const int CANTIDAD_DE_PAPELEOS_SEGUNDO_NIVEL = 3;
const int CANTIDAD_DE_FUEGOS_OLAF_SEGUNDO_NIVEL = 4;
const int CANTIDAD_DE_OBSTACULOS_OLAF_SEGUNDO_NIVEL = 8;

const int CANTIDAD_DE_MEDIAS_TERCER_NIVEL = 3;
const int CANTIDAD_DE_OBSTACULOS_TERCER_NIVEL = 6;
const int CANTIDAD_DE_BOTELLAS_TERCER_NIVEL = 2;
const int CANTIDAD_DE_PAPELEOS_TERCER_NIVEL = 4;
const int CANTIDAD_PAPELEOS_STITCH_TERCER_NIVEL = 3;

const char PARED = '#';
const char ESPACIO_VACIO_MATRIZ = ' ';

void realizar_llenado_fuegos(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS], int cantidad_de_fuegos){
    for (int i = 0; i < cantidad_de_fuegos; ++i){
        obstaculos[i].posicion = coordenadas_fuegos[i];
        obstaculos[i].tipo = FUEGOS;
        (*ref_tope_obstaculos)++;
    }
}

//Pre:Para inicializar correctamente, el vector coordenadas fuegos debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara los fuegos correspondientes al nivel, dandoles una coordenada aleatoria del vector coordenadas fuegos y asignandoles el tipo "fuegos". Este solo se activara si el personaje del tp1 es olaf
void llenar_obstaculos_con_fuegos_olaf(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS], int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_fuegos(obstaculos, ref_tope_obstaculos, coordenadas_fuegos, CANTIDAD_DE_FUEGOS_OLAF_PRIMER_NIVEL);
	} else if (numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_fuegos(obstaculos, ref_tope_obstaculos, coordenadas_fuegos, CANTIDAD_DE_FUEGOS_OLAF_SEGUNDO_NIVEL);
	}
}

void realizar_llenado_medias(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int
contador_numeros_aleatorios, int cantidad_de_medias){
    for (int i = *ref_tope_obstaculos; i < cantidad_de_medias; ++i){
        contador_numeros_aleatorios++;
        obstaculos[i].posicion = coordenadas_aleatorias[contador_numeros_aleatorios];
        obstaculos[i].tipo = MEDIAS;
        (*ref_tope_obstaculos)++;
    }
}

//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara las medias correspondientes al nivel, dandoles una coordenada aleatoria del vector coordenadas aleatorias y asignandoles el tipo "medias". Este solo se activara si el personaje del tp1 es olaf
void llenar_obstaculos_con_medias_olaf(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_medias(obstaculos, ref_tope_obstaculos, coordenadas_aleatorias, 0, CANTIDAD_DE_OBSTACULOS_OLAF_PRIMER_NIVEL);
	} else if (numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_medias(obstaculos, ref_tope_obstaculos, coordenadas_aleatorias, 0, CANTIDAD_DE_OBSTACULOS_OLAF_SEGUNDO_NIVEL);
	}
}

//Pre:Para inicializar correctamente, el vector coordenadas fuegos debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara las medias correspondientes al nivel, dandoles una coordenada aleatoria del vector coordenadas fuegos y asignandoles el tipo "fuego".
void llenar_obstaculos_con_fuegos(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS], int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_fuegos(obstaculos, ref_tope_obstaculos, coordenadas_fuegos, CANTIDAD_DE_FUEGOS_PRIMER_NIVEL);
	} else if (numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_fuegos(obstaculos, ref_tope_obstaculos, coordenadas_fuegos, CANTIDAD_DE_OBSTACULOS_SEGUNDO_NIVEL);
	} else{
        realizar_llenado_fuegos(obstaculos, ref_tope_obstaculos, coordenadas_fuegos, CANTIDAD_DE_OBSTACULOS_TERCER_NIVEL);
	}
}

//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara las medias correspondientes al nivel, dandoles una coordenada aleatoria del vector coordenadas aleatorias y asignandoles el tipo "medias".
void llenar_obstaculos_con_medias(objeto_t obstaculos[MAX_OBSTACULOS], int* ref_tope_obstaculos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_medias(obstaculos, ref_tope_obstaculos, coordenadas_aleatorias, 0, CANTIDAD_DE_OBSTACULOS_PRIMER_NIVEL);
	} else if (numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_medias(obstaculos, ref_tope_obstaculos, coordenadas_aleatorias, 0, CANTIDAD_DE_MEDIAS_SEGUNDO_NIVEL);
	} else{
        realizar_llenado_medias(obstaculos, ref_tope_obstaculos, coordenadas_aleatorias, 0, CANTIDAD_DE_MEDIAS_TERCER_NIVEL);
	}
}

void realizar_llenado_botellas(objeto_t herramientas[MAX_HERRAMIENTAS], int* ref_tope_herramientas, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int
contador_numeros_aleatorios, int cantidad_de_botellas){
    for (int i = 0; i < cantidad_de_botellas; ++i){
        herramientas[i].posicion = coordenadas_aleatorias[contador_numeros_aleatorios];
        herramientas[i].tipo = BOTELLAS_GRITOS;
        contador_numeros_aleatorios++;
        (*ref_tope_herramientas)++;
    }
}

//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara las botellas correspondientes al nivel , dandoles una coordenada aleatoria del vector coordenadas aleatorias y asignandoles el tipo "botellas gritos".
void llenar_herramientas_con_botellas(objeto_t herramientas[MAX_HERRAMIENTAS], int* ref_tope_herramientas, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS],int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_botellas(herramientas, ref_tope_herramientas, coordenadas_aleatorias, 6, CANTIDAD_DE_BOTELLAS_PRIMER_NIVEL);
	} else if(numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_botellas(herramientas, ref_tope_herramientas, coordenadas_aleatorias, 5, CANTIDAD_DE_BOTELLAS_SEGUNDO_NIVEL);
	} else{
        realizar_llenado_botellas(herramientas, ref_tope_herramientas, coordenadas_aleatorias, 4, CANTIDAD_DE_BOTELLAS_TERCER_NIVEL);
	}
}

void realizar_llenado_heramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int* ref_tope_herramientas, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int
contador_numeros_aleatorios, int cantidad_de_herramientas){
    for (int i = *ref_tope_herramientas; i < cantidad_de_herramientas; ++i){
        herramientas[i].posicion = coordenadas_aleatorias[contador_numeros_aleatorios];
        herramientas[i].tipo = AHUYENTA_RANDALL;
        (*ref_tope_herramientas)++;
        contador_numeros_aleatorios++;
    }
}
 
//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara los interruptores randall correspondientes al nivel , dandoles una coordenada aleatoria del vector coordenadas aleatorias y asignandoles el tipo "ahuyenta randall".
void llenar_herramientas_con_interruptores(objeto_t herramientas[MAX_HERRAMIENTAS], int* ref_tope_herramientas, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int numero_nivel){
	 if (numero_nivel == PRIMER_NIVEL){
         realizar_llenado_heramientas(herramientas, ref_tope_herramientas, coordenadas_aleatorias, 10, CANTIDAD_DE_HERRAMIENTAS_PRIMER_NIVEL);
	 } else if (numero_nivel == SEGUNDO_NIVEL){
         realizar_llenado_heramientas(herramientas, ref_tope_herramientas, coordenadas_aleatorias, 8, CANTIDAD_DE_HERRAMIENTAS_SEGUNDO_NIVEL);
	}
}

void realizar_llenado_papeleos(papeleo_t papeleos[MAX_PAPELEOS], int* ref_tope_papeleos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int contador_numeros_aleatorios, int
cantidad_de_papeleos){
    int id_papeleos = ID_PRIMER_PAPELEO;

    for (int i = 0; i < cantidad_de_papeleos; ++i){
        papeleos[i].posicion = coordenadas_aleatorias[contador_numeros_aleatorios];
        papeleos[i].id_papeleo = id_papeleos;
        papeleos[i].recolectado = NO_RECOLECTADO;
        contador_numeros_aleatorios++;
        id_papeleos++;
        (*ref_tope_papeleos)++;
    }
}

//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara los papeleos correspondientes al nivel, dandoles una coordenada aleatoria del vector coordenadas aleatorias, su id propio de cada papeleo y su estado de recoleccion.
void llenar_papeleos(papeleo_t papeleos[MAX_PAPELEOS], int* ref_tope_papeleos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int numero_nivel){
	if (numero_nivel == PRIMER_NIVEL){
        realizar_llenado_papeleos(papeleos, ref_tope_papeleos, coordenadas_aleatorias, 11, CANTIDAD_DE_PAPELEOS_PRIMER_NIVEL);
	} else if (numero_nivel == SEGUNDO_NIVEL){
        realizar_llenado_papeleos(papeleos, ref_tope_papeleos, coordenadas_aleatorias, 9, CANTIDAD_DE_PAPELEOS_SEGUNDO_NIVEL);
	} else {
        realizar_llenado_papeleos(papeleos, ref_tope_papeleos, coordenadas_aleatorias, 6, CANTIDAD_DE_PAPELEOS_TERCER_NIVEL);
	}
}

//Pre:Para inicializar correctamente, el vector coordenadas aleatorias debe estar cargado previamente con la cantidad de coordendas necesarias y la variable numero nivel debera tener un valor de entre 1 y 3 inclusives
//Pos:Procedimiento que inicializara los papeleos correspondientes al nivel con el personaje stitch, dandoles una coordenada aleatoria del vector coordenadas aleatorias, su id propio de cada papeleo y su estado de recoleccion. Esta funcion es exclusiva para cuando el personaje es Stitch.
void llenar_papeleos_stitch(papeleo_t papeleos[MAX_PAPELEOS], int* ref_tope_papeleos, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS]){
	int contador_numeros_aleatorios = 6;
	int id_papeleos = ID_PRIMER_PAPELEO;

	for (int i = 0; i < CANTIDAD_PAPELEOS_STITCH_TERCER_NIVEL; ++i){
		papeleos[i].posicion = coordenadas_aleatorias[contador_numeros_aleatorios];
		papeleos[i].id_papeleo = id_papeleos;
		papeleos[i].recolectado = NO_RECOLECTADO;
		contador_numeros_aleatorios++;
		id_papeleos++;
		(*ref_tope_papeleos)++;
	}
}

void inicializar_elementos_nivel_uno_dos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS]){

    if (personaje_tp1 == OLAF){
        llenar_obstaculos_con_medias_olaf(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_aleatorias, numero_nivel);
        llenar_obstaculos_con_fuegos_olaf(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_fuegos, numero_nivel);
    } else {
        llenar_obstaculos_con_fuegos(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_fuegos, numero_nivel);
        llenar_obstaculos_con_medias(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_aleatorias, numero_nivel);
    }

    llenar_herramientas_con_botellas(nivel->herramientas, &(nivel->tope_herramientas), coordenadas_aleatorias, numero_nivel);
    llenar_herramientas_con_interruptores(nivel->herramientas, &(nivel->tope_herramientas), coordenadas_aleatorias, numero_nivel);
    llenar_papeleos(nivel->papeleos, &(nivel->tope_papeleos), coordenadas_aleatorias, numero_nivel);
}

void inicializar_elementos_nivel_tres(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS],
 coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS]){
    llenar_obstaculos_con_medias(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_aleatorias, numero_nivel);
    llenar_obstaculos_con_fuegos(nivel->obstaculos, &(nivel->tope_obstaculos), coordenadas_fuegos, numero_nivel);
    llenar_herramientas_con_botellas(nivel->herramientas, &(nivel->tope_herramientas), coordenadas_aleatorias, numero_nivel);

    if (personaje_tp1 == STITCH){
        llenar_papeleos_stitch(nivel->papeleos, &(nivel->tope_papeleos), coordenadas_aleatorias);
    } else {
        llenar_papeleos(nivel->papeleos, &(nivel->tope_papeleos), coordenadas_aleatorias, numero_nivel);
    }

}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    nivel->tope_paredes = 0;
    nivel->tope_obstaculos = 0;
    nivel->tope_herramientas = 0;
    nivel->tope_papeleos = 0;

    obtener_paredes(numero_nivel, nivel->paredes, &(nivel->tope_paredes), &(nivel->pos_inicial_jugador));

    coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS];
    int tope_coord_aleatorias = 0;
    coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS];
    int tope_coord_fuegos = 0;

    obtener_coordenadas_aleatorias(coordenadas_aleatorias,nivel->paredes, &tope_coord_aleatorias, nivel->pos_inicial_jugador, nivel->tope_paredes, numero_nivel);
    obtener_coordenadas_fuegos(coordenadas_aleatorias, nivel->paredes, coordenadas_fuegos, tope_coord_aleatorias, &tope_coord_fuegos, nivel->pos_inicial_jugador, nivel->tope_paredes, numero_nivel);

    if (numero_nivel == PRIMER_NIVEL || numero_nivel == SEGUNDO_NIVEL){
        inicializar_elementos_nivel_uno_dos(nivel, numero_nivel, personaje_tp1, coordenadas_aleatorias, coordenadas_fuegos);
    } else {
        inicializar_elementos_nivel_tres(nivel, numero_nivel, personaje_tp1, coordenadas_aleatorias, coordenadas_fuegos);
    }
}

//Pre:la variable personaje_tp1 debe estar incializada con el personaje correspondiente del tp1
//Pos:devuelve la cantidad de martillos iniciales del primer nivel dependiendo del personaje del tp1 (si es jasmin contador_numeros_aleatorios no)
int define_martillos_iniciales_primer_nivel(char personaje_tp1){
	int martillos;
	if (personaje_tp1 == JASMIN){
		martillos = MARTILLOS_CON_JASMIN_PRIMER_NIVEL;
	} else {
		martillos = MARTILLOS_INICIALES_PRIMER_NIVEL;
	}

	return martillos;
}

//Pre:la variable personaje_tp1 debe estar incializada con el personaje correspondiente del tp1
//Pos:devuelve la cantidad de movimientos iniciales del primer nivel dependiendo del personaje del tp1 (si es rayo contador_numeros_aleatorios no)
int define_movimientos_iniciales_primer_nivel(char personaje_tp1){
	int movimientos;
	if (personaje_tp1 == RAYO_MCQUEEN){
		movimientos = MOVIMIENTOS_CON_RAYO_PRIMER_NIVEL;
	} else {
		movimientos = MOVIMIENTOS_INICIALES_PRIMER_NIVEL;
	} 

	return movimientos;
}

void inicializar_juego(juego_t* juego, char personaje_tp1){
	int numero_primer_nivel = PRIMER_NIVEL;	
	int numero_segundo_nivel = SEGUNDO_NIVEL;	
	int numero_tercer_nivel = TERCER_NIVEL;

	inicializar_nivel(&(juego->niveles[POSICION_PRIMER_NIVEL]), numero_primer_nivel, personaje_tp1);
	inicializar_nivel(&(juego->niveles[POSICION_SEGUNDO_NIVEL]), numero_segundo_nivel, personaje_tp1);
	inicializar_nivel(&(juego->niveles[POSICION_TERCER_NIVEL]), numero_tercer_nivel, personaje_tp1);	

	(juego)->nivel_actual = PRIMER_NIVEL;
	(juego)->personaje_tp1 = personaje_tp1;

	(juego)->jugador.posicion = juego->niveles[POSICION_PRIMER_NIVEL].pos_inicial_jugador;		
	(juego)->jugador.movimientos = define_movimientos_iniciales_primer_nivel(personaje_tp1);
	(juego)->jugador.martillos = define_martillos_iniciales_primer_nivel(personaje_tp1);
	(juego)->jugador.extintores = EXTINTORES_PRIMER_NIVEL;
	(juego)->jugador.ahuyenta_randall = RANDALL_PRIMER_NIVEL_DESACTIVADO;		
	(juego)->jugador.movimientos_realizados = SIN_MOVIMIENTOS;
}


void cargar_matriz_espacios_primer_nivel(char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL]){
    for (int i = 0; i < MAX_FILAS_PRIMER_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_PRIMER_NIVEL; ++j){
            mapa_primer_nivel[i][j] = ESPACIO_VACIO_MATRIZ;
        }
    }
}

void cargar_matriz_espacios_segundo_nivel(char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL]){
    for (int i = 0; i < MAX_FILAS_SEGUNDO_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_SEGUNDO_NIVEL; ++j){
            mapa_segundo_nivel[i][j] = ESPACIO_VACIO_MATRIZ;
        }
    }
}

void cargar_matriz_espacios_tercer_nivel(char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL]){
    for (int i = 0; i < MAX_FILAS_TERCER_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_TERCER_NIVEL; ++j){
            mapa_tercer_nivel[i][j] = ESPACIO_VACIO_MATRIZ;
        }
    }
}

//Pre:el nivel actual debe tener un valor de entre 1 y 3 inclusives
//Pos:carga los elementos sin ocupar de la matriz para evitar que haya basura en ella y la devuelve
void cargar_matriz_espacios(char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
        cargar_matriz_espacios_primer_nivel(mapa_primer_nivel);
	} else if (nivel_actual == SEGUNDO_NIVEL){
        cargar_matriz_espacios_segundo_nivel(mapa_segundo_nivel);
	} else {
        cargar_matriz_espacios_tercer_nivel(mapa_tercer_nivel);
	}
}


void cargar_paredes_primer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_PRIMER_NIVEL].tope_paredes; ++i){
        mapa_primer_nivel[niveles[POSICION_PRIMER_NIVEL].paredes[i].fil][niveles[POSICION_PRIMER_NIVEL].paredes[i].col] = PARED;
    }
}

void cargar_paredes_segundo_nivel(nivel_t niveles[MAX_NIVELES], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL]){
    for (int i = 0; i < niveles[POSICION_SEGUNDO_NIVEL].tope_paredes; ++i){
        mapa_segundo_nivel[niveles[POSICION_SEGUNDO_NIVEL].paredes[i].fil][niveles[POSICION_SEGUNDO_NIVEL].paredes[i].col] = PARED;
    }
}

void cargar_paredes_tercer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_TERCER_NIVEL].tope_paredes; ++i){
        mapa_tercer_nivel[niveles[POSICION_TERCER_NIVEL].paredes[i].fil][niveles[POSICION_TERCER_NIVEL].paredes[i].col] = PARED;
    }
}

//Pre:el vector paredes debe estar previamente inicializado para poder cargarlo a la matriz y el nivel actual debe tener un valor de entre 1 y 3 inclusives
//Pos:carga las paredes del nivel dado en su matriz correspondiente y devuelve la matriz cargada
void cargar_matriz_con_paredes(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
        cargar_paredes_primer_nivel(niveles, mapa_primer_nivel);
	} else if(nivel_actual == SEGUNDO_NIVEL){
        cargar_paredes_segundo_nivel(niveles, mapa_segundo_nivel);
	} else {
        cargar_paredes_tercer_nivel(niveles, mapa_tercer_nivel);
	}
}


void cargar_obstaculos_primer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_PRIMER_NIVEL].tope_obstaculos; ++i){
        mapa_primer_nivel[niveles[POSICION_PRIMER_NIVEL].obstaculos[i].posicion.fil][niveles[POSICION_PRIMER_NIVEL].obstaculos[i].posicion.col] = niveles[POSICION_PRIMER_NIVEL].obstaculos[i].tipo;
    }
}

void cargar_obstaculos_segundo_nivel(nivel_t niveles[MAX_NIVELES], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL]){
    for (int i = 0; i < niveles[POSICION_SEGUNDO_NIVEL].tope_obstaculos; ++i){
        mapa_segundo_nivel[niveles[POSICION_SEGUNDO_NIVEL].obstaculos[i].posicion.fil][niveles[POSICION_SEGUNDO_NIVEL].obstaculos[i].posicion.col] = niveles[POSICION_SEGUNDO_NIVEL].obstaculos[i].tipo;
    }
}

void cargar_obstaculos_tercer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_TERCER_NIVEL].tope_obstaculos; ++i){
        mapa_tercer_nivel[niveles[POSICION_TERCER_NIVEL].obstaculos[i].posicion.fil][niveles[POSICION_TERCER_NIVEL].obstaculos[i].posicion.col] = niveles[POSICION_TERCER_NIVEL].obstaculos[i].tipo;
    }
}

//Pre:el vector obstaculos debe estar previamente inicializado para poder cargarlo a la matriz y el nivel actual debe tener un valor de entre 1 y 3 inclusives
//Pos:carga los obstaculos del nivel dado en su matriz correspondiente y devuelve la matriz cargada
void cargar_matriz_con_obstaculos(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
        cargar_obstaculos_primer_nivel(niveles, mapa_primer_nivel);
	} else if (nivel_actual == SEGUNDO_NIVEL){
        cargar_obstaculos_segundo_nivel(niveles, mapa_segundo_nivel);
	} else {
        cargar_obstaculos_tercer_nivel(niveles, mapa_tercer_nivel);
	}
}


void cargar_herramientas_primer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_PRIMER_NIVEL].tope_herramientas; ++i){
        mapa_primer_nivel[niveles[POSICION_PRIMER_NIVEL].herramientas[i].posicion.fil][niveles[POSICION_PRIMER_NIVEL].herramientas[i].posicion.col] = niveles[POSICION_PRIMER_NIVEL].herramientas[i].tipo;
    }
}

void cargar_herramientas_segundo_nivel(nivel_t niveles[MAX_NIVELES], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL]){
    for (int i = 0; i < niveles[POSICION_SEGUNDO_NIVEL].tope_herramientas; ++i){
        mapa_segundo_nivel[niveles[POSICION_SEGUNDO_NIVEL].herramientas[i].posicion.fil][niveles[POSICION_SEGUNDO_NIVEL].herramientas[i].posicion.col] = niveles[POSICION_SEGUNDO_NIVEL].herramientas[i].tipo;
    }
}

void cargar_herramientas_tercer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL]){
    for (int i = 0; i < niveles[POSICION_TERCER_NIVEL].tope_herramientas; ++i){
        mapa_tercer_nivel[niveles[POSICION_TERCER_NIVEL].herramientas[i].posicion.fil][niveles[POSICION_TERCER_NIVEL].herramientas[i].posicion.col] = niveles[POSICION_TERCER_NIVEL].herramientas[i].tipo;
    }
}

//Pre:el vector herramientas debe estar previamente inicializado para poder cargarlo a la matriz y el nivel actual debe tener un valor de entre 1 y 3 inclusives
//Pos:carga las herramientas del nivel dado en su matriz correspondiente y devuelve la matriz cargada
void cargar_matriz_con_herramientas(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
        cargar_herramientas_primer_nivel(niveles, mapa_primer_nivel);
	} else if (nivel_actual == SEGUNDO_NIVEL){
        cargar_herramientas_segundo_nivel(niveles, mapa_segundo_nivel);
	} else {
        cargar_herramientas_tercer_nivel(niveles, mapa_tercer_nivel);
	}
}

//Pre:la posicion inicial debe estar previamente inicializada para poder cargarla a la matriz y el nivel actual debe tener un valor entre 1 y 3 inclusives
//Pos:carga la posicion inicial del jugador en el nivel dado en la matriz correspondiente y la devuelve cargada.
void cargar_matriz_con_pos(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual, coordenada_t posicion){
	if (nivel_actual == PRIMER_NIVEL){
		mapa_primer_nivel[posicion.fil][posicion.col] = MIKE;
	} else if(nivel_actual == SEGUNDO_NIVEL){
		mapa_segundo_nivel[posicion.fil][posicion.col] = MIKE;
	} else{
		mapa_tercer_nivel[posicion.fil][posicion.col] = MIKE;
	}
}

void cargar_matriz_con_papeleos_primer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], int* id_papeleos){
    for (int i = 0; i < niveles[POSICION_PRIMER_NIVEL].tope_papeleos; ++i){
        if (!niveles[POSICION_PRIMER_NIVEL].papeleos[i].recolectado){
            mapa_primer_nivel[niveles[POSICION_PRIMER_NIVEL].papeleos[i].posicion.fil][niveles[POSICION_PRIMER_NIVEL].papeleos[i].posicion.col] = (char)(*id_papeleos);
        }
        (*id_papeleos)++;
    }
}

void cargar_matriz_con_papeleos_segundo_nivel(nivel_t niveles[MAX_NIVELES], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], int* id_papeleos){
    for (int i = 0; i < niveles[POSICION_SEGUNDO_NIVEL].tope_papeleos; ++i){
        if (!niveles[POSICION_SEGUNDO_NIVEL].papeleos[i].recolectado){
            mapa_segundo_nivel[niveles[POSICION_SEGUNDO_NIVEL].papeleos[i].posicion.fil][niveles[POSICION_SEGUNDO_NIVEL].papeleos[i].posicion.col] = (char)(*id_papeleos);
        }
        (*id_papeleos)++;
    }
}

void cargar_matriz_con_papeleos_tercer_nivel(nivel_t niveles[MAX_NIVELES], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int* id_papeleos){
    for (int i = 0; i < niveles[POSICION_TERCER_NIVEL].tope_papeleos; ++i){
        if (!niveles[POSICION_TERCER_NIVEL].papeleos[i].recolectado){
            mapa_tercer_nivel[niveles[POSICION_TERCER_NIVEL].papeleos[i].posicion.fil][niveles[POSICION_TERCER_NIVEL].papeleos[i].posicion.col] = (char)(*id_papeleos);
        }
        (*id_papeleos)++;
    }
}

//Pre:el vector papeleos debe estar previamente inicializado para poder cargarlo a la matriz y nivel actual debe tener un valor del 1 al 3 inclusives
//Pos:Carga la matriz con los papeleos correspondientes al nivel dado
void cargar_matriz_con_papeleos(nivel_t niveles[MAX_NIVELES], char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual){
	int id_papeleos = '1';

	if (nivel_actual == PRIMER_NIVEL){
        cargar_matriz_con_papeleos_primer_nivel(niveles, mapa_primer_nivel, &id_papeleos);
	} else if (nivel_actual == SEGUNDO_NIVEL){
        cargar_matriz_con_papeleos_segundo_nivel(niveles, mapa_segundo_nivel, &id_papeleos);
	} else {
        cargar_matriz_con_papeleos_tercer_nivel(niveles, mapa_tercer_nivel, &id_papeleos);
	}
}

void imprimir_primer_nivel(char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL]){
    for (int i = 0; i < MAX_FILAS_PRIMER_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_PRIMER_NIVEL; ++j){
            printf(" %c", mapa_primer_nivel[i][j]);
        }
        printf("\n");
    }
}

void imprimir_segundo_nivel(char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL]){
    for (int i = 0; i < MAX_FILAS_SEGUNDO_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_SEGUNDO_NIVEL; ++j){
            printf(" %c", mapa_segundo_nivel[i][j]);
        }
        printf("\n");
    }
}

void imprimir_tercer_nivel(char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL]){
    for (int i = 0; i < MAX_FILAS_TERCER_NIVEL; ++i){
        for (int j = 0; j < MAX_COLUMNAS_TERCER_NIVEL; ++j){
            printf(" %c", mapa_tercer_nivel[i][j]);
        }
        printf("\n");
    }
}

//Pre:La matriz correspondiente al nivel debe estar cargada con todas sus caracteristicas y nivel actual debera tener un valor del 1 al 3 inclusives
//Pos:Imprime la matriz en pantalla, con todas las caracteristicas del nivel correspondiente
void imprimir_juego(char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL], char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL], char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL], int nivel_actual, int extintores, int martillos, int movimientos, int movimientos_realizados){

	printf("Nivel actual: %i    ", nivel_actual);
	printf("Movimientos realizados: %i 	 ", movimientos_realizados);
	printf("Movimientos restantes: %i 	", movimientos);
	printf("Extintores restantes: %i 	", extintores);
	printf("Martillos restantes: %i\n\n", martillos);

	if (nivel_actual == PRIMER_NIVEL){
        imprimir_primer_nivel(mapa_primer_nivel);
	} else if (nivel_actual == SEGUNDO_NIVEL){
        imprimir_segundo_nivel(mapa_segundo_nivel);
	} else {
        imprimir_tercer_nivel(mapa_tercer_nivel);
	}
}

void imprimir_terreno(juego_t juego){

	char mapa_primer_nivel[MAX_FILAS_PRIMER_NIVEL][MAX_COLUMNAS_PRIMER_NIVEL];
	char mapa_segundo_nivel[MAX_FILAS_SEGUNDO_NIVEL][MAX_COLUMNAS_SEGUNDO_NIVEL];
	char mapa_tercer_nivel[MAX_FILAS_TERCER_NIVEL][MAX_COLUMNAS_TERCER_NIVEL];
	

	cargar_matriz_espacios(mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual);
	cargar_matriz_con_paredes(juego.niveles, mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual);
	cargar_matriz_con_obstaculos(juego.niveles, mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual);
	cargar_matriz_con_herramientas(juego.niveles, mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual);
	cargar_matriz_con_papeleos(juego.niveles, mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual);
	cargar_matriz_con_pos(juego.niveles, mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual, juego.jugador.posicion);
	imprimir_juego(mapa_primer_nivel, mapa_segundo_nivel, mapa_tercer_nivel, juego.nivel_actual, juego.jugador.extintores, juego.jugador.martillos, juego.jugador.movimientos, juego.jugador.movimientos_realizados);
}

//Pre:-
//Post: Imprime en pantalla en mensaje de error de movimiento
void imprimir_error_movimiento(){
	printf("No te podes mover para ese lado\n");
}

//Pre:-
//Post: Imprime en pantalla los controles del juego
void imprimir_controles(){
	printf("CONTROLES DEL JUEGO\n");
	printf("Mover o martillar/extinguir a izquierda: A\n");
	printf("Mover o martillar/extinguir a derecha: D\n");
	printf("Martillar/extinguir hacia arriba: W\n");
	printf("Martillar hacia abajo: S\n");
	printf("Mov. rotacional horario: E\n");
	printf("Mov. rotacional antihorario: Q\n");
	printf("Utilizar extintor: C\n");
	printf("Utilizar martillo: Z\n");
	printf("\n");
}

//Pre: Debe recibir un vector de teclas validas vacio y su respectivo tope
//Post: Devuelve el vector de teclas validas lleno con las teclas de los controles del juego
void inicializar_teclas_validas(char teclas_validas[MAX_TECLAS_VALIDAS], int* tope_teclas_validas){

	teclas_validas[POSICION_ROTACION_HORARIO] = ROTAR_MAPA_HORARIO;
	teclas_validas[POSICION_ROTACIOON_ANTIHORARIO] = ROTAR_MAPA_ANTIHORARIO;
	teclas_validas[POSICION_USAR_EXTINTOR] = USAR_EXTINTOR;
	teclas_validas[POSICION_USAR_MARTILLO] = USAR_MARTILLO;				
	teclas_validas[POSICION_DERECHA] = DERECHA;
	teclas_validas[POSICION_IZQUIERDA] = IZQUIERDA;
	teclas_validas[POSICION_ARRIBA] = ARRIBA;
	teclas_validas[POSICION_ABAJO] = ABAJO;
	(*tope_teclas_validas) = CANTIDAD_TECLAS_VALIDAS;
}

//Pre: Debe recibir la accion realizada por el usuario
//Post: Devuelve true en el caso de que la accion realizada sea valida (cualquiera de las teclas validas) o false en caso de que no
bool accion_realizada_es_invalida(char accion_realizada){
	char teclas_validas[MAX_TECLAS_VALIDAS];
	int tope_teclas_validas = 0;
	bool es_invalida = true;
	inicializar_teclas_validas(teclas_validas, &tope_teclas_validas);

	for (int i = 0; i < CANTIDAD_TECLAS_VALIDAS_INICIALES; ++i){
		if (accion_realizada == teclas_validas[i]){
			es_invalida = false;
		}
	}
	return es_invalida;
}

//Pre: Debe recibir la accion realizada por el usuario
//Post: Devuelve true si la accion realizada es utilizar una herramienta(Z,C) y false en caso contrario
bool accion_realizada_usa_herramienta(char accion_realizada){
	return (accion_realizada == USAR_EXTINTOR || accion_realizada == USAR_MARTILLO);
}

//Pre: Debe recibir la accion realizada por el usuario
//Post: Devuelve true si la accion realizada es moverse (A,D) y false en caso contrario
bool accion_realizada_es_movimiento(char accion_realizada){
	return (accion_realizada == DERECHA || accion_realizada == IZQUIERDA);
}

//Pre: Debe recibir la accion realizada por el usuario
//Post: Devuelve true si la accion realizada es rotar el mapa y false en caso contrario
bool accion_realizada_es_rotacion(char accion_realizada){
	return(accion_realizada == ROTAR_MAPA_HORARIO || accion_realizada == ROTAR_MAPA_ANTIHORARIO);
}

//Pre: Debe recibir la accion realizada por el usuario
//Post: Devuelve true si la accion secundaria realizada es invalida (fuera de A,S,D,W ) y false en caso contrario
bool accion_secundaria_realizada_es_invalida(char accion_realizada){
	char teclas_validas[MAX_TECLAS_VALIDAS];
	int tope_teclas_validas = 0;
	bool es_invalida = true;
	inicializar_teclas_validas(teclas_validas, &tope_teclas_validas);

	for (int i = POSICION_DERECHA; i < tope_teclas_validas; ++i){
		if (accion_realizada == teclas_validas[i]){
			es_invalida = false;
		}
	}
	return es_invalida;
}

//Pre: Debe recibir una variable para guardar la accion ingresada por el usuario
//Post: Devuelve la variable recibida con el valor que ingreso el usuario. Siempre devuelve una accion valida
void pedir_accion(char* accion_realizada){
	printf("Ingresa una accion o movimiento... ");
	scanf(" %c", &(*accion_realizada));

	while(accion_realizada_es_invalida(*accion_realizada)){
		printf("La accion ingresada es invalida. Volve a intentar porfavor... ");
		scanf(" %c", &(*accion_realizada));
	}
}

//Pre: Debe recibir un nivel, la accion realizada y la variable jugador
//Post: Devuelve true en caso de que el movimiento sea imposible de realizar y false en caso contrario
bool movimiento_es_imposible(nivel_t nivel, char accion_realizada, jugador_t jugador){
	bool es_imposible = false;

	for (int i = 0; i < nivel.tope_paredes; ++i){
		if ((accion_realizada == DERECHA && jugador.posicion.fil == nivel.paredes[i].fil && (jugador.posicion.col+UNA_POSICION) == nivel.paredes[i].col) || (accion_realizada == IZQUIERDA && jugador.posicion.fil == nivel.paredes[i].fil && (jugador.posicion.col-UNA_POSICION) == nivel.paredes[i].col)){
            es_imposible = true;
		}
	}

	return es_imposible;
}

//Pre: Debe recibir un nivel y la variable jugador
//Post: Devuelve 0 si la posicion del jugador no choca con obstaculo, 1 si choca con un fuego y 2 si choca con media
int comprueba_si_choco_obstaculo(nivel_t nivel, jugador_t jugador){
	int obstaculo_chocado = NO_CHOCO;

	for (int i = 0; i < nivel.tope_obstaculos; ++i){
		if (jugador.posicion.fil == nivel.obstaculos[i].posicion.fil && jugador.posicion.col == nivel.obstaculos[i].posicion.col && nivel.obstaculos[i].tipo == FUEGOS){
			obstaculo_chocado = CHOCO_FUEGO;
		} else if (jugador.posicion.fil == nivel.obstaculos[i].posicion.fil && jugador.posicion.col == nivel.obstaculos[i].posicion.col && nivel.obstaculos[i].tipo == MEDIAS){
			obstaculo_chocado = CHOCO_MEDIA;
		}
	} 
	return obstaculo_chocado;
}

//Pre: Debe recibir un nivel y la variable jugador
//Post: Devuelve 0 si la posicion del jugador no choca con herramienta, 1 si choca con botella y 2 si choca con interruptor
int comprueba_si_choco_herramienta(nivel_t nivel, jugador_t jugador){
	int herramienta_chocada = NO_CHOCO;

	for (int i = 0; i < nivel.tope_herramientas; ++i){
		if (jugador.posicion.fil == nivel.herramientas[i].posicion.fil && jugador.posicion.col == nivel.herramientas[i].posicion.col && nivel.herramientas[i].tipo == BOTELLAS_GRITOS){
			herramienta_chocada = CHOCO_BOTELLA;
		} else if (jugador.posicion.fil == nivel.herramientas[i].posicion.fil && jugador.posicion.col == nivel.herramientas[i].posicion.col && nivel.herramientas[i].tipo == AHUYENTA_RANDALL){
			herramienta_chocada = CHOCO_INTERRUPTOR;
		}
	} 
	return herramienta_chocada;
}

//Pre: Debe recibir un nivel y la variable jugador
//Post: Devuelve -1 en caso de que el jugador no haya chocado ningun papeleo y en caso de que si haya chocado, devuelve la posicion en el vector papeleos del papeleo chocado.
int comprueba_si_choco_papeleo(nivel_t nivel, jugador_t jugador){
	int posicion_papeleo_chocado = NO_CHOCO_PAPELEO;
	for (int i = 0; i < nivel.tope_papeleos; ++i){
		if (jugador.posicion.fil == nivel.papeleos[i].posicion.fil && jugador.posicion.col == nivel.papeleos[i].posicion.col){
			posicion_papeleo_chocado = i;
		}
	}
	return posicion_papeleo_chocado;
}


//Pre: Debe recibir un nivel y la posicion del papeleo chocado. Posicion_papeleo_chocado debe ser mayor o igual a 0
bool papeleos_anteriores_fueron_recogidos(int posicion_papeleo_chocado, nivel_t nivel){
	bool papeleos_anteriores_fueron_recogidos = true;

	for (int i = 0; i < posicion_papeleo_chocado; ++i){
		if (!nivel.papeleos[i].recolectado){
			papeleos_anteriores_fueron_recogidos = false;
		}
	}
	return papeleos_anteriores_fueron_recogidos;
}

//Pre: Debe recibir la variable movimientos, del jugador
//Post: Resta los movimientos por chocar el fuego e imprime en pantalla su respectivo mensaje
void ejecutar_choque_con_fuego(int* movimientos){
	(*movimientos) = MOVIMIENTOS_AL_CHOCAR_FUEGO;
	printf("Se ha chocado un fuego! Perdiste el juego.	");
}

//Pre: Debe recibir la variable movimientos, del jugador
//Post: Suma los movimientos por chocar el botella e imprime en pantalla su respectivo mensaje
void ejecutar_choque_con_botella(int* movimientos){
	(*movimientos) = (*movimientos) + MOVIMIENTOS_GANADOS_POR_BOTELLA;
	printf("Se ha chocado una botella de gritos! Ganaste 7 movimientos extra	\n");
}

//Pre: Debe recibir la variable movimientos, del jugador
//Post: Resta los movimientos por chocar la media e imprime en pantalla su respectivo mensaje
void ejecutar_choque_con_media(int* movimientos){
	(*movimientos) = (*movimientos) - MOVIMIENTOS_PERDIDOS_POR_MEDIA;
	printf("Se ha chocado una media! Perdiste 10 movimientos    \n");
}

//Pre: Debe recibir la posicion del papeleo chocado (mayor o igual a 0) y el vector de papeleos
//Post: En caso de que el papeleo chocado no tenga sus anteriores ya recogidos, imprime un mensaje de error por pantalla. En caso contrario, elimina logicamente el papeleo marcando como true la variable recolectado.
void recoger_papeleo(papeleo_t* papeleo, int posicion_papeleo_chocado){
	if(!(*papeleo).recolectado) printf("El papaleo %i ha sido recolectado \n", (posicion_papeleo_chocado+1));
	(*papeleo).recolectado = true;
}

//Pre: Debe recibir la variable ahuyenta_randall
//Post: Activa o desactiva los ahuyenta randall dependiendo de su estado anterior.
void accionar_interruptor_ahuyenta_randall(bool* ahuyenta_randall){
	if ((*ahuyenta_randall) == false){
		(*ahuyenta_randall) = true;
		printf("El interruptor ahuyenta Randall ha sido activado!\n");
	} else{
		(*ahuyenta_randall) = false;
		printf("El interruptor ahuyenta Randall ha sido desactivado!\n");
	}
}

//Pre: Debe recibir la variable juego
//Post: Ejecuta las consecuencias que puede provocar un movimiento, como chocarse los distintos objetos del juego
void ejecutar_consecuencia_de_movimiento(juego_t* juego){		
	int obstaculo_chocado = comprueba_si_choco_obstaculo((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], (*juego).jugador);
	if (obstaculo_chocado == CHOCO_FUEGO){
		ejecutar_choque_con_fuego(&(*juego).jugador.movimientos);
	} else if (obstaculo_chocado == CHOCO_MEDIA){
		ejecutar_choque_con_media(&(*juego).jugador.movimientos);
	}

	int herramienta_chocada = comprueba_si_choco_herramienta((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], (*juego).jugador);
	if (herramienta_chocada == CHOCO_BOTELLA){
		ejecutar_choque_con_botella(&(*juego).jugador.movimientos);
	} else if (herramienta_chocada == CHOCO_INTERRUPTOR){
		accionar_interruptor_ahuyenta_randall(&(*juego).jugador.ahuyenta_randall);
	}

	int posicion_papeleo_chocado = comprueba_si_choco_papeleo((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], (*juego).jugador);
	if (posicion_papeleo_chocado >= POSICION_PRIMER_PAPELEO){
		if (papeleos_anteriores_fueron_recogidos(posicion_papeleo_chocado, (*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL])){
			recoger_papeleo(&(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].papeleos[posicion_papeleo_chocado], posicion_papeleo_chocado);
		} else{
			printf("Este papeleo no se puede recoger porque todavia no recogiste los anteriores!	\n");
		}
	}
}

//Pre: Debe recibir la variable juego
//Post: Devuelve true en caso de que el personaje este parado sobre una pared y false en caso contrario
bool personaje_tiene_piso(juego_t juego){
	bool tiene_piso = false;

	for (int i = 0; i < juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].tope_paredes; ++i){
		if(juego.jugador.posicion.col == juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].paredes[i].col && juego.jugador.posicion.fil+1 == juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].paredes[i].fil){
			tiene_piso = true;
		}
	}

	return tiene_piso;
}

//Pre: Debe recibir la variable juego
//Post: Aplica la gravedad en caso de que el personaje no este parado sobre una pared
void aplicar_gravedad(juego_t* juego){
	while(!personaje_tiene_piso((*juego))){
		((*juego).jugador.posicion.fil)++;
		ejecutar_consecuencia_de_movimiento(juego);
		imprimir_terreno((*juego));
		detener_el_tiempo(TIEMPO_DE_CAIDA);
	}
}

//Pre: Debe recibir el nivel actual y la cantidad de movimientos realizados
//Post: Devuelve true en caso de que se deba generar una pared random y false en caso contrario
bool se_debe_generar_pared(int nivel_actual, int movimientos_realizados){
    return ((nivel_actual == PRIMER_NIVEL && movimientos_realizados < MOVIMIENTOS_LIMITES_PARA_PAREDES_PRIMER_NIVEL) || (nivel_actual == SEGUNDO_NIVEL && movimientos_realizados <
    MOVIMIENTOS_LIMITES_PARA_PAREDES_SEGUNDO_NIVEL) || (nivel_actual == TERCER_NIVEL && movimientos_realizados < MOVIMIENTOS_LIMITES_PARA_PAREDES_TERCER_NIVEL));
}

//Pre: Debe recibir el nivel actual, los movimientos realizados, y la variable ahuyenta randall
//Post: Devuelve true en caso de que se tenga que mover un papeleo y false en caso contrario
bool se_debe_mover_papeleo(int nivel_actual, int movimientos_realizados, bool ahuyenta_randall){
    return ((!ahuyenta_randall && nivel_actual == PRIMER_NIVEL && (movimientos_realizados % R_PRIMER_NIVEL) == ES_DIVISIBLE) || (!ahuyenta_randall && nivel_actual == SEGUNDO_NIVEL &&
    (movimientos_realizados % R_SEGUNDO_NIVEL) == ES_DIVISIBLE) || (!ahuyenta_randall && nivel_actual == TERCER_NIVEL && (movimientos_realizados % R_TERCER_NIVEL) == ES_DIVISIBLE));
}

//Pre: Debe recibir la variable juego
//Post: En caso de que un papeleo se tenga que mover, lo mueve a una coordenada aleatoria
void mover_papeleo(juego_t* juego){
	int papeleo_seleccionado = selecciona_papeleo_random((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].tope_papeleos);
	while((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].papeleos[papeleo_seleccionado].recolectado){
		papeleo_seleccionado = selecciona_papeleo_random((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].tope_papeleos);
	}
	(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].papeleos[papeleo_seleccionado].posicion = genera_coordenada_random(&(*juego));
}

//Pre: Debe recibir la variable juego, el vector de paredes y su respectivo tope
//Post: Genera una pared random y la incluye en el vector de paredes
void generar_pared_random(coordenada_t paredes[MAX_PAREDES], int* tope_paredes, juego_t* juego){
	paredes[(*tope_paredes)] = genera_coordenada_random(&(*juego));
	(*tope_paredes)++;
}

//Pre: Debe recibir la variable juego
//Post: Ejecuta las consecuencias indirectas de moverse
void ejecutar_consecuencias_indirectas_de_movimiento(juego_t* juego){
    aplicar_gravedad(&(*juego));

	if(se_debe_generar_pared((*juego).nivel_actual, (*juego).jugador.movimientos_realizados)){
		generar_pared_random((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].paredes, &(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].tope_paredes, juego);
	}

	if (se_debe_mover_papeleo((*juego).nivel_actual, (*juego).jugador.movimientos_realizados, (*juego).jugador.ahuyenta_randall)){
		mover_papeleo(juego);
	}
}

//Pre: Debe recibir la accion realizada y la variable juego
//Post: En caso del movimiento sea imposible de realizada imprime error, y en caso contrario ejecuta un movimiento y todas sus consecuencias
void ejecutar_movimiento(char accion_realizada, juego_t* juego){
	if(movimiento_es_imposible((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], accion_realizada, (*juego).jugador)){
		imprimir_error_movimiento();
	} else{
		if (accion_realizada == DERECHA){
			(*juego).jugador.posicion.col++;
			(*juego).jugador.movimientos--;
			(*juego).jugador.movimientos_realizados++;
			ejecutar_consecuencia_de_movimiento(juego);							
			ejecutar_consecuencias_indirectas_de_movimiento(&(*juego));		
		} else{
			(*juego).jugador.posicion.col--;
			(*juego).jugador.movimientos--;
			(*juego).jugador.movimientos_realizados++;
			ejecutar_consecuencia_de_movimiento(juego);
			ejecutar_consecuencias_indirectas_de_movimiento(&(*juego));
		}
	}		
}


void definir_fuego_superior_a_apagar(int* fuego_a_apagar, nivel_t nivel, jugador_t jugador){
    for (int i = 0; i < nivel.tope_obstaculos; ++i){
        if(nivel.obstaculos[i].tipo == FUEGOS && nivel.obstaculos[i].posicion.fil == (jugador.posicion.fil-UNA_POSICION) && nivel.obstaculos[i].posicion.col == jugador.posicion.col){
            (*fuego_a_apagar) = i;
        }
    }
}

void definir_fuego_inferior_a_apagar(int* fuego_a_apagar, nivel_t nivel, jugador_t jugador){
    for (int i = 0; i < nivel.tope_obstaculos; ++i){
        if(nivel.obstaculos[i].tipo == FUEGOS && nivel.obstaculos[i].posicion.fil == (jugador.posicion.fil+UNA_POSICION) && nivel.obstaculos[i].posicion.col == jugador.posicion.col){
            (*fuego_a_apagar) = i;
        }
    }
}

void definir_fuego_derecho_a_apagar(int* fuego_a_apagar, nivel_t nivel, jugador_t jugador){
    for (int i = 0; i < nivel.tope_obstaculos; ++i){
        if(nivel.obstaculos[i].tipo == FUEGOS && nivel.obstaculos[i].posicion.fil == jugador.posicion.fil && nivel.obstaculos[i].posicion.col == (jugador.posicion.col+UNA_POSICION)){		//CONVERTIR EN CONSTANTE
            (*fuego_a_apagar) = i;
        }
    }
}

void definir_fuego_izquierdo_a_apagar(int* fuego_a_apagar, nivel_t nivel, jugador_t jugador){
    for (int i = 0; i < nivel.tope_obstaculos; ++i){
        if(nivel.obstaculos[i].tipo == FUEGOS && nivel.obstaculos[i].posicion.fil == jugador.posicion.fil && nivel.obstaculos[i].posicion.col == (jugador.posicion.col-UNA_POSICION)){
            (*fuego_a_apagar) = i;
        }
    }
}

//Pre: Debe recibir la accion realizada, el nivel y la variable jugador
//Post: Devuelve -1 en caso de que no haya fuego a apagar en la direccion ingresada por el usuario y si no, devuelve la posicion del fuego a apagar en el vector de fuegos del respectivo nivel
int comprueba_si_hay_fuego(char accion_realizada, nivel_t nivel, jugador_t jugador){
	int fuego_a_apagar = NO_HAY_FUEGO;

	if (accion_realizada == ARRIBA){
        definir_fuego_superior_a_apagar(&fuego_a_apagar, nivel, jugador);
	} else if(accion_realizada == ABAJO){
        definir_fuego_inferior_a_apagar(&fuego_a_apagar, nivel, jugador);
	} else if(accion_realizada == DERECHA){
        definir_fuego_derecho_a_apagar(&fuego_a_apagar, nivel, jugador);
	} else{
        definir_fuego_izquierdo_a_apagar(&fuego_a_apagar, nivel, jugador);
	}

	return fuego_a_apagar;
}

void definir_limites_mapa(int* ultima_fila_jugable, int* ultima_columna_jugable,int valor_ultima_fila_jugable,int valor_ultima_columna_jugable){
    (*ultima_fila_jugable) = valor_ultima_fila_jugable;
    (*ultima_columna_jugable) = valor_ultima_columna_jugable;
}

void definir_pared_superior_a_destruir(int* pared_a_destruir, nivel_t nivel, jugador_t jugador, int ultima_columna_jugable){
    for (int i = 0; i < nivel.tope_paredes; ++i){
        if(jugador.posicion.fil != PRIMERA_FILA_JUGABLE && nivel.paredes[i].fil == (jugador.posicion.fil-UNA_POSICION) && nivel.paredes[i].col == jugador.posicion.col){
            (*pared_a_destruir) = i;
        }
    }
}

void definir_pared_inferior_a_destruir(int* pared_a_destruir, nivel_t nivel, jugador_t jugador, int ultima_fila_jugable){
    for (int i = 0; i < nivel.tope_paredes; ++i){
        if(jugador.posicion.fil != ultima_fila_jugable && nivel.paredes[i].fil == (jugador.posicion.fil+UNA_POSICION) && nivel.paredes[i].col == jugador.posicion.col){
            (*pared_a_destruir) = i;
        }
    }
}

void definir_pared_derecha_a_destruir(int* pared_a_destruir, nivel_t nivel, jugador_t jugador, int ultima_columna_jugable){
    for (int i = 0; i < nivel.tope_paredes; ++i){
        if(jugador.posicion.col != ultima_columna_jugable && nivel.paredes[i].fil == jugador.posicion.fil && nivel.paredes[i].col == (jugador.posicion.col+UNA_POSICION)){
            (*pared_a_destruir) = i;
        }
    }
}

void definir_pared_izquierda_a_destruir(int* pared_a_destruir, nivel_t nivel, jugador_t jugador){
    for (int i = 0; i < nivel.tope_paredes; ++i){
        if(jugador.posicion.col != PRIMERA_COLUMNA_JUGABLE && nivel.paredes[i].fil == jugador.posicion.fil && nivel.paredes[i].col == (jugador.posicion.col-UNA_POSICION)){
            (*pared_a_destruir) = i;
        }
    }
}

void definir_mapa(int* ultima_fila_jugable, int* ultima_columna_jugable, int nivel_actual){
    if (nivel_actual == PRIMER_NIVEL){
        definir_limites_mapa(&(*ultima_fila_jugable), &(*ultima_columna_jugable), ULTIMA_FILA_JUGABLE_PRIMER_NIVEL, ULTIMA_COLUMNA_JUGABLE_PRIMER_NIVEL);
    } else if(nivel_actual == SEGUNDO_NIVEL){
        definir_limites_mapa(&(*ultima_fila_jugable), &(*ultima_columna_jugable), ULTIMA_FILA_JUGABLE_SEGUNDO_NIVEL, ULTIMA_COLUMNA_JUGABLE_SEGUNDO_NIVEL);
    } else{
        definir_limites_mapa(&(*ultima_fila_jugable), &(*ultima_columna_jugable), ULTIMA_FILA_JUGABLE_TERCER_NIVEL, ULTIMA_COLUMNA_JUGABLE_TERCER_NIVEL);
    }
}

//Pre: Debe recibir la accion realizada, el nivel, la variable jugador y el nivel actual
//Post: Devuelve -1 si no hay pared para destruir en la direccion dada por el usuario o si la pared seleccionada es no destruible, si no, devuelve la posicion en el vector paredes de la pared a destruir
int comprueba_si_hay_pared(char accion_realizada, nivel_t nivel, jugador_t jugador, int nivel_actual){
	int pared_a_destruir = NO_HAY_PARED;
	int ultima_columna_jugable;
	int ultima_fila_jugable;

    definir_mapa(&ultima_fila_jugable, &ultima_columna_jugable, nivel_actual);

	if (accion_realizada == ARRIBA){
        definir_pared_superior_a_destruir(&pared_a_destruir, nivel, jugador, ultima_columna_jugable);
	} else if(accion_realizada == ABAJO){
        definir_pared_inferior_a_destruir(&pared_a_destruir, nivel, jugador, ultima_fila_jugable);
	} else if(accion_realizada == DERECHA){
        definir_pared_derecha_a_destruir(&pared_a_destruir, nivel, jugador, ultima_columna_jugable);
	} else{
        definir_pared_izquierda_a_destruir(&pared_a_destruir, nivel, jugador);
	}
	return pared_a_destruir;
}

//Pre:Debe recibir la accion realizada
//Post: Pregunta al usuario la accion secundaria a realizar (hacia que lado quiere usar la herramienta) y devuelve el valor cargado en accion_realizada
void pedir_accion_secundaria(char* accion_realizada){
	if ((*accion_realizada) == USAR_EXTINTOR){
		printf("Vas a usar un extintor. Ingresa hacia donde deseas usarlo... ");
		scanf(" %c", &(*accion_realizada));

		while(accion_secundaria_realizada_es_invalida((*accion_realizada))){
			printf("La tecla ingresada es incorrecta. Ingresa nuevamente hacia donde queres usar el extintor... ");
			scanf(" %c", &(*accion_realizada));
		}
	} else{
		printf("Vas a usar un martillo. Ingresa hacia donde deseas usarlo... ");
		scanf(" %c", &(*accion_realizada));

		while(accion_secundaria_realizada_es_invalida((*accion_realizada))){
			printf("La tecla ingresada es incorrecta. Ingresa nuevamente hacia donde queres usar el martillo... ");
			scanf(" %c", &(*accion_realizada));
		}
	}
}

//Pre: Debe recibir un nivel y la posicion de la pared a destruir en el vector de paredes. La posicion_pared_destruida debe ser igual o mayor a 0
//Post: Elimina del vector paredes la pared seleccionada por el usuario e imprime un aviso en pantalla
void eliminar_pared(nivel_t* nivel, int posicion_pared_destruida){
	(*nivel).paredes[posicion_pared_destruida] = (*nivel).paredes[(*nivel).tope_paredes-1];
	(*nivel).tope_paredes--;
	printf("Has destruido la pared!\n");
}

//Pre: Debe recibir un nivel y la posicion del fuego a apagar (siempre mayor o igual a 0) en el vector obstaculos.
//Post: Elimina el fuego seleccionado del vector de obstaculos.
void eliminar_fuego(nivel_t* nivel, int posicion_fuego_apagar){ 
	for (int i = posicion_fuego_apagar; i < ((*nivel).tope_obstaculos-1); ++i){
		(*nivel).obstaculos[i] = (*nivel).obstaculos[i+1];
	}
    (*nivel).tope_obstaculos--;
	printf("Has extinguido el fuego!\n");
}

//Pre: Debe recibir la accion realizada por el jugador y la variable juego
//Post: Activa la eliminacion de una pared en caso de que esa pared pueda ser eliminada y luego aplica la gravedad. En caso de que no se pueda hacer, imprime un mensaje de error por pantalla
void utilizar_martillo(char accion_realizada,juego_t* juego){
	int posicion_pared_destruida = comprueba_si_hay_pared(accion_realizada, (*juego).niveles[(*juego).nivel_actual-1], (*juego).jugador, (*juego).nivel_actual);	
	if(posicion_pared_destruida >= POSICION_PRIMERA_PARED){				
		eliminar_pared(&(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], posicion_pared_destruida);
		(*juego).jugador.martillos--;
		aplicar_gravedad(&(*juego));
	} else{
		printf("No podes usar un martillo hacia ese lado! \n");
	}
}

//Pre: Debe recibir la accion realizada y la variable juego
//Post: Activa la eliminacion de un fuego o imprime en pantalla un mensaje de error en caso de que eso no sea posible
void utilizar_extintor(char accion_realizada,juego_t* juego){
	int posicion_fuego_apagar = comprueba_si_hay_fuego(accion_realizada, (*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], (*juego).jugador);		
	if(posicion_fuego_apagar >= POSICION_PRIMER_OBSTACULO){				
		eliminar_fuego(&(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], posicion_fuego_apagar);
		(*juego).jugador.extintores--;
	} else{
		printf("No podes usar un extintor ahi! \n");
	}
}

//Pre: Debe recibir la accion realizada y la variable juego.
//Post: Utiliza la herramienta seleccionada en la accion realizada, utilizando todas las funciones aparte. En caso de que el jugador no tenga mas de la herramienta seleccionada, imprime un error por pantalla.
void ejecutar_uso_de_herramienta(char accion_realizada, juego_t* juego){
	if (accion_realizada == USAR_EXTINTOR){
		if ((*juego).jugador.extintores > SIN_HERRAMIENTAS){
			pedir_accion_secundaria(&accion_realizada);
			utilizar_extintor(accion_realizada, juego);
		} else{
			printf("No tenes mas extintores!\n");
		} 
	} else if(accion_realizada == USAR_MARTILLO){
		if ((*juego).jugador.martillos > SIN_HERRAMIENTAS){
			pedir_accion_secundaria(&accion_realizada);
			utilizar_martillo(accion_realizada, juego);
		} else{
			printf("No tenes mas martillos!\n");
		}
	}
}

void ejecutar_rotacion_horaria_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int desplazamiento){
    for (int i = 0; i < tope_paredes; ++i){
        int fila_auxiliar = paredes[i].fil;
        paredes[i].fil = paredes[i].col;
        paredes[i].col = abs(fila_auxiliar - desplazamiento);
    }
}

void ejecutar_rotacion_antihoraria_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int desplazamiento){
    for (int i = 0; i < tope_paredes; ++i){
        int columna_auxiliar = paredes[i].col;
        paredes[i].col = paredes[i].fil;
        paredes[i].fil = abs(columna_auxiliar - desplazamiento);
    }
}

//Pre: Debe recibir el vector de paredes junto a su tope, la accion realizada y el nivel actual.
//Post: Rotara las paredes del mapa hacia el lado ingresado por el usuario
void rotar_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, char accion_realizada, int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_paredes(paredes, tope_paredes, LIMITE_POSICION_FILAS_PRIMER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_paredes(paredes, tope_paredes, LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
		}
	} else if(nivel_actual == SEGUNDO_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_paredes(paredes, tope_paredes, LIMITE_POSICION_FILAS_SEGUNDO_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_paredes(paredes, tope_paredes, LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL);
		}
	} else{
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_paredes(paredes, tope_paredes, LIMITE_POSICION_FILAS_TERCER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_paredes(paredes, tope_paredes, LIMITE_POSICION_COLUMNAS_TERCER_NIVEL);
		}
	}
}

void ejecutar_rotacion_horaria_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, int desplazamiento){
    for (int i = 0; i < tope_obstaculos; ++i){
        int fila_auxiliar = obstaculos[i].posicion.fil;
        obstaculos[i].posicion.fil = obstaculos[i].posicion.col;
        obstaculos[i].posicion.col = abs(fila_auxiliar - desplazamiento);
    }
}

void ejecutar_rotacion_antihoraria_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, int desplazamiento){
    for (int i = 0; i < tope_obstaculos; ++i){
        int columna_auxiliar = obstaculos[i].posicion.col;
        obstaculos[i].posicion.col = obstaculos[i].posicion.fil;
        obstaculos[i].posicion.fil = abs(columna_auxiliar - desplazamiento);
    }
}

//Pre: Debe recibir el vector de obstaculos junto a su tope, la accion realizada y el nivel actual.
//Post: Rotara los obstaculos del mapa hacia el lado ingresado por el usuario
void rotar_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, char accion_realizada, int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_FILAS_PRIMER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
		}
	} else if(nivel_actual == SEGUNDO_NIVEL){
        if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_FILAS_SEGUNDO_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL);
		}
	} else{
        if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_FILAS_TERCER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_obstaculos(obstaculos, tope_obstaculos, LIMITE_POSICION_COLUMNAS_TERCER_NIVEL);
		}
	}
}

void ejecutar_rotacion_horaria_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int desplazamiento){
    for (int i = 0; i < tope_herramientas; ++i){
        int fila_auxiliar = herramientas[i].posicion.fil;
        herramientas[i].posicion.fil = herramientas[i].posicion.col;
        herramientas[i].posicion.col = abs(fila_auxiliar - desplazamiento);
    }
}

void ejecutar_rotacion_antihoraria_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int desplazamiento){
    for (int i = 0; i < tope_herramientas; ++i){
        int columna_auxiliar = herramientas[i].posicion.col;
        herramientas[i].posicion.col = herramientas[i].posicion.fil;
        herramientas[i].posicion.fil = abs(columna_auxiliar - desplazamiento);
    }
}

//Pre: Debe recibir el vector de herramientas junto a su tope, la accion realizada y el nivel actual.
//Post: Rotara las herramientas del mapa hacia el lado ingresado por el usuario
void rotar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, char accion_realizada, int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_FILAS_PRIMER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
		}
	} else if(nivel_actual == SEGUNDO_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_FILAS_SEGUNDO_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL);
		}
	} else{
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_horaria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_FILAS_TERCER_NIVEL);
		} else{
            ejecutar_rotacion_antihoraria_herramientas(herramientas, tope_herramientas, LIMITE_POSICION_COLUMNAS_TERCER_NIVEL);
		}
	}
}

void ejecutar_rotacion_papeleos_horario(papeleo_t papeleos[MAX_HERRAMIENTAS], int tope_papeleos, int desplazamiento){
    for (int i = 0; i < tope_papeleos; ++i){
        if (!papeleos[i].recolectado){
            int fila_auxiliar = papeleos[i].posicion.fil;
            papeleos[i].posicion.fil = papeleos[i].posicion.col;
            papeleos[i].posicion.col = abs(fila_auxiliar - desplazamiento);
        }
    }
}

void ejecutar_rotacion_papeleos_antihorario(papeleo_t papeleos[MAX_HERRAMIENTAS], int tope_papeleos, int desplazamiento){
    for (int i = 0; i < tope_papeleos; ++i){
        if(!papeleos[i].recolectado){
            int columna_auxiliar = papeleos[i].posicion.col;
            papeleos[i].posicion.col = papeleos[i].posicion.fil;
            papeleos[i].posicion.fil = abs(columna_auxiliar - LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
        }
    }
}

//Pre: Debe recibir el vector de papeleos junto a su tope, la accion realizada y el nivel actual.
//Post: Rotara los papeleos del mapa hacia el lado ingresado por el usuario
void rotar_papeleos(papeleo_t papeleos[MAX_HERRAMIENTAS], int tope_papeleos, char accion_realizada, int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_papeleos_horario(papeleos, tope_papeleos, LIMITE_POSICION_FILAS_PRIMER_NIVEL);
		} else{
            ejecutar_rotacion_papeleos_antihorario(papeleos, tope_papeleos, LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
		}
	} else if(nivel_actual == SEGUNDO_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_papeleos_horario(papeleos, tope_papeleos, LIMITE_POSICION_FILAS_SEGUNDO_NIVEL);
		} else{
            ejecutar_rotacion_papeleos_antihorario(papeleos, tope_papeleos, LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL);
		}
	} else{
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_papeleos_horario(papeleos, tope_papeleos, LIMITE_POSICION_FILAS_TERCER_NIVEL);
		} else{
            ejecutar_rotacion_papeleos_antihorario(papeleos, tope_papeleos, LIMITE_POSICION_COLUMNAS_TERCER_NIVEL);
		}
	}
}

void ejecutar_rotacion_correspondiente(jugador_t* jugador, char accion_realizada, int limite){
    if (accion_realizada == ROTAR_MAPA_HORARIO){
        int fila_auxiliar = (*jugador).posicion.fil;
        (*jugador).posicion.fil = (*jugador).posicion.col;
        (*jugador).posicion.col = abs(fila_auxiliar - limite);
    } else{
        int columna_auxiliar = (*jugador).posicion.col;
        (*jugador).posicion.col = (*jugador).posicion.fil;
        (*jugador).posicion.fil = abs(columna_auxiliar - limite);
    }
}

//Pre: Debe recibir la variable jugador, la accion realizada y el nivel actual.
//Post: Rotará el jugador hacia el lado ingresado por el usuario
void rotar_jugador(jugador_t* jugador, char accion_realizada, int nivel_actual){
	if (nivel_actual == PRIMER_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_FILAS_PRIMER_NIVEL);
		} else{
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_COLUMNAS_PRIMER_NIVEL);
		}
	} else if(nivel_actual == SEGUNDO_NIVEL){
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_FILAS_SEGUNDO_NIVEL);
		} else{
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_COLUMNAS_SEGUNDO_NIVEL);
		}
	} else{
		if (accion_realizada == ROTAR_MAPA_HORARIO){
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_FILAS_TERCER_NIVEL);
		} else{
            ejecutar_rotacion_correspondiente(jugador, accion_realizada, LIMITE_POSICION_COLUMNAS_TERCER_NIVEL);
		}
	}
}

//Pre: Debe recibir las variables juego, jugador, nivel, accion_realizada, nivel actual y juego
//Post: Ejecutara la rotacion del mapa entero y luego aplicara las consecuencias indirectas por moverse
void ejecutar_rotacion_de_mapa(jugador_t* jugador, nivel_t* nivel, char accion_realizada, int nivel_actual, juego_t* juego){
	(*jugador).movimientos--;
	(*jugador).movimientos_realizados++;
	rotar_paredes((*nivel).paredes, (*nivel).tope_paredes, accion_realizada, nivel_actual);
	rotar_obstaculos((*nivel).obstaculos, (*nivel).tope_obstaculos, accion_realizada, nivel_actual);
	rotar_herramientas((*nivel).herramientas, (*nivel).tope_herramientas, accion_realizada, nivel_actual);
	rotar_papeleos((*nivel).papeleos, (*nivel).tope_papeleos, accion_realizada, nivel_actual);
	rotar_jugador(jugador, accion_realizada, nivel_actual);	
	ejecutar_consecuencias_indirectas_de_movimiento(juego);
}

//Pre: Debe recibir la variable accion realizada y la variable juego
//Post: Ejecuta la accion ingresada dependiendo de si es un movimiento, una rotacion o el uso de una herramienta
void ejecutar_accion(char accion_realizada, juego_t* juego){
	if (accion_realizada_es_movimiento(accion_realizada)){
		ejecutar_movimiento(accion_realizada, juego);
	} else if (accion_realizada_usa_herramienta(accion_realizada)){
		ejecutar_uso_de_herramienta(accion_realizada, juego);
	} else if (accion_realizada_es_rotacion(accion_realizada)){
		ejecutar_rotacion_de_mapa(&(*juego).jugador, &(*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL], accion_realizada, (*juego).nivel_actual, juego);
	}
}

void realizar_jugada(juego_t* juego){
	char accion_realizada;
	imprimir_controles();
	pedir_accion(&accion_realizada);
	ejecutar_accion(accion_realizada, juego);
}

int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
	int estado = GANADO;

	for (int i = 0; i < tope_papeleos; ++i){
		if(!papeleos[i].recolectado){
			estado = JUGANDO;
		}
	}
	return estado;
}	


//Pre: Debe recibir los movimientos actuales del jugador
//Post: Devuelve true en caso de que el jugador se haya quedado sin movimientos y false en caso contrario
bool jugador_sin_movimientos(int movimientos){
	return(movimientos <= SIN_MOVIMIENTOS);
}

int estado_juego(juego_t juego){
	int estado;

	if(juego.nivel_actual != TERCER_NIVEL && !jugador_sin_movimientos(juego.jugador.movimientos)){
		estado = JUGANDO;
	} else if(estado_nivel(juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].papeleos, juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].tope_papeleos) == JUGANDO && jugador_sin_movimientos(juego.jugador.movimientos)){
		estado = PERDIDO;
	} else if(juego.nivel_actual == TERCER_NIVEL && estado_nivel(juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].papeleos, juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].tope_papeleos) == JUGANDO){
		estado = JUGANDO;
	} else if(juego.nivel_actual == TERCER_NIVEL && estado_nivel(juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].papeleos, juego.niveles[juego.nivel_actual-DESFASAJE_NIVEL].tope_papeleos) == GANADO){
		estado = GANADO;
	}

	return estado;
}
