#include "studentas.h"
#include "konteineriai.h"

int main(){

    vector < Studentas > studentai_v;
    list < Studentas > studentai_l;
    deque < Studentas > studentai_d;

    int n = 10000;
    string failas = "Studentai_" + std::to_string(n) + ".txt";

    tyrimas(failas, studentai_v, "vekor");
    tyrimas(failas, studentai_l, "list");
    tyrimas(failas, studentai_d, "deque");
    


    return 0;
}