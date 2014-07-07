/**
@file
Interfaccia del modulo view
*/

#include <allegro5/allegro.h>

/**
Mostra sul display gli elementi.
Disegna gli elementi nella loro posizione
@param[in] elem Array degli elementi da disegnare
@param[in] n Numero degli elementi
@param[in] display Display sul quale disegnare
*/
void mostra_schermata(elementi elem, int n, ALLEGRO_DISPLAY* const display);
