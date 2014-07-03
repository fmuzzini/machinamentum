/**
@file
Interfaccia del modulo accesso_dati
*/

#include <allegro5/allegro.h>
#include "struttura_dati.h"

/**
Salva in memoria il bitmap.
I vari fotogrammi vengono accodati sotto forma di lista in modo da creare un replay
@param[in] fotogramma Bitmap da accodare al replay
*/
void buffer_replay(ALLEGRO_BITMAP* fotogramma)

/**
Salva su un file il replay.
Crea un array di bitmap che poi verrà salvata su file attraverso il modulo file_IO.cc
*/
bool salva_replay()
