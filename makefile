CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: plotSpectrogram query


hashable.o: hashable.cpp hashable.h 
	$(CC) $(CFLAGS) -c hashable.cpp 

linkedmap.o: linkedmap.h linkedmap.cpp hashable.o map.h
	$(CC) $(CFLAGS) -c linkedmap.cpp 

hashmap.o: hashmap.h hashmap.cpp hashable.o map.h
	$(CC) $(CFLAGS) -c hashmap.cpp


simplecanvas.o: simplecanvas/simplecanvas.h simplecanvas/simplecanvas.cpp
	$(CC) $(CFLAGS) -c simplecanvas/simplecanvas.cpp

dsp.o: dsp.cpp dsp.h
	$(CC) $(CFLAGS) -c dsp.cpp

dspviz.o: dsp.o dspviz.cpp dspviz.h simplecanvas.o
	$(CC) $(CFLAGS) -c dspviz.cpp

plotSpectrogram: dsp.o dspviz.o simplecanvas.o AudioFile.h plotSpectrogram.cpp
	$(CC) $(CFLAGS) -o plotSpectrogram dsp.o dspviz.o simplecanvas.o plotSpectrogram.cpp

query: hashable.o linkedmap.o hashmap.o dsp.o dspviz.o simplecanvas.o AudioFile.h query.cpp
	$(CC) $(CFLAGS) -o query hashable.o linkedmap.o hashmap.o dsp.o dspviz.o simplecanvas.o query.cpp

clean:
	rm *.o *.exe *.stackdump plotSpectrogram