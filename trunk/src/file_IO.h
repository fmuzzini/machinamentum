/**
@file
Interfaccia del modulo file_IO
*/

#ifndef FILE_IO
#define FILE_IO

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "struttura_dati.h"

/**
Salva su file una sequenza di n byte.
@param[in] cont Puntatore all'inizio della sequenza
@param[in] n Numero di byte da scrivere
@param[in] file Nome da dare al file
@param[in] chiusura Indica se chiudere il file alla fine della scrittura
*/
bool salva_su_file(void* cont, int n, const char file[], bool chiusura = false);

/**
Carica in memoria gli n byte del file
@param[out] dest Puntatore alla zona di memoria in cui salvare
*/
int carica_da_file(void* dest, const char file[], int n, bool chiusura);

/**
Chiude il file associato all'ultimo stream utilizzato.
*/
bool chiudi_file();

/**
Carica immagine dal file e ne crea un bitmap_renderizzato.
@param[out] dest Destinazione del bitmap
@param[in] file File da caricare
*/
bool caricamento_img(bitmap_renderizzato &dest, const char file[]);


#endif
