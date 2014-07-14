#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <cstdio>
#include <cstring>
#include "struttura_dati.h"
#include "file_IO.h"
#include "rendering.h"

#include "debug.h"

extern int LARGHEZZA, ALTEZZA;

const char FILE_FONT[] = "font/gunplay.ttf";
const char FILE_LOGO[] = "img/logo.png";
const char FILE_SFONDO[] = "img/sfondo.png";
const char FILE_TUTORIAL[] = "img/tutorial.png";

const float SPESSORE_SELEZIONE = 10;
ALLEGRO_FONT* FONT_OPZIONI;
ALLEGRO_FONT* FONT_TEXT;
ALLEGRO_COLOR COLORE_SELEZIONE, COLORE_SFONDO_OPZIONI, COLORE_TESTO_OPZIONI;

bitmap_renderizzato LOGO, SFONDO, TUTORIAL;


/**
Scala l'immagine alla larghezza ed altezza desiderate.
Se altezza = 0 o omesso mantiene le proporzioni.
@param[in-out] img Bitmap da scalare
@param[in] larghezza Larghezza desiderata
@param[in] altezza Altezza desiderata
*/
static void scala_img(bitmap_renderizzato &img, float larghezza, float altezza = 0, int flags = 0){
	if(altezza == 0)
		altezza = larghezza * (((double)img.altezza) / img.larghezza);

	ALLEGRO_BITMAP* tmp = al_create_bitmap(LARGHEZZA, ALTEZZA);
	al_set_target_bitmap(tmp);
	al_draw_scaled_bitmap(img.bitmap, 0, 0, img.larghezza, img.altezza, 0, 0, larghezza, altezza, flags);
	img.larghezza = larghezza;
	img.altezza = altezza;

	al_destroy_bitmap(img.bitmap);
	img.bitmap = tmp;
}

static void scrivi_text(ALLEGRO_FONT* font, ALLEGRO_COLOR colore, int larghezza, int altezza, int flag, const char testo[]){
MASK = 1|2;
	int posX = (flag == ALLEGRO_ALIGN_CENTER) ? larghezza/2 : 0;
	int posY = 10;

	int char_width = al_get_text_width(font, "m\0");
	D2(cout<<"char_width: "<<char_width<<endl);
	int line_width = larghezza / char_width;
	D2(cout<<"line: "<<line_width<<endl;)	
	
	int i = 0;
	int inizio = 0;
	int stacco = 0;
	char s_tmp[line_width+1];
	
	D4(cout<<"Inizio ciclo"<<endl;)
	while (testo[inizio] != '\0'){
	stacco = line_width;
	for (i = 0; i < line_width && testo[inizio+i-1] != '\0'; i++){
		if (testo[inizio+i] == ' ' || testo[inizio+i] == '\n' || testo[inizio+i] == '\0')
			stacco = inizio+i;
		if (testo[inizio+i] == '\n')
			break;
		}
	D2(cout<<"inizio: "<<inizio<<" stacco: "<<stacco<<endl;)
	strncpy(s_tmp, &testo[inizio], stacco-inizio);
	s_tmp[stacco-inizio] = '\0';
	D1(cout<<"stringa creata"<<endl;)
	al_draw_text(font, colore, posX, posY, flag, s_tmp);
	D1(cout<<"stringa scritta"<<endl;)
	inizio = stacco+1;
	stacco = 0;
	posY += al_get_font_line_height(font);
	}
}

bool caricamento_iniziale(){	
	caricamento_img(LOGO, FILE_LOGO);
	scala_img(LOGO, LARGHEZZA/2);
	D1(cout<<"Logo caricato"<<endl;)

	caricamento_img(SFONDO, FILE_SFONDO);
	scala_img(SFONDO, LARGHEZZA, ALTEZZA);
	D1(cout<<"Sfondo caricato"<<endl;)

	caricamento_img(TUTORIAL, FILE_TUTORIAL);
	scala_img(TUTORIAL, LARGHEZZA/3);
	D1(cout<<"tutorial caricato"<<endl;)
	
	COLORE_SELEZIONE = al_map_rgb(0, 0, 255);
	COLORE_SFONDO_OPZIONI = al_map_rgb(50, 50, 50);
	COLORE_TESTO_OPZIONI = al_map_rgb(200, 200, 200);

	FONT_OPZIONI = al_load_ttf_font(FILE_FONT, (ALTEZZA/14 - 10), 0);
	FONT_TEXT = al_load_ttf_font(FILE_FONT, (ALTEZZA/20 - 10), 0);
	D1(cout<<"Font caricato"<<endl;)
	
	return true;
}

ALLEGRO_BITMAP* rendering_img(bitmap_renderizzato img){
	return al_clone_bitmap(img.bitmap);	
}

ALLEGRO_BITMAP* rendering_img(const char file[], float larghezza, float altezza, int flags){
		bitmap_renderizzato img;
		caricamento_img(img, file);
		scala_img(img, larghezza, altezza, flags);
		return img.bitmap;
}

ALLEGRO_BITMAP* rendering_sfondo(){
	D1(cout<<"Rendering Sfondo"<<endl;)
	static ALLEGRO_BITMAP* sfondo = al_create_bitmap(LARGHEZZA, ALTEZZA);
	static int scorrimento = 0;
	(++scorrimento) %= LARGHEZZA;
	al_set_target_bitmap(sfondo);
	al_draw_bitmap(SFONDO.bitmap, (scorrimento * -1), 0, 0);
	al_draw_bitmap(SFONDO.bitmap, (LARGHEZZA - scorrimento), 0, 0);
	return sfondo; 
}

ALLEGRO_BITMAP* rendering_opzione(const char titolo[], int larghezza, int altezza){
	ALLEGRO_BITMAP* opzione = al_create_bitmap(larghezza, altezza);
	al_set_target_bitmap(opzione);
	al_draw_filled_rectangle(0, 0, larghezza, altezza, COLORE_SFONDO_OPZIONI);
	al_draw_text(FONT_OPZIONI, COLORE_TESTO_OPZIONI, (larghezza / 2), 10, ALLEGRO_ALIGN_CENTER, titolo);		

	return opzione; 
}

ALLEGRO_BITMAP* rendering_selezione(int larghezza, int altezza){
	ALLEGRO_BITMAP* selezione = al_create_bitmap(larghezza, altezza);
	al_set_target_bitmap(selezione);
	al_draw_rectangle(0, 0, larghezza, altezza, COLORE_SELEZIONE, SPESSORE_SELEZIONE);
	return selezione;
}

ALLEGRO_BITMAP* rendering_textarea(const char testo[], int larghezza, int altezza){
	ALLEGRO_BITMAP* textarea = al_create_bitmap(larghezza, altezza);
	al_set_target_bitmap(textarea);
	al_clear_to_color(COLORE_SFONDO_OPZIONI);
	scrivi_text(FONT_TEXT, COLORE_TESTO_OPZIONI, larghezza, altezza, ALLEGRO_ALIGN_CENTER, testo);
	return textarea;
}

ALLEGRO_BITMAP* rendering_textarea(int testo, int larghezza, int altezza){ MASK = 1;
	char buffer[10];	
	sprintf(buffer, "%03d", testo);
	D1(cout<<buffer<<endl;)
	return rendering_textarea(buffer, larghezza, altezza);
}

	
