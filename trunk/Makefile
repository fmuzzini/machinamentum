VPATH = src/
OBJ = machinamentum.o view.o accesso_dati.o file_IO.o
CXXFLAGS=-Wall

Machinamentum: depend $(OBJ)
	g++ -o Machinamentum $(OBJ)

-include dependencies

.PHONY: depend clean cleanall

depend:
	g++ -MM $(VPATH)*.cc > dependencies
clean:
	rm *.o
cleanall:
	rm Machinamentum *.o *~

