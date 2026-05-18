#include "studentas.h"
#include "konteineriai.h"
#include "vector.h"

void strategija_3(){

    Vector < Studentas > studentai_v;
    list < Studentas > studentai_l;
    deque < Studentas > studentai_d;

    cout << "Trečios strategijos testavimas " << endl;
    cout << "-----------------------------------------------------------" << endl;

    string failas = pasirinkimas();
    double vektoriaus_laik;
    double list_laik;
    double deque_laik;

    cout << endl;
    cout << "Rezultatai: " << endl;
    cout << "-----------------------------------------------------------" << endl;
    strategijos_trys_tyrimas(failas, studentai_v, "vekor");
   // strategijos_trys_tyrimas(failas, studentai_l, "list");
   // strategijos_trys_tyrimas(failas, studentai_d, "deque");

  //  return 0;
}