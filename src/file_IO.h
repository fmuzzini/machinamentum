/**
@file
Interfaccia del modulo file_IO
*/

#include <allegro5/allegro.h>

/**
Salva su file una sequenza di n byte.
@param[in] cont Puntatore all'inizio della sequenza
@param[in] n numero di byte da scrivere
@param[in] file nome da dare al file
*/
bool salva_su_file(const void* cont, int n, const char file[]);
