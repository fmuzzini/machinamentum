/**
@mainpage Machinamentum
Semplice gioco per progetto d'esame.

@author Filippo Muzzini
*/

/**
@file 
File contenente la funzione ::main.
Inizializza i vari componenti e poi passa il controllo a stati.cc
Alla fine del programma distrugge i vari componenti.
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <cassert>
#include "struttura_dati.h"
#include "stati.h"
#include "rendering.h"

#include "debug.h"
#ifdef DEBUG_MODE
unsigned char MASK = 1;		//Setto maschera debug
#endif

extern const int FPS = 30;
int ALTEZZA;
int LARGHEZZA;

ALLEGRO_DISPLAY* display;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* coda_eventi;

void chiudi(){
	al_destroy_display(display);
	al_destroy_event_queue(coda_eventi);
	al_destroy_timer(timer);
}

/**
Funzione principale.
Inizializza il core Allegro e i vari addon, collega i vari moduli
*/
int main(int argc, char* argv[])
{	
	ALLEGRO_DISPLAY_MODE disp_data;
	
 
	al_init();		
	D1(cout<<"Allegro inizializzato"<<endl;)
	al_init_image_addon();
	D1(cout<<"Image addon inizializzato"<<endl;)
	al_init_primitives_addon();
	D1(cout<<"Primitives addon inizializzato"<<endl;)
	al_init_font_addon();
	D1(cout<<"Font addon inizializzato"<<endl;)
	al_init_ttf_addon();
	D1(cout<<"Ttf addon inizializzato"<<endl;)
	
	al_install_keyboard();	
	D1(cout<<"Tastiera Inizilizzata"<<endl;)
	
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	LARGHEZZA = disp_data.width;	
	D2(cout<<"LARGHEZZA: "<<LARGHEZZA<<endl;)
	ALTEZZA = disp_data.height;	
	D2(cout<<"ALTEZZA: "<<ALTEZZA<<endl;)
	
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(LARGHEZZA, ALTEZZA);
	assert(display);	
	D1(cout<<"Display creato"<<endl;)
	
	al_hide_mouse_cursor(display);
	D1(cout<<"Cursore Mouse nascosto"<<endl;)

	coda_eventi = al_create_event_queue();
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());
	D2(cout<<"CODA_EVENTI: "<<coda_eventi;)

	timer = al_create_timer(1.0/FPS);
	//al_register_event_source(coda_eventi, al_get_timer_event_source(timer));
	al_start_timer(timer);
	D2(cout<<"Timer Creato"<<endl;)
	D1(cout<<"Inizializzazioni completate"<<endl;)

	caricamento_iniziale();

	atexit(chiudi);

	menu_principale();
	
	
	return 0;
	
}
