/**
@file
Interfaccia del modulo file_IO
*/


/**
Salva su file una sequenza di n byte.
@param[in] cont Puntatore all'inizio della sequenza
@param[in] n Numero di byte da scrivere
@param[in] file Nome da dare al file
@param[in] chiusura Indica se chiudere il file alla fine della scrittura
*/
bool salva_su_file(const void* cont, int n, const char file[], bool chiusrua = false);

/**
Chiude il file associato all'ultimo stream utilizzato.
*/
bool chiudi_file();
