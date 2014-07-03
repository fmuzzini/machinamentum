/**
@file
Modulo per il salvataggio/caricamento su/da file
*/

#include <allegro5/allegro.h>
#include <fstream>

bool replay_to_file(ALLEGRO_BITMAP replay[], int n, char file[]){
	ostream f1(file);
	if (!f1) return false;
	
	int numero_byte = n*sizeof(ALLEGRO_BITMAP);
	f1.write(reinterpret_cast<char*>(replay), numero_byte);
	f1.close();

	return true;
}
