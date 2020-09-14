CFLAGS=-W -Wall -g
OBJECTS=wordperline.o stringADT.o arraylist.o iterator.o jsheap.o jsstring.o

wordperline: $(OBJECTS)
	gcc -o wordperline $^

wordperline.o: wordperline.c stringADT.h arraylist.h accumulator.h
stringADT.o: stringADT.c stringADT.h arraylist.h jsheap.h jsstring.h
arraylist.o: arraylist.c arraylist.h iterator.h jsheap.h
iterator.o: iterator.c iterator.h jsheap.h
jsheap.o: jsheap.c jsheap.h accumulator.h
jsstring.o: jsstring.c jsstring.h accumulator.h
clean:
	rm -f wordperline $(OBJECTS)
