main: main.o AbstractHex.o HexVector.o HexArray1D.o
	g++ main.o AbstractHex.o HexVector.o HexArray1D.o -o main
	./main
	
main.o: main.cpp
	g++ -std=gnu++11 -c main.cpp
	
AbstractHex.o: AbstractHex.cpp
	g++ -std=gnu++11 -c AbstractHex.cpp
	
HexVector.o: HexVector.cpp
	g++ -std=gnu++11 -c HexVector.cpp
	
HexArray1D.o: HexArray1D.cpp
	g++ -std=gnu++11 -c HexArray1D.cpp
	
clean:
	rm *.o main
