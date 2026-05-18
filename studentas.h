#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>
#include <random>
#include "RandInt.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include "zmogus.h"
#include "vector.h"
#include <deque>

using std:: string;
//using std:: vector;
using std:: cout;
using std:: cin;
using std:: accumulate;
using std:: setw;
using std:: left;
using std:: right;
using std:: endl;


class Studentas : public Zmogus {
    private:
        Vector <int> paz_;
        int egz_paz_;
        double Vidurkis_;
        double Mediana_;

    public:

        Studentas() : Zmogus(), paz_({0}), egz_paz_(0), Vidurkis_(0.0), Mediana_(0.0) { } 

        Studentas(string v, string p, Vector<int> pazymiai) : Zmogus(v, p), paz_(pazymiai), egz_paz_(0), Vidurkis_(0.0), Mediana_(0.0) { }

        Studentas(std::istream& is);

        // copy konstruktorius
        Studentas(const Studentas& s): 
            Zmogus(s), 
            paz_(s.paz_), 
            egz_paz_(s.egz_paz_), 
            Vidurkis_(s.Vidurkis_), 
            Mediana_(s.Mediana_) {}

        // move konstruktorius
        Studentas(Studentas&& s) noexcept : 
            Zmogus(std::move(s)), 
            paz_(std::move(s.paz_)),
            egz_paz_(s.egz_paz_),
            Vidurkis_(s.Vidurkis_),
            Mediana_(s.Mediana_) { s.egz_paz_ = 0; s.Vidurkis_ = 0.0; s.Mediana_ = 0.0; }

        ~Studentas(){
            Clear();
        }

        inline const Vector<int>& pazymiai() const { return paz_; }
        inline int egzaminas() const { return egz_paz_; }
        inline double vidurkis() const { return Vidurkis_; }
        inline double mediana() const { return Mediana_; }


        inline void setGalutinisV(double galutVid) { Vidurkis_ = galutVid; }
        inline void setGalutinisM(double galutMed) { Mediana_ = galutMed; }
        inline void setEgzaminas(int egz) {egz_paz_ = egz; }
        inline void setPazymiai(Vector<int> paz) {paz_ = paz;}

        void apskaiciuot_vidurkis();
        void apskaiciuoti_mediana();

        // copy assignment operatorius
        Studentas& operator = (const Studentas& s)
        {
            if (this == &s)
                return *this;

            Zmogus::operator=(s);
            paz_ = s.paz_;
            egz_paz_ = s.egz_paz_;
            Vidurkis_ = s.Vidurkis_;
            Mediana_ = s.Mediana_;

            return *this;
        }

        // move assignment operatorius
        Studentas& operator = (Studentas&& s) noexcept
        {
            if (this == &s) 
                return *this;

            Zmogus::operator=(std::move(s));
            paz_ = std::move(s.paz_);
            egz_paz_ = s.egz_paz_;
            Vidurkis_ = s.Vidurkis_;
            Mediana_ = s.Mediana_;

            Clear();

            return *this;
        }

         friend bool operator==(const Studentas& s1, const Studentas& s2) 
        {
            return (s1.Vardas_ == s2.Vardas_ && s1.Pavarde_ == s2.Pavarde_ && s1.egz_paz_ == s2.egz_paz_ && s1.Vidurkis_ == s2.Vidurkis_ && s1.Mediana_ == s2.Mediana_);
        }

        //input operatorius
        friend std::istream& operator>>(std::istream& in, Studentas& s);

        //output operatorius
        friend std::ostream& operator<<(std::ostream& out, const Studentas &s);

        bool Clear()
        {
            return (Vardas_.empty()) && (Pavarde_.empty()) && (paz_.empty()) && (egz_paz_== 0) && (Vidurkis_ == 0.0) && (Mediana_== 0.0);
        }

        void printInfo() const override 
        {
            cout << "Vardas: " << vardas() << ", Pavarde: " << pavarde() << endl;
        }

};


void failu_generavimas(int Studentu_sk);
void studentu_skirstymas(Vector < Studentas > &grupe);
void isvedimas_i_du_failus (Vector < Studentas > &vargsiukai, Vector < Studentas > &kietakai);
void skaiciuoti_viska(Studentas &x);
void skaityti_faila_automatiskai(string pav, Vector<Studentas>& grupe);
string pasirinkimas ();
void skaityti_faila(Vector < Studentas > &grupe);
void duomenu_ivedimas(Vector < Studentas > &grupe);
void skaiciu_generevimas(Studentas &A);
void rezultatai (Vector < Studentas > &grupe);
void rezultatu_isvedimas(Vector < Studentas > &grupe);
bool pagal_varda(const Studentas &a, const Studentas &b);
bool pagal_pavarde(const Studentas &a, const Studentas &b);
bool pagal_vid_did(const Studentas &a, const Studentas &b);
bool pagal_vid_maz(const Studentas &a, const Studentas &b);
bool pagal_med_did(const Studentas &a, const Studentas &b);
bool pagal_med_maz(const Studentas &a, const Studentas &b);
void rikiavimas(Vector < Studentas > &grupe);
void meniu(Vector < Studentas > &grupe);
void strategija_1();
void strategija_2();
void strategija_3();


#endif