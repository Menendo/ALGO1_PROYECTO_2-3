#include "test_personalidad.h"
#include <stdio.h>
#include "papeleo.h"
#include <stdlib.h>
#include <time.h>

static const int DESFASAJE_NIVEL = 1;
static const int POSICION_SEGUNDO_NIVEL = 1;
static const int POSICION_TERCER_NIVEL = 2;
static const int SEGUNDO_NIVEL = 2;
static const int TERCER_NIVEL = 3;

static const int SIN_MOVIMIENTOS = 0;	
const int PERDIDO = -1;
const int GANADO = 1;
const int JUGANDO = 0;

const int MOVIMIENTOS_INICIALES_SEGUNDO_NIVEL = 30;
const int MOVIMIENTOS_INICIALES_TERCER_NIVEL = 20;
const int MARTILLOS_SEGUNDO_NIVEL = 5;
const int EXTINTORES_SEGUNDO_NIVEL = 2;
const int MARTILLOS_TERCER_NIVEL = 6;
const int EXTINTORES_TERCER_NIVEL = 2;

const int MARTILLOS_SEGUNDO_NIVEL_JASMIN = 6;
const int MARTILLOS_TERCER_NIVEL_JASMIN = 7;

//Pre: Debe recibir la variable juego por parametro para hacer los respectivos cambios.
//Post: Aumentara el nivel_actual y seteara las reglas y las condiciones propias de ese nivel.
void pasar_de_nivel(juego_t* juego){
	juego->nivel_actual++;

	if ((juego)->personaje_tp1 == JASMIN){

		if ((juego)->nivel_actual == SEGUNDO_NIVEL){

			(juego)->jugador.posicion = juego->niveles[POSICION_SEGUNDO_NIVEL].pos_inicial_jugador;		
			(juego)->jugador.movimientos = ((juego)->jugador.movimientos + MOVIMIENTOS_INICIALES_SEGUNDO_NIVEL);
			(juego)->jugador.martillos = MARTILLOS_SEGUNDO_NIVEL_JASMIN;
			(juego)->jugador.extintores = EXTINTORES_SEGUNDO_NIVEL;
			(juego)->jugador.ahuyenta_randall = true;
			(juego)->jugador.movimientos_realizados = SIN_MOVIMIENTOS;

		} else if ((juego)->nivel_actual == TERCER_NIVEL){

			(juego)->jugador.posicion = juego->niveles[POSICION_TERCER_NIVEL].pos_inicial_jugador;		
			(juego)->jugador.movimientos = ((juego)->jugador.movimientos + MOVIMIENTOS_INICIALES_TERCER_NIVEL);;
			(juego)->jugador.martillos = MARTILLOS_TERCER_NIVEL_JASMIN;
			(juego)->jugador.extintores = EXTINTORES_TERCER_NIVEL;
			(juego)->jugador.ahuyenta_randall = true;
			(juego)->jugador.movimientos_realizados = SIN_MOVIMIENTOS;
		}
	} else{
		if ((juego)->nivel_actual == SEGUNDO_NIVEL){

			(juego)->jugador.posicion = juego->niveles[POSICION_SEGUNDO_NIVEL].pos_inicial_jugador;		
			(juego)->jugador.movimientos = ((juego)->jugador.movimientos + MOVIMIENTOS_INICIALES_SEGUNDO_NIVEL);
			(juego)->jugador.martillos = MARTILLOS_SEGUNDO_NIVEL;
			(juego)->jugador.extintores = EXTINTORES_SEGUNDO_NIVEL;
			(juego)->jugador.ahuyenta_randall = true;
			(juego)->jugador.movimientos_realizados = SIN_MOVIMIENTOS;

		} else if ((juego)->nivel_actual == TERCER_NIVEL){

			(juego)->jugador.posicion = juego->niveles[POSICION_TERCER_NIVEL].pos_inicial_jugador;		
			(juego)->jugador.movimientos = ((juego)->jugador.movimientos + MOVIMIENTOS_INICIALES_TERCER_NIVEL);;
			(juego)->jugador.martillos = MARTILLOS_TERCER_NIVEL;
			(juego)->jugador.extintores = EXTINTORES_TERCER_NIVEL;
			(juego)->jugador.ahuyenta_randall = true;
			(juego)->jugador.movimientos_realizados = SIN_MOVIMIENTOS;
		}
	}
}


//Pre: Debe recibir la variable juego con todo seteado en el primer nivel.
//Post: Se ocupa de manejar el flujo del juego, cambiar los niveles y dar el juego por perdido o ganado.
void correr_juego(juego_t* juego){

	while(estado_juego((*juego)) == JUGANDO && estado_nivel((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].papeleos, (*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].tope_papeleos) == JUGANDO){
		realizar_jugada(juego);
		imprimir_terreno((*juego));

		if (estado_juego((*juego)) == JUGANDO && estado_nivel((*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].papeleos, (*juego).niveles[(*juego).nivel_actual-DESFASAJE_NIVEL].tope_papeleos) == GANADO){
			pasar_de_nivel(juego);
			imprimir_terreno((*juego));
		} else if (estado_juego((*juego)) == PERDIDO){
			printf("Perdiste.\n");
		} else if (estado_juego((*juego)) == GANADO){
			printf("Felicitaciones. ¡Has completado el juego!\n");
		}
	}
}

int main(){

	juego_t juego;
	char inicial_personaje_ayuda;

	srand (( unsigned)time(NULL));
	ejecutar_test_personaje(&inicial_personaje_ayuda);
	void inicializar_controlador();
	inicializar_juego(&juego, inicial_personaje_ayuda);
	imprimir_terreno(juego);
	correr_juego(&juego);

	void terminar_controlador();

 return 0; 

}