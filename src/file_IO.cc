/**
@file
Modulo per il salvataggio/caricamento su/da file
*/

#include <allegro5/allegro.h>
#include <fstream>
using namespace std;

/*
Riguardare per apertura, accodamento e chiusura file
*/
bool salva_su_file(void* cont, int n, const char file[]){
	ofstream f1(file, ios_base::app);
	if (!f1) return false;
	
	f1.write( (char*) cont, n);
	f1.close();

	return true;
}
