/**
@file
File contente le istruzioni per il debug.
Viene incluso solo se è definito DEBUG_MODE
*/

#ifndef DEBUG
#define DEBUG

#ifdef DEBUG_MODE
	extern unsigned char MASK;	/**< Maschera Debug. */
	#define DBG(A, B) {if ((A) & MASK) {B; } }
	#include <iostream>
	using namespace std;
#else
	#define DBG(A, B)
#endif

#define D1(A) DBG(1, A) //Mostra i vari passaggi fondamentali
#define D2(A) DBG(2, A) //Mostra stato variabili ed errori veri e propri
#define D4(A) DBG(4, A) //Mostra stato di variabili utili per capire evoluzione di cicli ed eventi

#endif
