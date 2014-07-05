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

/**
Struttura utilizzata per il salvataggio su file del replay.
Contiene le caratteristiche dei bitmap del replay,
questa struttura è utilizzata solo da questo modulo.
*/
struct replay_header_file{
	int n_fotogrammi;			/**< Numero di fotogrammi del replay. */
	int larghezza;				/**< Larghezza dei bitmap dei fotogrammi. */
	int altezza;				/**< Altezza dei bitmap dei fotogrammi. */
	int pixel_size;				/**< Lunghezza di ogni pixel in byte. */
	int pixel_format;			/**< Tipo di pixel. */
};


static fotogramma* replay = NULL; 		/**< Puntatore alla testa della lista dei fotogrammi. */
static fotogramma* ultimo = NULL;		/**< Puntatore all'ultimo fotogramma. */
static int numero_fotogrammi = 0;		/**< Contatore numero fotogrammi inseriti. */
static const int secondi = 5; 			/**< Durata replay. */
static const int max_fotogrammi = secondi*FPS; 	/**< Massimo numero fotogrammi. */	


void buffer_replay(ALLEGRO_BITMAP* const bitmap){
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

/**
Crea dati grezzi dal bitmap.
Salva in out il bitmap grezzo pixel per pixel, la memoria deve essere già stata allocata all'indirizzo di out in quantità sufficiente.
@param[in] bitmap Bitmap sorgente
@param[out] out Indirizzo dove verranno salvati i dati grezzi
@param[in] n_pixel numero di pixel da copiare 
*/
static void crea_bitmap_grezzo(ALLEGRO_BITMAP* const bitmap, void* out, int n_pixel){
	int format = al_get_bitmap_format(bitmap);
	ALLEGRO_LOCKED_REGION* loked = al_lock_bitmap(bitmap, format, ALLEGRO_LOCK_READONLY);
	
	memcpy(out, bitmap, n_pixel);
}


bool salva_replay(const char file[]){
	fotogramma* p = replay;
	
	//Salvo le informazioni per l'header del file
	replay_header_file header;
	header.n_fotogrammi = numero_fotogrammi;
	header.larghezza = al_get_bitmap_width(p->bitmap);
	header.altezza = al_get_bitmap_height(p->bitmap);
	header.pixel_format = al_get_bitmap_format(p->bitmap);
	header.pixel_size = al_get_pixel_size(header.pixel_format);
	
	//Salvo header all'inizio del file
	salva_su_file(&header, sizeof(header), file);

	int bitmap_size = header.larghezza * header.altezza * header.pixel_size;
	
	//Alloco memoria per un bitmap, per ogni fotogramma ne creo i dati grezzi e li accodo al file
	void* grezzo = malloc(bitmap_size);
	while (p != NULL){
		crea_bitmap_grezzo(p->bitmap, grezzo, bitmap_size);
		salva_su_file(grezzo, bitmap_size, file);
		p = p->prossimo;
	}
}



