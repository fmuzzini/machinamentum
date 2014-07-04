/**
@file
Interfaccia del modulo file_IO
*/

#include <allegro5/allegro.h>

/**
Salva su file l'array di bitmap.
@param[in] replay Array di bitmap
@parma[in] n numero di elementi
*/
bool replay_to_file(ALLEGRO_BITMAP replay[], int n);
