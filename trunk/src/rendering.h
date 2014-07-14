#ifndef RENDERING
#define RENDERING

#include "struttura_dati.h"

bool caricamento_iniziale();

ALLEGRO_BITMAP* rendering_img(bitmap_renderizzato img);

ALLEGRO_BITMAP* rendering_img(const char file[], float larghezza, float altezza, int flags);

ALLEGRO_BITMAP* rendering_sfondo();

ALLEGRO_BITMAP* rendering_opzione(const char titolo[], int larghezza, int altezza);

ALLEGRO_BITMAP* rendering_selezione(int larghezza, int altezza);

ALLEGRO_BITMAP* rendering_textarea(const char testo[], int larghezza, int altezza);

ALLEGRO_BITMAP* rendering_textarea(int testo, int larghezza, int altezza);

#endif
