output: main.o myvector.o contact.o contactbst.o
	g++ main.o myvector.o contact.o contactbst.o -o output
main.o: main.cpp myvector.h contact.h contactbst.h
	g++ -c main.cpp
myvector.o: myvector.h myvector.cpp
	g++ -c myvector.cpp
contact.o: contact.h contact.cpp
	g++ -c contact.cpp
contactbst.o: contactbst.h contactbst.cpp 
	g++ -c contactbst.cpp

clean:
	rm *.o output