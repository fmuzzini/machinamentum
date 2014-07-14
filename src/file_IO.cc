/**
@file
Modulo per il salvataggio/caricamento su/da file
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <fstream>
using namespace std;
#include "file_IO.h"
#include "debug.h"

static const char STRINGA_NULL[] = "";

bool salva_su_file(void* cont, int n, const char file[], bool chiusura){
	static ofstream f1;
	if ( !f1.is_open() && file != STRINGA_NULL )
		f1.open(file, ios_base::app);

	if (!f1) return false;
	
	f1.write( (char*) cont, n);
	f1.flush();
	
	if (chiusura == true)
		f1.close();

	return f1.good();
}

int carica_da_file(void* dest, const char file[], int n, bool chiusura){
	static ifstream f1;
	if ( !f1.is_open() && file != STRINGA_NULL )
		f1.open(file);

	if (!f1) return -1;

	if (n == -1)
		; //legge tutto il file
	
	f1.read( (char*) dest, n);
	
	if (chiusura == true || f1.eof() )
		f1.close();

	return f1.gcount();
}

bool chiudi_file(){
	return salva_su_file(NULL, 0, STRINGA_NULL, true);
}

bool caricamento_img(bitmap_renderizzato &dest, const char file[]){
	dest.bitmap = al_load_bitmap(file);
	if (dest.bitmap == NULL)
		return false;

	dest.larghezza = al_get_bitmap_width(dest.bitmap);
	dest.altezza = al_get_bitmap_height(dest.bitmap);

	return true;	
}
