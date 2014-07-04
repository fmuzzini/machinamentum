/**
@file
Modulo per l'accesso e il salvataggio dei dati durante l'esecuzione del programma
*/
#include <allegro5/allegro.h>
#include "struttura_dati.h"
#include "file_IO.h"
#include "accesso_dati.h"

/**
Struttura alla base della lista del replay.
Contiene il puntatore al bitmap e il puntatore al prossimo fotogramma,
questa struttura è utilizzata solo da questo modulo
*/
struct fotogramma{
	ALLEGRO_BITMAP* bitmap;
	fotogramma* prossimo;
};


static fotogramma* replay = NULL; 		/**< Puntatore alla testa della lista dei fotogrammi. */
static fotogramma* ultimo = NULL;		/**< Puntatore all'ultimo fotogramma. */
static int numero_fotogrammi = 0;		/**< Contatore numero fotogrammi inseriti. */
static const int secondi = 5; 			/**< Durata replay. */
static const int max_fotogrammi = secondi*FPS; 	/**< Massimo numero fotogrammi. */	


void buffer_replay(ALLEGRO_BITMAP* bitmap){
	//creo il nuovo fotogramma
	fotogramma* f = new fotogramma;
	f->bitmap = al_clone_bitmap(bitmap);
	f->prossimo = NULL;

	numero_fotogrammi++;
	
	//Se non ci sono ancora fotogrammi lo inserisco come primo	
	if (replay == NULL){
		replay = f;
		ultimo = f;
		return;
	}
	
	//Aggancio il fotogramma all'ultimo esistente e faccio puntare ultimo al fotogramma appena inserito
	ultimo->prossimo = f;
	ultimo = f;

	//Se ho raggiunto il massimo di fotogrammi elimino il più vecchio (quello in testa)
	if (numero_fotogrammi > max_fotogrammi){
		fotogramma* da_eliminare = replay;
		replay = replay->prossimo;
		al_destroy_bitmap(da_eliminare->bitmap);	//Bisogna eliminare anche il bitmap puntato dal fotogramma!
		delete da_eliminare;
		
	}
		
}

/*
Funzione da rivedere poichè il tipo ALLEGRO_BITMAP non contiene direttamente il bitmap ma ha dei puntatori a memoria dinamica.
Possibili soluzioni:
Utilizzare funzioni di libreria per il salvataggio su file, reindirizzando il salvataggio in un array per poi creare un unico file.
Creare un tipo apposito per la memorizzazione effettiva del bitmap, studiando a fondo il tipo ALLEGRO_BITMAP.
Ricordarsi di modificare anche la funzione replay_to_file()
*/
bool salva_replay(){
	//creo array di bitmap
	ALLEGRO_BITMAP* array_replay = new ALLEGRO_BITMAP[numero_fotogrammi];
	
	//Salvo nell'array i bitmap dei fotogrammi
	fotogramma* p = replay;
	for (int i = 0; i < numero_fotogrammi; i++){
		array_replay[i] = (p->bitmap)*;
		p = p->prossimo;
	}

	//Salvo array su file
	bool successo = replay_to_file(array_replay, numero_fotogrammi);
	if (!successo) return false;

	//Dealloco array
	delete[] array_replay;
	
	return true;
}



