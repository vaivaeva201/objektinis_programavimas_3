#include "studentas.h"
#include "vector.h"

void testas(unsigned int sz, double &laikas_std, double &laikas_class, int &v1_r, int &v2_r)
{
    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<int> v1;
    size_t cap1 = 0; v1_r = 0;
    for (int i = 1; i <= sz; ++i) {
        if (v1.capacity() != cap1) {
            cap1 = v1.capacity();
            v1_r++;
        }
        v1.push_back(i);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    laikas_std += std::chrono::duration<double>(end1 - start1).count();

    auto start2 = std::chrono::high_resolution_clock::now();
    Vector<int> v2;
    size_t cap2 = 0; v2_r = 0;
    for (int i = 1; i <= sz; ++i) {
        if (v2.capacity() != cap2) {
            cap2 = v2.capacity();
            v2_r++;
        }
        v2.push_back(i);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    laikas_class += std::chrono::duration<double>(end2 - start2).count();
}

int main()
{
    unsigned int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};

    for (unsigned int sz : sizes) 
    {
        double laikas_std = 0, laikas_class = 0;
        int r1 = 0, r2 = 0;

        cout << "\nTestuojamas dydis: " << sz  << endl;
        for (int i = 0; i < 3; i++)
        {
            testas(sz, laikas_std, laikas_class, r1, r2);
        }

        cout << left << setw(20) << "Konteineris" << setw(20) << "Vid. Laikas (s)" << "Perskirstymai" << endl;
        cout << left << setw(20) << "std::vector" << setw(20) << laikas_std / 3.0 << r1 - 1 << endl;
        cout << left << setw(20) << "Mano Vector" << setw(20) << laikas_class / 3.0 << r2 - 1 << endl;
    }

    return 0;
}