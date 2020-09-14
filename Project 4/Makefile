CFLAGS =-W -Wall 
OBJECTS= wordperline.o stringADT.o arraylist.o iterator.o

wordperline: $(OBJECTS)
	gcc -o wordperline $(OBJECTS)

wordperline.o: wordperline.c stringADT.h iterator.h
stringADT.o: arraylist.h stringADT.c stringADT.h
arraylist.o: iterator.h arraylist.c arraylist.h
iterator.o: iterator.c iterator.h

clean:
	rm -f wordperline $(OBJECTS)
