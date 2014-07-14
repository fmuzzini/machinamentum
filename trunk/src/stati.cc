/**
@file
Modulo che si occupa di far passare il programma da uno stato all'altro.
Può essere visto come controller.
Intercetta gli eventi e in base a quelli modifica lo stato del programma, i dati in memoria (utilizzando accesso_dati.cc)
e passa al modulo view.cc i vari elementi renderizzati dal modulo render.cc
*/
#include <allegro5/allegro.h>
#include <cstring>
#include "struttura_dati.h"
#include "view.h"
#include "rendering.h"

#include "debug.h"

extern ALLEGRO_EVENT_QUEUE* coda_eventi;
extern int LARGHEZZA, ALTEZZA, FPS;
extern bitmap_renderizzato LOGO, SFONDO, TUTORIAL;

ALLEGRO_EVENT ev;
const int MAX_CHAR_MENU = 15;

struct opzione_menu{
	char titolo[MAX_CHAR_MENU + 1];
	void(*fun)();
};

struct nemico_t{
	int tipo;
	int punti;
	int vita;
	int velocita;
	int posX;
	int posY;
	int fineX;
	int fineY;
	ALLEGRO_BITMAP* bitmap;
};

struct proiettile_t{
	int verso;
	int velocita;
	int posX;
	int posY;
	int fineX;
	int fineY;
	ALLEGRO_BITMAP* bitmap;
};

struct personaggio_t{
	int sparati;	
	int posX;
	int posY;
	int fineX;
	int fineY;
	ALLEGRO_BITMAP* bitmap;
};

void tutorial();
void gioca();
void replay();
void esci();

void menu_principale(){
	
	const int ELEM_MENU = 4;
	const int ELEM_GRAFICI = 3 + ELEM_MENU;
	const int ALTEZZA_OPZIONI = ALTEZZA/10;
	int selezionato = 0;
	opzione_menu menu[ELEM_MENU];
	elemento elementi_grafici[ELEM_GRAFICI];

	//Definisco le varie opzioni del menu
	strcpy(menu[0].titolo, "TUTORIAL");
	menu[0].fun = tutorial;

	strcpy(menu[1].titolo, "GIOCA!");
	menu[1].fun = gioca;
	
	strcpy(menu[2].titolo, "CARICA REPLAY");
	menu[2].fun = replay;

	strcpy(menu[3].titolo, "ESCI");
	menu[3].fun = esci;
	
	D1(cout<<"Opzioni create"<<endl;)

	elementi_grafici[0].posX = 0;
	elementi_grafici[0].posY = 0;

	elementi_grafici[1].bitmap = rendering_img(LOGO);
	elementi_grafici[1].posX = LARGHEZZA/4;
	elementi_grafici[1].posY = 10;
	D1(cout<<"Logo"<<endl;)
	
	elementi_grafici[2+ELEM_MENU].bitmap = rendering_selezione(LARGHEZZA/2, ALTEZZA_OPZIONI);
	elementi_grafici[2+ELEM_MENU].posX = LARGHEZZA/4;
	elementi_grafici[2+ELEM_MENU].posY = ALTEZZA/2;

	//Rendering vari elementi menu
	for (int i = 0; i < ELEM_MENU; i++){
		elementi_grafici[i+2].bitmap = rendering_opzione(menu[i].titolo, LARGHEZZA/2, ALTEZZA_OPZIONI);
		elementi_grafici[i+2].posX = LARGHEZZA/4;
		elementi_grafici[i+2].posY = (ALTEZZA/2) + (ALTEZZA_OPZIONI + 10)*i;
	}
	D1(cout<<"Opzioni"<<endl;)
		
	while(true){

		D4(cout<<"Attesa evento Selezionato:"<<selezionato<<endl;)
		if (al_wait_for_event_timed(coda_eventi, &ev, 1.0/FPS) && ev.type == ALLEGRO_EVENT_KEY_DOWN){
			D4(cout<<"KEY: "<<ev.keyboard.keycode<<endl;)
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					selezionato--;
					break;
				case ALLEGRO_KEY_DOWN:
					selezionato++;
					break;
				case ALLEGRO_KEY_RIGHT:
					
					break;
				case ALLEGRO_KEY_LEFT:
					
					break;
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
					menu[selezionato].fun();
					break;
				case ALLEGRO_KEY_ESCAPE:
					return;
					break;
				case ALLEGRO_KEY_R:
					
					break;
				default: break;
			}
		selezionato = (selezionato+ELEM_MENU)%ELEM_MENU;
		}

		elementi_grafici[0].bitmap = rendering_sfondo();
		

		elementi_grafici[2+ELEM_MENU].posY = (ALTEZZA/2) + (ALTEZZA_OPZIONI + 10)*selezionato;
		
		mostra_schermata(elementi_grafici, ELEM_GRAFICI);

	}
}

void tutorial(){
	const int schermate = 5;
	const int ELEM_GRAFICI = 3;
	int schermata_attuale = 0;
	elemento elementi_grafici[ELEM_GRAFICI];
	
	char benvenuto[] =	"Benvenuto soldato.\n"
		   		"Qui imparerai ad essere una vera\n"
				"Macchina da guerra.\n",

	movimento[] =	 	"Grazie alle nostre spaciali tute alari "
				"potrai muoverti agevolmente in tutte le direzioni.\n"
				"Usa i taasti freccia della tastiera per muoverti.\n",

	sparo[] =		"Durante il volo ti troverai davanti diversi nemici "
				"che diventeranno sempre più forti man mano che avanzerai.\n"
				"Ma non temere sei perfettamente in grado di abbatterli tutti.\n"
				"Per sparare premi <SPAZIO>\n",

	replay[] =		"Se ti capita di compiere imprese memorabili puoi "
				"salvarle premendo <R>.\n"
				"potrai poi rivederle nella sezione Carica Replay del menù principale\n",

	fine[] =		"I vari nemici che abbatterai ti faranno accumulare punti.\n"
				"Impeganti per migliorare sempre il tuo punteggio.\n"
				"Ora sei pronto per scendere in battaglia!\n";
	
	char* testi[schermate] = {benvenuto, movimento, sparo, replay, fine};
	
	elementi_grafici[0].posX = 0;
	elementi_grafici[0].posY = 0;

	elementi_grafici[1].bitmap = rendering_img(TUTORIAL);
	elementi_grafici[1].posX = (LARGHEZZA - (LARGHEZZA/3)) / 2;
	elementi_grafici[1].posY = 0;

	elementi_grafici[2].posX = (LARGHEZZA - (LARGHEZZA/2)) / 2;
	elementi_grafici[2].posY = ALTEZZA/2;

	while(schermata_attuale < schermate){
		al_destroy_bitmap(elementi_grafici[2].bitmap);
		elementi_grafici[2].bitmap = rendering_textarea(testi[schermata_attuale], LARGHEZZA/2, ALTEZZA/2 - 10);

		if (al_wait_for_event_timed(coda_eventi, &ev, 1.0/FPS) && ev.type == ALLEGRO_EVENT_KEY_DOWN)
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				return;
			else
				schermata_attuale++;

		elementi_grafici[0].bitmap = rendering_sfondo();
		
		mostra_schermata(elementi_grafici, ELEM_GRAFICI);
	}
	
	
	  
}

ALLEGRO_BITMAP* proiettile_p;
ALLEGRO_BITMAP* proiettile_n;
ALLEGRO_BITMAP* nemico;
ALLEGRO_BITMAP* personaggio;
const float LARGHEZZA_PROIETTILE = LARGHEZZA/30.0;
const float ALTEZZA_PROIETTILE = ALTEZZA/30.0;
const char FILE_PROIETTILE[] = "img/proiettile.png";

inline void inizializza_proiettili(){
	proiettile_p = rendering_img(FILE_PROIETTILE, LARGHEZZA_PROIETTILE, ALTEZZA_PROIETTILE, 0);
	proiettile_n = rendering_img(FILE_PROIETTILE, LARGHEZZA_PROIETTILE, ALTEZZA_PROIETTILE, ALLEGRO_FLIP_HORIZONTAL);
}

inline void inizializza_proiettili(proiettile_t proiettili[], int n){
	for (; n > 0; n--)
		proiettili[n].verso = 0;
}

void inizializza_nemici(nemico_t nemici[], int n){
	
}

void inizializza_personaggio(personaggio_t &personaggio){

}

bool spara(personaggio_t &personaggio, proiettile_t proiettili[], int max_proiettili){
	if (personaggio.sparati >= max_proiettili)
		return false;
	personaggio.sparati++;
	
	int i = 0;
	for (; proiettili[i].verso != 0 && i < max_proiettili; i++)
		;
	proiettili[i].verso = 1;
	proiettili[i].posX = personaggio.fineX;
	proiettili[i].posY = personaggio.fineY;

	return true;
}

inline void aggiorna_proiettili(proiettile_t proiettili[], int n){
	for (int i = 0; i < n; i++)
		proiettili[i].posX += verso * proiettili[i].velocita;
}

void nuovo_nemico(nemico_t nemici[], int n, int score){
	for (int i = 0; i < n && nemici[i].vita != -1; i++)
		;
	if (i == n)
		return;
	
	int modulo = score/((FINE_GIOCO-100)/TIPI_NEMICI);
	int caso = rand()%modulo;
	switch (caso) {
		case 0:
			
	}
		
}

inline void collisione(int posX_1, int fineX_1, int posY_1, int fineY_1, int posX_2, int fineX_2, int posY_2, int fineY_2){
	if (	fineX_1 < posX_2 ||	//_1 alla sinistra
		posX_1 > fineX_2 ||	//_1 alla destra
		fineY_1 < posY_2 ||	//_1 sopra
		posY_1 > fineY_2 ) 	//_1 sotto
				
		return false;
	else
		return true;
}
void aggiorna_nemici(nemico_t nemici[], int n, proiettile_t proiettili[], int m, int &score){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (collisione(	nemici[i].posX, nemici[i].fineX, nemici[i].posY, nemici[i].fineY,
					proiettili[j].posX, proiettili[j].fineX. proiettili[j].posY, proiettili[j].fineY)){
				
				nemici[i].vita--;
				proiettile[j].verso = 0;
				score += nemici[i].punti;
			}
	
	for (int i = 0; i < n; i++){
		if (nemici[i].vita <= 0){
			if(nemici[i].posY < ALTEZZA){
				nemici[i].vita = -1;
				continue;
			} else {
				nemici[i].posY -= GRAVITA;
				continue;
			}
		}

		int caso = rand();
		switch((caso+nemici[i].tipo+nemici[i].vita+nemici[i].posX+nemici[i].posY)%4){
			case 0:
				nemici[i].posX += nemici[i].velocita;
			case 1:
				nemici[i].posX -= nemici[i].velocita;
			case 2:
				nemici[i].posY += nemici[i].velocita;
			case 3:
				nemici[i].posY -= nemici[i].velocita;
		}
	}
}



bool personaggio_morto(personaggio_t personaggio, proiettile_t proiettili[], int n){
	for (int i = 0; i < n; i++){
		if (collisione(	personaggio.posX, personaggio.fineX, personaggio.posY, personaggio.fineY,
				proiettili[i].posX, proiettili[i].fineX, proiettili[i].posY, proiettili[i].fineY) )
				
					return true;
	}
	
	return false;
}

void game_over(int score){

}

void machinamentum(){

}

void nome_replay(){

}

void menu_esci(){

}
						extern unsigned char MASK;
void gioca(){					MASK = 1;
	const int FINE_GIOCO = 900;
	const int VELOCITA_PERSONAGGIO = 1;
	const int RANGE_MOVIMENTO = LARGHEZZA/3;
	const int MAX_NEMICI = 7;
	const int CARICATORE = 10;
	const int CARICATORE_NEMICO = 3;
	const int PROIETTILI_NEMICI = MAX_NEMICI*CARICATORE_NEMICO;
	const int LARGHEZZA_SCORE = LARGHEZZA/4;
	const int ALTEZZA_SCORE = ALTEZZA/10;
	const char SURRISCALDATA[] = "ARMA SURRISCALDATA!";
	const int LARGHEZZA_SURR = LARGHEZZA/3;
	const int ALTEZZA_SURR = ALTEZZA/5;
	nemico_t nemici[MAX_NEMICI];
	proiettile_t proiettili_nemici[PROIETTILI_NEMICI];
	proiettile_t proiettili_personaggio[CARICATORE];
	elemento elementi_grafici[MAX_NEMICI*CARICATORE_NEMICO + CARICATORE + MAX_NEMICI + 4];
	personaggio_t personaggio;
	int elementi_g = 3;
	bool surriscaldata = false, key_up = false, key_down = false, key_left = false, key_right = false;
	int score = 0;

	inizializza_proiettili();
	inizializza_proiettili(proiettili_nemici, PROIETTILI_NEMICI);
	inizializza_proiettili(proiettili_personaggio, CARICATORE);
	inizializza_nemici(nemici, MAX_NEMICI);
	inizializza_personaggio(personaggio);
	

	elementi_grafici[0].posX = 0;
	elementi_grafici[0].posY = 0;
	
	elementi_grafici[1].posX = (LARGHEZZA - LARGHEZZA_SCORE) / 2;
	elementi_grafici[1].posY = 10;

	while (true) {
		if (al_wait_for_event_timed(coda_eventi, &ev, 1.0/FPS) && ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					key_up = true;
					break;
				case ALLEGRO_KEY_DOWN:
					key_down = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					key_right = true;
					break;
				case ALLEGRO_KEY_LEFT:
					key_left = true;
					break;
				case ALLEGRO_KEY_SPACE:
					surriscaldata = !spara(personaggio, proiettili_personaggio, CARICATORE);
					break;
				case ALLEGRO_KEY_R:
					nome_replay();
					break;
				case ALLEGRO_KEY_ESCAPE:
					menu_esci();
				default: break;
			}
		}
		
		if (ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					key_up = false;
					break;
				case ALLEGRO_KEY_DOWN:
					key_down = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					key_right = false;
					break;
				case ALLEGRO_KEY_LEFT:
					key_left = false;
					break;
				default: break;
			}
		}
		
		if (key_up && personaggio.posX > 0)
			personaggio.posX -= VELOCITA_PERSONAGGIO;
		if (key_down && personaggio.posX < ALTEZZA)
			personaggio.posX += VELOCITA_PERSONAGGIO;
		if (key_left && personaggio.posY > 0)
			personaggio.posY -= VELOCITA_PERSONAGGIO;
		if (key_right && personaggio.posY < RANGE_MOVIMENTO)
			personaggio.posY += VELOCITA_PERSONAGGIO;

		aggiorna_nemici(nemici, MAX_NEMICI, proiettili_personaggio, CARICATORE, score);
		aggiorna_proiettili(proiettili_nemici, PROIETTILI_NEMICI);
		aggiorna_proiettili(proiettili_personaggio, CARICATORE);

		if (score >= FINE_GIOCO){
			machinamentum();
			return;
		}

		if (personaggio_morto(personaggio, proiettili_nemici, PROIETTILI_NEMICI)){
			game_over(score);
			return;
		}
		
		nuovo_nemico(nemici, MAX_NEMICI, score);
		
		elementi_grafici[0].bitmap = rendering_sfondo();
		
		al_destroy_bitmap(elementi_grafici[2].bitmap);
		elementi_grafici[1].bitmap = rendering_textarea(score, LARGHEZZA_SCORE, ALTEZZA_SCORE);
		
		elementi_grafici[2].bitmap = personaggio.bitmap;
		elementi_grafici[2].posX = personaggio.posX;
		elementi_grafici[2].posY = personaggio.posY;
		
		elementi_g = 3;

		for (int i = 0; i < MAX_NEMICI; i++){
			if (nemici[i].tipo > 0){
				elementi_grafici[elementi_g].bitmap = nemici[i].bitmap;
				elementi_grafici[elementi_g].posX = nemici[i].posX;
				elementi_grafici[elementi_g].posY = nemici[i].posY;
				elementi_g++;
			}
				
		}
		
		for (int i = 0; i < PROIETTILI_NEMICI; i++){
			if (proiettili_nemici[i].verso != 0){
				elementi_grafici[elementi_g].bitmap = proiettili_nemici[i].bitmap;
				elementi_grafici[elementi_g].posX = proiettili_nemici[i].posX;
				elementi_grafici[elementi_g].posY = proiettili_nemici[i].posY;
				elementi_g++;
			}
		}

		for (int i = 0; i < CARICATORE; i++){
			if (proiettili_personaggio[i].verso != 0){
				elementi_grafici[elementi_g].bitmap = proiettili_personaggio[i].bitmap;
				elementi_grafici[elementi_g].posX = proiettili_personaggio[i].posX;
				elementi_grafici[elementi_g].posY = proiettili_personaggio[i].posY;
				elementi_g++;
			}
		}

		if (surriscaldata){
			elementi_grafici[elementi_g].bitmap = rendering_textarea(SURRISCALDATA, LARGHEZZA_SURR, ALTEZZA_SURR);
			elementi_grafici[elementi_g].posX = (LARGHEZZA - LARGHEZZA_SURR) / 2;
			elementi_grafici[elementi_g].posY = (ALTEZZA - ALTEZZA_SURR) / 2;
			elementi_g++;
		}

		mostra_schermata(elementi_grafici, elementi_g);
	}
}

void replay(){
	ALLEGRO_EVENT ev;
	
}

void esci(){
	exit(0);
};
