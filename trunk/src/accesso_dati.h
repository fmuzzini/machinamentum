/**
@file
Interfaccia del modulo accesso_dati
*/

#include <allegro5/allegro.h>

/**
Salva in memoria il bitmap.
I vari fotogrammi vengono accodati sotto forma di lista in modo da creare un replay
@param[in] fotogramma Bitmap da accodare al replay
*/
void buffer_replay(const ALLEGRO_BITMAP* fotogramma);

/**
Salva su un file il replay.
Estrae dai fotogrammmi i bitmap grezzi che poi verranno salvati su file attraverso il modulo file_IO.cc
*/
bool salva_replay(const char file[]);
