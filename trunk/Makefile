VPATH = src/
OBJ = machinamentum.o view.o accesso_dati.o file_IO.o stati.o rendering.o
LIBRERIE = allegro-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_font-5.0 allegro_ttf-5.0
LIBS = `pkg-config --libs $(LIBRERIE)`
FLAGS = `pkg-config --cflags $(LIBRERIE)`
CXXFLAGS = -Wall $(FLAGS)


Machinamentum: depend $(OBJ)
	g++ -o Machinamentum $(OBJ) $(LIBS)

-include dependencies

.PHONY: depend clean cleanall debug

depend:
	g++ -MM $(VPATH)*.cc > dependencies

debug: CXXFLAGS := -g -D DEBUG_MODE
debug: clean Machinamentum

clean:
	rm *.o -f
cleanall:
	rm Machinamentum *.o -f
