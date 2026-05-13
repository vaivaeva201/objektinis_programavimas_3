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

vector:
	g++ -std=c++17 vector_Unit_testai.cpp funkcijos.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lCatch2Main -lCatch2 -o unit_test	
	./unit_test


clean:
	rm -f programa