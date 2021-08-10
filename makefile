output: Word_Wizard.o 
	g++ Word_Wizard.o -o output

Word_Wizard.o: Word_Wizard.cpp Vector.h map.h Heap.h 
	g++ -c Word_Wizard.cpp
clean:
	rm *.o output