main:
	g++ vector.cpp funkcijos.cpp -o programa
	./programa

run0:
	g++ -std=c++17 -O3 konteinerius_tyrimas.cpp funkcijos.cpp -o programa
	./programa

run1:
	g++ -std=c++17 -O3 strategija_1.cpp funkcijos.cpp -o programa
	./programa

run2:
	g++ -std=c++17 -O3 strategija_2.cpp funkcijos.cpp -o programa
	./programa

run3:
	g++ -std=c++17  -O3 strategija_3.cpp funkcijos.cpp -o programa
	./programa	

clean:
	rm -f programa