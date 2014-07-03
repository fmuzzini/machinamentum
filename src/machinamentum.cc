/**
@mainpage Machinamentum
Semplice gioco per progetto d'esame.

@author Filippo Muzzini
*/

/**
@file 
File contenente la funzione ::main
*/

#include <allegro5/allegro.h>
#include "struttura_dati.h"
#include "view.h"

/**
Funzione principale.
Inizializza il core Allegro e i vari addon, collega i vari moduli
*/
int main(int argc, char* argv[])
{
	elementi elem;
	int n_elem;
	ALLEGRO_DISPLAY* display;
	 
	
	al_init();

	while(true){
		n_elem = get_schermata(elem);
		mostra_schermata(elem, n_elem, display);
			
	}
	
	
}
