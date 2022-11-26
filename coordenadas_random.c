#include "coordenadas_random.h"
#include "papeleo.h"
#include <stdbool.h>
#include <stdlib.h>
#include "utiles.h"

const int COORDENADAS_ALEATORIAS_NECESITADAS_PRIMER_NIVEL = 12;
const int COORDENADAS_FUEGOS_NECESITADAS_PRIMER_NIVEL = 10;
const int AMPLITUD_DE_RANGO_PRIMER_NIVEL = 21;
const int DISTANCIA_ADYACENTE = 1;
const int VALOR_MINIMO_PRIMER_NIVEL = 1;
const int COORDENADAS_ALEATORIAS_NECESITADAS_SEGUNDO_NIVEL = 11;
const int COORDENADAS_FUEGOS_NECESITADAS_SEGUNDO_NIVEL = 5;
const int AMPLITUD_DE_RANGO_SEGUNDO_NIVEL = 16;
const int VALOR_MINIMO_SEGUNDO_NIVEL = 1;
const int COORDENADAS_ALEATORIAS_NECESITADAS_TERCER_NIVEL = 9;
const int COORDENADAS_FUEGOS_NECESITADAS_TERCER_NIVEL = 3;
const int AMPLITUD_DE_RANGO_TERCER_NIVEL = 11;
const int VALOR_MINIMO_TERCER_NIVEL = 1;
static const int PRIMER_NIVEL = 1;
static const int SEGUNDO_NIVEL = 2;
const int VALOR_MINIMO_PAPELEOS = 0;
const int PRIMERA_POSICION_VECTOR = 0;

#define MAX_COORD_ALEATORIAS 50

//Pre:Debe ser dada una coordenada aleatoria y el vector de coordenadas aleatorias junto a su tope para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada no coincide con ninguna coordenada del vector coordenadas_aleatorias y false en el caso de que si lo haga
bool coordenada_no_coincide_coordenadas(coordenada_t coordenada_aleatoria, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS],int* ref_tope_coord_aleatorias){
	bool no_coincide = true;

	int i = 0;
	while(i < (*ref_tope_coord_aleatorias)){
		if (coordenada_aleatoria.fil == coordenadas_aleatorias[i].fil && coordenada_aleatoria.col == coordenadas_aleatorias[i].col){
			no_coincide = false;
		} i++;
	}	
    
    return no_coincide;
}

//Pre:Debe ser dada una una coordenada aleatoria y el vector de paredes junto a su tope para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada no coincide con ninguna coordenada de ninguna pared y false en el caso de que si lo haga
bool coordenada_no_coincide_paredes(coordenada_t coordenada_aleatoria, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
	bool no_coincide = true;
	
	int i = 0;
	while(i < tope_paredes){
		if(coordenada_aleatoria.fil == paredes[i].fil && coordenada_aleatoria.col == paredes[i].col){
			no_coincide = false;	
		}i++;
	} 
    
    return no_coincide;
}

//Pre:Debe ser dada  una coordenada aleatoria y la posicion inicial del jugador en el nivel para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada no coincide con la posicion inicial del jugador en el nivel y false en el caso de que si lo haga
bool coordenada_coincide_pos_inicial(coordenada_t coordenada_aleatoria, coordenada_t pos_inicial_jugador){
    return (coordenada_aleatoria.fil == pos_inicial_jugador.fil && coordenada_aleatoria.col == pos_inicial_jugador.col);
}

//Pre:Debe ser dada una una coordenada fuego aleatoria y el vector de coordenadas aleatorias junto a su tope para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada para los fuegos no coincide con ninguna de las coordenadas del vector coordenadas aleatorias y false en el caso de que si lo haga
bool fuego_no_coincide_coordenadas(coordenada_t coordenada_fuego, coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS],int tope_coord_aleatorias){
	bool no_coincide = true;
	int i = 0;

	while(i < (tope_coord_aleatorias)){
		if (coordenada_fuego.fil == coordenadas_aleatorias[i].fil && coordenada_fuego.col == coordenadas_aleatorias[i].col){
			no_coincide = false;
		} i++;
	}	
    
    return no_coincide;
}

//Pre:-Debe ser dada una una coordenada fuego aleatoria y el vector de paredes junto a su tope para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada para los fuegos no coincide con ninguna coordenada de ninguna pared y false en el caso de que si lo haga
bool fuego_no_coincide_paredes(coordenada_t coordenada_fuego, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
	bool no_coincide = true;

	int i = 0;

	while(i < tope_paredes){
		if(coordenada_fuego.fil == paredes[i].fil && coordenada_fuego.col == paredes[i].col){
			no_coincide = false;	
		}i++;
	} return no_coincide;
}

//Pre:-Debe ser dada una una coordenada aleatoria y la posicion inicial del jugador en el nivel para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada para los fuegos no coincide con la coordenada de la posicion inicial del jugador y false en el caso de que si lo haga
bool fuego_coincide_pos_inicial(coordenada_t coordenada_fuego, coordenada_t pos_inicial_jugador){
    return (coordenada_fuego.fil == pos_inicial_jugador.fil && coordenada_fuego.col == pos_inicial_jugador.col);
}

//Pre:-Debe ser dada una una coordenada fuego aleatoria y el vector de coordenadas fuegos junto a su tope para hacer la comparacion
//Pos:Devuelve True si la coordenada aleatoria generada para los fuegos no coincide con ninguna coordenada del vector coordenadas fuegos y false en el caso de que si lo haga
bool fuego_no_coincide_fuegos(coordenada_t coordenada_fuego, coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS],int* ref_tope_coord_fuegos){
	bool no_coincide = true;
	int i = 0;

	while(i < (*ref_tope_coord_fuegos)){
		if (coordenada_fuego.fil == coordenadas_fuegos[i].fil && coordenada_fuego.col == coordenadas_fuegos[i].col){
			no_coincide = false;
		} i++;
	}

    return no_coincide;
}

//Pre:-debe ser dada una coordenada fuego y el vector paredes junto con su tope para realizar la comparacion de distancia
//Pos:Devuelve True si la coordenada aleatoria generada para los fuegos esta a una distancia == 1 de una pared (siendo asi adyacente) y false en el caso de que no lo haga
bool fuego_adyacente_pared(coordenada_t coordenada_fuego, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
	bool fuego_es_adyacente = false;

	for (int i = 0; i < tope_paredes; ++i){
		int distancia = (abs(coordenada_fuego.fil - paredes[i].fil) + abs(coordenada_fuego.col - paredes[i].col));

		if (distancia == DISTANCIA_ADYACENTE) fuego_es_adyacente = true;
	}

    return fuego_es_adyacente;
}

//Pre:debe ser dado un vector de coordenadas aleatorias junto a su tope
//Pos:inicializa una coordenada random con valor 0 en ambos campos y lo asigna al vector coordenadas aleatorias para su correcto funcionamiento
void inicializar_coordenada_random(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], int** ref_tope_coord_aleatorias){
    coordenada_t coordenada_random;
    coordenada_random.fil = 0;
    coordenada_random.col = 0;
    coordenadas_aleatorias[PRIMERA_POSICION_VECTOR] = coordenada_random;
    (**ref_tope_coord_aleatorias) = 1;
}

void generar_coordenadas_aleatorias(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES],int* ref_tope_coord_aleatorias, coordenada_t
pos_inicial_jugador, int tope_paredes, int coordenadas_aleatorias_necesitadas, int amplitud_de_rango, int valor_minimo){
    for (int i = 0; i < coordenadas_aleatorias_necesitadas; ++i){
        coordenada_t coordenada_aleatoria;
        coordenada_aleatoria.fil = rand () % amplitud_de_rango + valor_minimo;
        coordenada_aleatoria.col = rand () % amplitud_de_rango + valor_minimo;

        while(!coordenada_no_coincide_paredes(coordenada_aleatoria, paredes, tope_paredes) || !coordenada_no_coincide_coordenadas(coordenada_aleatoria, coordenadas_aleatorias, ref_tope_coord_aleatorias) || coordenada_coincide_pos_inicial(coordenada_aleatoria, pos_inicial_jugador)){
            coordenada_aleatoria.fil = rand () % amplitud_de_rango + valor_minimo;
            coordenada_aleatoria.col = rand () % amplitud_de_rango + valor_minimo;
        }
        coordenadas_aleatorias[*ref_tope_coord_aleatorias] = coordenada_aleatoria;
        (*ref_tope_coord_aleatorias)++;
    }
}

void obtener_coordenadas_aleatorias(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES],int* ref_tope_coord_aleatorias, coordenada_t pos_inicial_jugador, int tope_paredes, int numero_nivel){
    inicializar_coordenada_random(coordenadas_aleatorias, &ref_tope_coord_aleatorias);
	if(numero_nivel == PRIMER_NIVEL){
        generar_coordenadas_aleatorias(coordenadas_aleatorias, paredes, ref_tope_coord_aleatorias, pos_inicial_jugador, tope_paredes, COORDENADAS_ALEATORIAS_NECESITADAS_PRIMER_NIVEL,AMPLITUD_DE_RANGO_PRIMER_NIVEL, VALOR_MINIMO_PRIMER_NIVEL);
	} else if(numero_nivel == SEGUNDO_NIVEL){
        generar_coordenadas_aleatorias(coordenadas_aleatorias, paredes, ref_tope_coord_aleatorias, pos_inicial_jugador, tope_paredes, COORDENADAS_ALEATORIAS_NECESITADAS_SEGUNDO_NIVEL,AMPLITUD_DE_RANGO_SEGUNDO_NIVEL, VALOR_MINIMO_SEGUNDO_NIVEL);
	} else {
        generar_coordenadas_aleatorias(coordenadas_aleatorias, paredes, ref_tope_coord_aleatorias, pos_inicial_jugador, tope_paredes, COORDENADAS_ALEATORIAS_NECESITADAS_TERCER_NIVEL,AMPLITUD_DE_RANGO_TERCER_NIVEL, VALOR_MINIMO_TERCER_NIVEL);
	}
}

void generar_coordenadas_fuegos(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES], coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS],int
tope_coord_aleatorias, int* ref_tope_coord_fuegos,coordenada_t pos_inicial_jugador, int tope_paredes, int amplitud_de_rango, int valor_minimo, int coordendas_fuegos_necesitadas){
    for (int i = 0; i < coordendas_fuegos_necesitadas; ++i){
        coordenada_t coordenada_fuego;
        coordenada_fuego.fil = rand () % amplitud_de_rango + valor_minimo;
        coordenada_fuego.col = rand () % amplitud_de_rango + valor_minimo;

        while(!fuego_no_coincide_paredes(coordenada_fuego, paredes, tope_paredes) || !fuego_no_coincide_coordenadas(coordenada_fuego, coordenadas_aleatorias, tope_coord_aleatorias) || fuego_coincide_pos_inicial(coordenada_fuego, pos_inicial_jugador)  || !fuego_no_coincide_fuegos(coordenada_fuego, coordenadas_fuegos, ref_tope_coord_fuegos) || !fuego_adyacente_pared(coordenada_fuego, paredes, tope_paredes)){
            coordenada_fuego.fil = rand () % amplitud_de_rango + valor_minimo;
            coordenada_fuego.col = rand () % amplitud_de_rango + valor_minimo;
        }
        coordenadas_fuegos[*ref_tope_coord_fuegos] = coordenada_fuego;
        (*ref_tope_coord_fuegos)++;
    }
}

void obtener_coordenadas_fuegos(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES], coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS],int  tope_coord_aleatorias, int* ref_tope_coord_fuegos,coordenada_t pos_inicial_jugador, int tope_paredes, int numero_nivel){
	if(numero_nivel == PRIMER_NIVEL){
        generar_coordenadas_fuegos(coordenadas_aleatorias, paredes, coordenadas_fuegos, tope_coord_aleatorias, ref_tope_coord_fuegos, pos_inicial_jugador, tope_paredes, AMPLITUD_DE_RANGO_PRIMER_NIVEL, VALOR_MINIMO_PRIMER_NIVEL, COORDENADAS_FUEGOS_NECESITADAS_PRIMER_NIVEL);
	} else if(numero_nivel == SEGUNDO_NIVEL){
        generar_coordenadas_fuegos(coordenadas_aleatorias, paredes, coordenadas_fuegos, tope_coord_aleatorias, ref_tope_coord_fuegos, pos_inicial_jugador, tope_paredes, AMPLITUD_DE_RANGO_SEGUNDO_NIVEL, VALOR_MINIMO_SEGUNDO_NIVEL, COORDENADAS_FUEGOS_NECESITADAS_SEGUNDO_NIVEL);
	} else {
        generar_coordenadas_fuegos(coordenadas_aleatorias, paredes, coordenadas_fuegos, tope_coord_aleatorias, ref_tope_coord_fuegos, pos_inicial_jugador, tope_paredes, AMPLITUD_DE_RANGO_TERCER_NIVEL, VALOR_MINIMO_TERCER_NIVEL, COORDENADAS_FUEGOS_NECESITADAS_TERCER_NIVEL);
	}
}

//Pre: Debe recibir la coordenada aleatoria, el vector de herramientas y su tope
//Post: Devuelve true en caso de que la coordenada aleatoria coincida con la coordenada de alguna herramienta y false en caso contrario
bool coordenada_coincide_herramienta(coordenada_t coordenada_random, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas){
	bool coincide = false;

	for (int i = 0; i < tope_herramientas; ++i){
		if (herramientas[i].posicion.fil == coordenada_random.fil && herramientas[i].posicion.col == coordenada_random.col){
			coincide = true;
		}
	}
	return coincide;
}

//Pre: Debe recibir la coordenada aleatoria, el vector de obstaculos y su tope
//Post: Devuelve true en caso de que la coordenada aleatoria coincida con la coordenada de algun obstaculo y false en caso contrario
bool coordenada_coincide_obstaculo(coordenada_t coordenada_random, objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){
	bool coincide = false;

	for (int i = 0; i < tope_obstaculos; ++i){
		if (obstaculos[i].posicion.fil == coordenada_random.fil && obstaculos[i].posicion.col == coordenada_random.col){
			coincide = true;
		}
	}
	return coincide;
}

//Pre: Debe recibir la coordenada aleatoria, el vector de papeleos y su tope
//Post: Devuelve true en caso de que la coordenada aleatoria coincida con la coordenada de algun papeleo y false en caso contrario
bool coordenada_coincide_papeleo(coordenada_t coordenada_random, papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
	bool coincide = false;

	for (int i = 0; i < tope_papeleos; ++i){
		if (papeleos[i].posicion.fil == coordenada_random.fil && papeleos[i].posicion.col == coordenada_random.col){
			coincide = true;
		}
	}
	return coincide;
}

//Pre: Debe recibir la coordenada aleatoria y la posicion del jugador en el mapa
//Post: Devuelve true en caso de que la coordenada aleatoria coincida con la coordenada de la posicion del jugador y false en caso contrario
bool coordenada_coincide_jugador(coordenada_t coordenada_random, coordenada_t posicion_jugador){
	return (coordenada_random.fil == posicion_jugador.fil && coordenada_random.col == posicion_jugador.col);
}

coordenada_t genera_coordenada_random(juego_t* juego){
	coordenada_t coordenada_random;
	if ((*juego).nivel_actual == PRIMER_NIVEL){
		coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_PRIMER_NIVEL + VALOR_MINIMO_PRIMER_NIVEL;
		coordenada_random.col = rand () % AMPLITUD_DE_RANGO_PRIMER_NIVEL + VALOR_MINIMO_PRIMER_NIVEL;

		while(!coordenada_no_coincide_paredes(coordenada_random, (*juego).niveles[0].paredes, (*juego).niveles[0].tope_paredes) || coordenada_coincide_herramienta(coordenada_random, (*juego).niveles[0].herramientas, (*juego).niveles[0].tope_herramientas) || coordenada_coincide_obstaculo(coordenada_random, (*juego).niveles[0].obstaculos, (*juego).niveles[0].tope_obstaculos) || coordenada_coincide_papeleo(coordenada_random, (*juego).niveles[0].papeleos, (*juego).niveles[0].tope_papeleos) || coordenada_coincide_jugador(coordenada_random, (*juego).jugador.posicion)){
			coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_PRIMER_NIVEL + VALOR_MINIMO_PRIMER_NIVEL;
			coordenada_random.col = rand () % AMPLITUD_DE_RANGO_PRIMER_NIVEL + VALOR_MINIMO_PRIMER_NIVEL;
		}

		return coordenada_random;
	} else if ((*juego).nivel_actual == SEGUNDO_NIVEL){
		coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_SEGUNDO_NIVEL + VALOR_MINIMO_SEGUNDO_NIVEL;
		coordenada_random.col = rand () % AMPLITUD_DE_RANGO_SEGUNDO_NIVEL + VALOR_MINIMO_SEGUNDO_NIVEL;

		while(!coordenada_no_coincide_paredes(coordenada_random, (*juego).niveles[1].paredes, (*juego).niveles[1].tope_paredes) || coordenada_coincide_herramienta(coordenada_random, (*juego).niveles[1].herramientas, (*juego).niveles[1].tope_herramientas) || coordenada_coincide_obstaculo(coordenada_random, (*juego).niveles[1].obstaculos, (*juego).niveles[1].tope_obstaculos) || coordenada_coincide_papeleo(coordenada_random, (*juego).niveles[1].papeleos, (*juego).niveles[1].tope_papeleos) || coordenada_coincide_jugador(coordenada_random, (*juego).jugador.posicion)){
			coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_SEGUNDO_NIVEL + VALOR_MINIMO_SEGUNDO_NIVEL;
			coordenada_random.col = rand () % AMPLITUD_DE_RANGO_SEGUNDO_NIVEL + VALOR_MINIMO_SEGUNDO_NIVEL;
		}

		return coordenada_random;
	} else{
		coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_TERCER_NIVEL + VALOR_MINIMO_TERCER_NIVEL;
		coordenada_random.col = rand () % AMPLITUD_DE_RANGO_TERCER_NIVEL + VALOR_MINIMO_TERCER_NIVEL;

		while(!coordenada_no_coincide_paredes(coordenada_random, (*juego).niveles[2].paredes, (*juego).niveles[2].tope_paredes) || coordenada_coincide_herramienta(coordenada_random, (*juego).niveles[2].herramientas, (*juego).niveles[2].tope_herramientas) || coordenada_coincide_obstaculo(coordenada_random, (*juego).niveles[2].obstaculos, (*juego).niveles[2].tope_obstaculos) || coordenada_coincide_papeleo(coordenada_random, (*juego).niveles[2].papeleos, (*juego).niveles[2].tope_papeleos) || coordenada_coincide_jugador(coordenada_random, (*juego).jugador.posicion)){
			coordenada_random.fil = rand () % AMPLITUD_DE_RANGO_TERCER_NIVEL + VALOR_MINIMO_TERCER_NIVEL;
			coordenada_random.col = rand () % AMPLITUD_DE_RANGO_TERCER_NIVEL + VALOR_MINIMO_TERCER_NIVEL;
		}

		return coordenada_random;
	}
}

int selecciona_papeleo_random(int tope_papeleos){
	return (rand () % (tope_papeleos) + VALOR_MINIMO_PAPELEOS);
}