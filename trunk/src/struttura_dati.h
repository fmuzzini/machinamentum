/**
@file
Strutture dati comuni all'intero programma
*/

#ifndef STRUTTURA_DATI
#define STRUTTURA_DATI

#include <allegro5/allegro.h>

/**
Struttura di un singolo elemento da mostrare.
Questa struttura comprende la posizione, le dimensioni e il bitmap dell'elemento.
Viene utilizzata dal modulo view.cc per creare la schermata da mostrare
*/
struct elemento {
	float posX;
	float posY;
	ALLEGRO_BITMAP* bitmap;
	};


/**
Array di elemento.
Il controller (stati.cc) lo passa alla view.cc per creare la schermata da mostrare
*/
typedef elemento* elementi;

struct bitmap_renderizzato{
	ALLEGRO_BITMAP* bitmap;
	int larghezza;
	int altezza;
};

#endif
