/**
@file
Modulo che si occupa di assemblare e mostrare a video i vari elementi
*/

#include <allegro5/allegro.h>
#include "struttura_dati.h"
#include "accesso_dati.h"
#include "view.h"

#include "debug.h"

extern ALLEGRO_DISPLAY* display;			extern unsigned char MASK;

void mostra_schermata(elementi elem, int n){		MASK = 0;
	D2(cout<<"Numero elementi: "<<n<<endl;)
	al_set_target_backbuffer(display); 		//Setto il backbuffer
	al_clear_to_color(al_map_rgb(255,255,255)); 	//Pulisco il backbuffer
	D1(cout<<"Backbuffer ripulito"<<endl;)

	for (int i = 0; i < n; i++){
		elemento el = elem[i];
		al_draw_bitmap(el.bitmap, el.posX, el.posY, 0);
		D1(cout<<"Elemento Disegnato"<<endl;)
		
		//al_destroy_bitmap(el.bitmap); 		//Distuggo il bitmap appena copiato
		D1(cout<<"Bitmap distrutto"<<endl;)
	}
	D1(cout<<"Backbuffer disegnato"<<endl;)
	
	buffer_replay( al_get_backbuffer(display) );	//Salvo nel replay il backbuffer appena creato
	D1(cout<<"Fotogramma salvato nel buffer"<<endl;)

	al_flip_display();				//Mostro il backbuffer
	D1(cout<<"Mostrato a video"<<endl;)

}
