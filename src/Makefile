FLAGS=-fast -static -Ob2 -march=pentiumiii -xK
COMPILER=icpc

MSTconcurs: MSTconcurs.cc GrafClass.o mfSetClass.o HeapClass.o ArestaClass.o Hash.o
	$(COMPILER) -o MST MSTconcurs.cc GrafClass.o ArestaClass.o Hash.o mfSetClass.o HeapClass.o $(FLAGS) 

HeapClass.o: HeapClass.h HeapClass.cc ArestaClass.h
	$(COMPILER) -c HeapClass.cc $(FLAGS)

mfSetClass.o: mfSetClass.cc mfSetClass.h
	$(COMPILER) -c mfSetClass.cc $(FLAGS)
	
GrafClass.o: ArestaClass.h Hash.h GrafClass.cc GrafClass.h mfSetClass.h HeapClass.h
	$(COMPILER) -c GrafClass.cc $(FLAGS)
	
Hash.o: Hash.cc Hash.h
	$(COMPILER) -c Hash.cc $(FLAGS)

ArestaClass.o: ArestaClass.cc ArestaClass.h
	$(COMPILER) -c ArestaClass.cc $(FLAGS)

clean:
	rm -f *.o *.il MST

