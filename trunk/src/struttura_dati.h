/**
@file
Strutture dati comuni all'intero programma
*/

#include <allegro5/allegro.h>

/**
Struttura di un singolo elemento da mostrare.
Questa struttura comprende la posizione, le dimensioni e il bitmap dell'elemento.
Viene utilizzata dal modulo view.cc per creare la schermata da mostrare
*/
struct elemento {
	float posX;
	float posY;
	float altezza;
	float larghezza;
	ALLEGRO_BITMAP* bitmap;
	}

/**
Array di elemento.
La funzione ::main lo passa alla view.cc per creare la schermata da mostrare
*/
typedef elemento* elementi;


const int FPS = 60; /**< Frame per secondo.*/


