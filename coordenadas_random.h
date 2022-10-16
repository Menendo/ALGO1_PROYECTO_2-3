#ifndef _coordenadas_random_h_
#define _coordenadas_random_h_
#include "utiles.h"
#include "papeleo.h"


#define MAX_COORD_ALEATORIAS 50

//Pre:el vector paredes debe estar inicializado previamente, junto con la posicion inicial y el tope paredes y la variable numero nivel debe tener un valor de entre 1 y 3 inclusives.
//Pos:devuelve el vector coordenadas aleatorias lleno con sus coordenadas de su respectivo mapa asegurandose que no se superpongan con nada
void obtener_coordenadas_aleatorias(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES],int* ref_tope_coord_aleatorias, coordenada_t pos_inicial_jugador,int tope_paredes, int numero_nivel);

//Pre:el vector paredes debe estar inicializado previamente, junto con la posicion inicial y el tope paredes y la variable numero nivel debe tener un valor de entre 1 y 3 inclusives.
//Pos:devuelve el vector coordenadas fuegos con coordenadas aleatorias dentro del mapa correspondiente con la particularidad de que estas son adyacentes y que no se superponen con nada
void obtener_coordenadas_fuegos(coordenada_t coordenadas_aleatorias[MAX_COORD_ALEATORIAS], coordenada_t paredes[MAX_PAREDES], coordenada_t coordenadas_fuegos[MAX_COORD_ALEATORIAS], int  tope_coord_aleatorias, int* ref_tope_coord_fuegos22x22,coordenada_t pos_inicial_jugador,int tope_paredes, int numero_nivel);

//Pre: la variable juego debe estar inicializada
//Post: devuelve una coordenada con valores aleatorios entre una franja definida dependiendo del nivel que no coincide con ningun objeto del mapa
coordenada_t genera_coordenada_random(juego_t* juego);

//Pre: Debe recibir la variable tope papeleos
//Post: Devuelve un numero aleatorio entre 0 y tope_papeleos
int selecciona_papeleo_random(int tope_papeleos);

#endif