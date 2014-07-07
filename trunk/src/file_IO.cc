/**
@file
Modulo per il salvataggio/caricamento su/da file
*/

#include <fstream>
using namespace std;

static const char STRINGA_NULL[] = "";

bool salva_su_file(void* cont, int n, const char file[], bool chiusura = false){
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

bool chiudi_file(){
	return salva_su_file(NULL, 0, STRINGA_NULL, false);
}
