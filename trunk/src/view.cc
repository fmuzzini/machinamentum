/**
@file
Modulo che si occupa di assemblare e mostrare a video i vari elementi
*/

#include <allegro5/allegro.h>
#include "struttura_dati.h"
#include "accesso_dati.h"
#include "view.h"


void mostra_schermata(elementi elem, int n, ALLEGRO_DISPLAY* const display){
	al_set_target_backbuffer(display); 		//Setto il backbuffer
	al_clear_to_color(al_map_rgb(255,255,255)); 	//Pulisco il backbuffer
	
	for (int i = 0; i < n; i++){
		elemento el = elem[i];
		al_draw_bitmap(el.bitmap, el.posX, el.posY, 0); 	
	}
	
	buffer_replay( al_get_backbuffer(display) );	//Salvo nel replay il backbuffer appena creato
	
	al_flip_display();				//Mostro il backbuffer
}
