#ifndef KONTEINERIAI_H
#define KONTEINERIAI_H
#include "studentas.h"
#include <list>
#include <type_traits>
#include <algorithm>

using std:: deque;
using std:: list;

template < typename Container >
void skaityti_failus (string pav, Container& grupe)
{
    string v, p;

    std::ifstream fd(pav);
    if (!fd) 
    {
        std::cerr << "Klaida: nepavyko atidaryti failo!" << endl;
        return;
    }

    string eil;
    getline(fd, eil);

    while(getline(fd, eil)) 
    {
        if(eil.empty()) continue;
        Studentas A;
        std::istringstream eilute(eil);
        if (eilute >> A) 
        { 
            skaiciuoti_viska(A);
            grupe.push_back(std::move(A));
        }    
    }
    fd.close();
}


template < typename Container >
void rusiavimas_maz (Container& grupe)
{
    if constexpr (std::is_same_v<Container, std::list<Studentas>>)
    {
        grupe.sort([](const Studentas &a, const Studentas &b) 
        {
            return a.vidurkis() > b.vidurkis();
        });
    } 
    else 
    {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) 
        {
            return a.vidurkis() > b.vidurkis();
        });

    }
}

template < typename Container >
void stunedu_skirstymas (Container& grupe)
{
    Container vargsiukai;
    Container kietakai;

    if constexpr (std::is_same_v<Container, Vector<Studentas>>) 
    {
        vargsiukai.reserve(grupe.size() / 2);
        kietakai.reserve(grupe.size() / 2);
    }

    for (auto &x : grupe) 
    {
        if (x.vidurkis() < 5.0)
            vargsiukai.push_back(std::move(x));
        else
            kietakai.push_back(std::move(x));
    }
    
    isvedimas(vargsiukai, kietakai);

    grupe.clear(); 
}


template <typename Container>
void pirma_strategija(Container& grupe){
    Container vargsiukai;
    Container kietakai;

    for (const auto &s : grupe)
    {
        if (s.vidurkis() < 5){
            vargsiukai.push_back(s);
        } else if (s.vidurkis() >= 5){
            kietakai.push_back(s);
        }
    }

    if constexpr(std::is_same_v<Container, Vector<Studentas>> || std::is_same_v<Container, deque<Studentas>>){
        vargsiukai.shrink_to_fit();
        kietakai.shrink_to_fit();
    }

    isvedimas(vargsiukai, kietakai);
}

template <typename Container>
void antra_strategija (Container& grupe)
{
    Container vargsiukai;
    while (!grupe.empty() && grupe.back().vidurkis() < 5.0) 
    {
        vargsiukai.push_back(std::move(grupe.back())); 
        grupe.pop_back();
    }

    isvedimas(vargsiukai, grupe);
}

template <typename Container>
void trecia_strategija(Container& grupe) {
    Container vargsiukai;
    
    auto it = std::stable_partition(grupe.begin(), grupe.end(), [](const Studentas& s) 
    {
        return s.vidurkis() >= 5.0;
    });

    std::move(it, grupe.end(), std::back_inserter(vargsiukai));
    grupe.erase(it, grupe.end());
    
    if constexpr(std::is_same_v<Container, Vector<Studentas>>)
     {
        grupe.shrink_to_fit();
    }

    isvedimas(vargsiukai, grupe);    
}

template <typename Container>
void tyrimas (string failas, Container& grupe, string tipas)
{
    double nuskaitym = 0, rikiav = 0, skirst = 0;

    cout << "Testuojamas " << tipas  << endl;

    for (int i = 0; i < 3; i++) 
    {
        grupe.clear();
        auto s = std::chrono::high_resolution_clock::now();
        skaityti_failus(failas, grupe);
        auto e = std::chrono::high_resolution_clock::now();
        nuskaitym += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        rusiavimas_maz(grupe);
        e = std::chrono::high_resolution_clock::now();
        rikiav += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        stunedu_skirstymas(grupe);
        e = std::chrono::high_resolution_clock::now();
        skirst += std::chrono::duration<double>(e - s).count();

    }

    cout << tipas << " rezultatai (vidurkis is 3 bandymu):" << endl;
    cout << "  Nuskaitymas užtruko: " << nuskaitym / 3.0 << " s" << endl;
    cout << "  Rikiavimas užtruko:   " << rikiav / 3.0 << " s" << endl;
    cout << "  Skirstymas užtruko:   " << skirst / 3.0 << " s" << endl;
    cout << "  Bendras veikimos laikas:      " << (nuskaitym + rikiav + skirst) / 3.0 << " s" << endl;
}

template <typename Container>
void strategiju_tyrimas (string failas, Container& grupe, string tipas)
{
    double nuskaitym = 0, rikiav = 0, skirst = 0;



    for (int i = 0; i < 3; i++) 
    {
        grupe.clear();
        auto s = std::chrono::high_resolution_clock::now();
        skaityti_failus(failas, grupe);
        auto e = std::chrono::high_resolution_clock::now();
        nuskaitym += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        rusiavimas_maz(grupe);
        e = std::chrono::high_resolution_clock::now();
        rikiav += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        pirma_strategija(grupe);
        e = std::chrono::high_resolution_clock::now();
        skirst += std::chrono::duration<double>(e - s).count();

    }
    cout << "Programa su " << tipas << " vidutiniškai užtruko:      " << (nuskaitym + rikiav + skirst) / 3.0 << " s" << endl;
}

template <typename Container>
void strategijos_du_tyrimas (string failas, Container& grupe, string tipas)
{
    double nuskaitym = 0, rikiav = 0, skirst = 0;



    for (int i = 0; i < 3; i++) 
    {
        grupe.clear();
        auto s = std::chrono::high_resolution_clock::now();
        skaityti_failus(failas, grupe);
        auto e = std::chrono::high_resolution_clock::now();
        nuskaitym += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        rusiavimas_maz(grupe);
        e = std::chrono::high_resolution_clock::now();
        rikiav += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        antra_strategija(grupe);
        e = std::chrono::high_resolution_clock::now();
        skirst += std::chrono::duration<double>(e - s).count();

    }
    cout << "Programa su " << tipas << " vidutiniškai užtruko:      " << (nuskaitym + rikiav + skirst) / 3.0 << " s" << endl;
}

template <typename Container>
void strategijos_trys_tyrimas (string failas, Container& grupe, string tipas)
{
    double nuskaitym = 0, rikiav = 0, skirst = 0;



    for (int i = 0; i < 3; i++) 
    {
        grupe.clear();
        auto s = std::chrono::high_resolution_clock::now();
        skaityti_failus(failas, grupe);
        auto e = std::chrono::high_resolution_clock::now();
        nuskaitym += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        rusiavimas_maz(grupe);
        e = std::chrono::high_resolution_clock::now();
        rikiav += std::chrono::duration<double>(e - s).count();

        s = std::chrono::high_resolution_clock::now();
        trecia_strategija(grupe);
        e = std::chrono::high_resolution_clock::now();
        skirst += std::chrono::duration<double>(e - s).count();

    }
    cout << "Programa su " << tipas << " vidutiniškai užtruko:      " << (nuskaitym + rikiav + skirst) / 3.0 << " s" << endl;
}

template < typename Container >
void isvedimas (Container &vargsiukai, Container &kietakai)
{

    auto i_faila = [](string pav, Container& duomenys) 
    {
        std::ofstream fr(pav);
        fr << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis" << endl;
        for (const auto &s : duomenys) {
            fr << left << setw(20) << s.vardas() << setw(20) << s.pavarde() << std::fixed << std::setprecision(2) << s.vidurkis() << "\n";
        }
        fr.close();
    };

    i_faila("vargsiukai.txt", vargsiukai);


    i_faila("kietaikai.txt", kietakai);
}

#endif