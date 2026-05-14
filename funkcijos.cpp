#include "studentas.h"
#include "vector.h"

void failu_generavimas(int Studentu_sk)
{
    auto start = std::chrono::high_resolution_clock::now();
    string pav = "Studentai_" + std::to_string(Studentu_sk) + ".txt";
    std::ofstream fr(pav);

    fr << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    RandInt rnd{3, 18};
    int kiek = rnd();

    for (int i = 1; i <= kiek; i++) 
        fr << left << setw(20) << "ND" + std::to_string(i);
    fr << left << setw(20) << "Egz." << endl;

    RandInt random{1, 10};
    
    for (int i = 0; i < Studentu_sk; i++) 
    {
        fr << left << setw(20) << ("Vardas" + std::to_string(i+1)) << setw(20) << ("Pavarde" + std::to_string(i+1));
        
        for (int j = 0; j < kiek; j++) 
        {
            fr << left << setw(20) << random();
        }
        fr << left << setw(20) << random() << "\n";
    }
    fr.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Failo " << pav << " sukurimas uztruko: " << diff.count() << " s" << endl;

}

void studentu_skirstymas(Vector < Studentas > &grupe)
{
    auto start = std::chrono::high_resolution_clock::now();

    Vector<Studentas> vargsiukai;
    Vector<Studentas> kietakai;

    vargsiukai.reserve(grupe.size() / 2);
    kietakai.reserve(grupe.size() / 2);

    for (auto &x : grupe) 
    {
        if (x.vidurkis() < 5.0) 
            vargsiukai.push_back(std::move(x));
        else
            kietakai.push_back(std::move(x));
    }
    
    grupe.clear();
    grupe.shrink_to_fit(); 

    auto end = std::chrono::high_resolution_clock::now();
    cout << "Skirstymas uztruko: " << std::chrono::duration<double>(end - start).count() << " s" << endl;
    rikiavimas(vargsiukai);
    rikiavimas(kietakai);
    isvedimas_i_du_failus(vargsiukai, kietakai);
}

void isvedimas_i_du_failus (Vector < Studentas > &vargsiukai, Vector < Studentas > &kietakai)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto i_faila = [](string pav, Vector<Studentas>& duomenys) 
    {
        std::ofstream fr(pav);
        fr << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis" << endl;
        for (const auto &s : duomenys) {
            fr << left << setw(20) << s.vardas() << setw(20) << s.pavarde() << std::fixed << std::setprecision(2) << s.vidurkis() << "\n";
        }
        fr.close();
    };

    i_faila("vargsiukai.txt", vargsiukai);
    vargsiukai.clear();
    vargsiukai.shrink_to_fit();

    i_faila("kietaikai.txt", kietakai);
    kietakai.clear();
    kietakai.shrink_to_fit();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Grupių įrašymas į failus užtruko: " << diff.count() << " s" << endl;

}

void skaiciuoti_viska(Studentas &x)
{
    Vector<int> temp_paz = x.pazymiai(); 
    int egz = x.egzaminas();

    double sum = accumulate(temp_paz.begin(), temp_paz.end(), 0.0);
    double vid = (sum / temp_paz.size()) * 0.4 + egz * 0.6;
    x.setGalutinisV(vid);

    double mediana;
    std::sort(temp_paz.begin(), temp_paz.end());

    if (temp_paz.size() % 2 == 0)
    {
        mediana = (temp_paz[temp_paz.size() / 2 - 1] + temp_paz[temp_paz.size() / 2]) / 2.0;
    }
    else
    {
        mediana = temp_paz[temp_paz.size() / 2];
    }
    double med = mediana * 0.4 + egz * 0.6;
    x.setGalutinisM(med);   
}

void skaityti_faila_automatiskai(string pav, Vector<Studentas>& grupe)
{
    
    std::ifstream fd(pav);
    if (!fd) 
    {
        std::cerr << "Klaida: nepavyko atidaryti failo!" << endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    string eil;
    getline(fd, eil);

    while(getline(fd, eil)) 
    {
        if(eil.empty()) continue;
        Studentas A;
        std::istringstream eilute(eil);
        string v, p;
        if (!(eilute >> v >> p)) continue;

        Vector<int> temp_paz;
        int pazymys;
        while (eilute >> pazymys) 
        {
            temp_paz.push_back(pazymys);
        }
        
        if (!temp_paz.empty()) 
        {
            int egz = temp_paz.back();
            temp_paz.pop_back();

            Studentas A;
            A.setVardas(v);
            A.setPavarde(p);
            A.setPazymiai(temp_paz);
            A.setEgzaminas(egz);

            skaiciuoti_viska(A);
            grupe.push_back(std::move(A));
        }
    }
    fd.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Failo nuskaitymas uztruko: " << diff.count() << " s" << endl;

}

string pasirinkimas ()
{
    string failas;
    std:: ifstream fd;
    while (true)
    {
        system("ls *.txt");
        cout<<"Ivesk failo pavadinima: ";
        cin>>failas;

        try
        {
            fd.open(failas);
            if (!fd)
            {
                    throw std::runtime_error("Klaida: nepavyko atidaryti failo!");
            }
            break;
        }
        catch (const std::runtime_error &e)
	    {
		    std::cerr << e.what() << endl;
            fd.clear();
	    }
    }
    return failas;
}

void skaityti_faila(Vector < Studentas > &grupe)
{
    string failas;
    std:: ifstream fd;
    while (true)
    {
        system("ls *.txt");
        cout<<"Ivesk failo pavadinima: ";
        cin>>failas;

        try
        {
            fd.open(failas);
            if (!fd)
            {
                    throw std::runtime_error("Klaida: nepavyko atidaryti failo!");
            }
            break;
        }
        catch (const std::runtime_error &e)
	    {
		    std::cerr << e.what() << endl;
            fd.clear();
	    }
    }

    auto start = std::chrono::high_resolution_clock::now();

    std:: stringstream buferis;
    string eil;

    if (!fd)
    {
        std:: cerr << "Klaida: nepavyko atidaryti failo!" << endl;
        return;
    }
    buferis << fd.rdbuf();
    fd.close();
    getline(buferis, eil);

    while(getline(buferis, eil))
    {
       std::istringstream eilute(eil);
        Studentas A;
        eilute >> A;
        skaiciuoti_viska(A);
        grupe.push_back(std::move(A));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Failo nuskaitymas ir skaičiavimai užtruko: " << diff.count() << " s" << endl;
}

void duomenu_ivedimas(Vector < Studentas > &grupe)
{

    while(true)
    {
        string v, p;
        int temp;
        Vector<int> temp_paz;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Įveskite studento vardą (jeigu įvedetė visus norimus studentus įrašykite 'x'): ";
        getline(cin, v);
        if (v == "x")
        {
            break;
        }
        cout << "Įveskite studento pavardę: ";
        getline(cin, p);

        cout << "Įveskite semestro pažymius (jeigu įvedetė visus norimus pažymius įrašykite '-1'):" << endl;
        while (true)
        {
            try
            {
                cin >> temp;
                if(cin.fail() || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Įvedėte ne skaičių.");
                }
                if (temp == -1)
                    break;
                if(temp < 1 || temp > 10)
                    throw std::out_of_range("Neteisingas pažymys! Įveskite sveikąjį skaičių nuo 1 iki 10.");
                temp_paz.push_back(temp);
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
            catch(const std::out_of_range& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
        }
        int temp_egz;
        cout << "Įveskite egzamino pažymį: ";
        while (true)
        {   
            try
            {
                cin >> temp_egz;   
                if(cin.fail() || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Įvedėte ne skaičių.");
                }
                if(temp_egz < 1 || temp_egz> 10)
                    throw std::out_of_range("Neteisingas pažymys! Įveskite sveikąjį skaičių nuo 1 iki 10.");
                break;
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
            catch(const std::out_of_range& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
        }

        Studentas A;
        A.setVardas(v);
        A.setPavarde(p);
        A.setPazymiai(temp_paz);
        A.setEgzaminas(temp_egz);

        grupe.push_back(std::move(A));
    }  
    
}

void vidurkis(Studentas &x)
{
    const Vector<int>& p = x.pazymiai(); 
 
    if (p.empty()) {
        double galutinis = x.egzaminas() * 0.6;
        x.setGalutinisV(galutinis);
        return;
    }

    double sum = std::accumulate(p.begin(), p.end(), 0.0);
    
    double galutinis_rez = (sum / (p.size() * 1.0)) * 0.4 + x.egzaminas() * 0.6;
    
    x.setGalutinisV(galutinis_rez);

}

void mediana(Studentas &x)
{
    double med_reiksme;
    Vector<int> temp_paz = x.pazymiai();

    if (temp_paz.empty()) 
    {
        double galutinis = x.egzaminas() * 0.6;
        x.setGalutinisM(galutinis);
        return;
    }

   std::sort(temp_paz.begin(), temp_paz.end());

    if (temp_paz.size() % 2 == 0)
    {
        med_reiksme = (temp_paz[temp_paz.size() / 2 - 1] + temp_paz[temp_paz.size() / 2]) / 2.0;
    }
    else
    {
        med_reiksme = temp_paz[temp_paz.size() / 2];
    }

    double galutinis_med = med_reiksme * 0.4 + x.egzaminas() * 0.6;
    x.setGalutinisM(galutinis_med);
}

void skaiciu_generevimas(Studentas &A)
{

    RandInt rnd{1, 10};
    int kiek = rnd();
    Vector<int> temp_paz;

    for (int i = 0; i < kiek; i++)
    {
       temp_paz.push_back(rnd());
    }

    A.setPazymiai(temp_paz);
    A.setEgzaminas(rnd());

}

void rezultatai (Vector < Studentas > &grupe)
{
    int formatas;
    cout << "Prašau pasirinkite ar norite galutinį balą skaičiuoti su vidurkiu ar mediana. (Vidurkiu - 0, mediana - 1): ";
    while (true)
    { 
        try
        {
            cin >> formatas;   
                if(cin.fail() || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Įvedėte ne skaičių.");
                }
                if(formatas != 1 && formatas != 0)
                    throw std::out_of_range("Neteisingas skaičius! Įveskite 0 arba 1.");
                break;
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
            catch(const std::out_of_range& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
    }

    cout << left << setw(20) << "Pavardė" << setw(20) << "Vardas";

    if (formatas == 0)
    {
        cout << std::setw(20) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (auto &x : grupe)
        {
            vidurkis(x);
            cout << left << setw(20) << x.pavarde() << setw(20) << x.vardas() << setw(20) << std::fixed << std::setprecision(2) << x.vidurkis() << endl;

        }
    }
    else
    {
        cout << std::setw(20) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (auto &x : grupe)
        {
        mediana(x);
        cout << left << setw(20) << x.pavarde() << setw(20) << x.vardas() << setw(20) << std::fixed << std::setprecision(2) << x.mediana() << endl;
        }

    }

}

void rezultatu_isvedimas(Vector < Studentas > &grupe)
{

    std::ostringstream buferis;
    buferis << left << setw(20) << "Pavardė" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    buferis << "----------------------------------------------------------------------------" << endl;

    for (auto &x : grupe) {
        buferis << left << setw(20) << x.pavarde() << setw(20) << x.vardas() << setw(20) << std::fixed << std::setprecision(2) << x.vidurkis() << setw(20) << std::fixed << std::setprecision(2) << x.mediana() << endl;
    }

    int pasirinkimas = 0;

    cout << "Pasirinkite kur norite matyti rezultatus: " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "1 - Komandinėje eilutėje;" << endl;
    cout << "2 - Faile;" << endl;
    cout << endl;

    while (true)
    { 
        try
        {
            cin >> pasirinkimas;   
                if(cin.fail() || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Įvedėte ne skaičių.");
                }
                if(pasirinkimas < 1 ||  pasirinkimas > 2)
                    throw std::out_of_range("Neteisingas pasirinkimas! Prašau įveskite vieną iš duotų variantų.");
                break;
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
            catch(const std::out_of_range& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
    }

    switch(pasirinkimas)
    {
        case 1:
            cout << buferis.str();
            break;
        case 2:
        {
            std::ofstream fr("studentuRezultatai.txt");
            fr << buferis.str();
            fr.close();
            break;
        }    
        default: 
                cout << "Prašau įveskite vieną iš duotų variantų " << endl; 

    }   

}

bool pagal_varda(const Studentas &a, const Studentas &b) 
{ 
    return a.vardas() < b.vardas(); 
}

bool pagal_pavarde(const Studentas &a, const Studentas &b) 
{ 
    return a.pavarde() < b.pavarde(); 
}

bool pagal_vid_did(const Studentas &a, const Studentas &b) 
{ 
    return a.vidurkis() < b.vidurkis(); 
}

bool pagal_vid_maz(const Studentas &a, const Studentas &b) 
{ 
    return a.vidurkis() > b.vidurkis(); 
}

bool pagal_med_did(const Studentas &a, const Studentas &b) 
{ 
    return a.mediana() < b.mediana(); 
}

bool pagal_med_maz(const Studentas &a, const Studentas &b) 
{ 
    return a.mediana() > b.mediana(); 
}

void rikiavimas(Vector < Studentas > &grupe)
{
    int pasirinkimas = 0;
    cout << "Pasirinkite rikiavimo būdą:" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "1 - Rikiuoti pagal vardą;" << endl;
    cout << "2 - Rikiuoti pagal pavardę;" << endl;
    cout << "3 - Rikiuoti pagal vidurkį (nuo mažiausio iki didžiausio);" << endl;
    cout << "4 - Rikiuoti pagal vidurkį (nuo didžiausio iki mažiausio);" << endl;
    cout << "5 - Rikiuioti pagal mediana (nuo mažiausio iki didžiausio);" << endl;
    cout << "6 - Rikiuoti pagal mediana (nuo didžiausio iki mažiausio);" << endl;
    cout << endl;

    while (true)
    { 
        try
        {
            cin >> pasirinkimas;
                if(cin.fail() || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Įvedėte ne skaičių.");
                }
                if(pasirinkimas < 1 ||  pasirinkimas > 6)
                    throw std::out_of_range("Neteisingas pasirinkimas! Prašau įveskite vieną iš duotų variantų.");
                break;
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
            catch(const std::out_of_range& e)
            {
                std::cerr << e.what() << " Įveskite dar kartą: " << endl;
            }
    }

    switch (pasirinkimas)
    {
    case 1:
        std::sort(grupe.begin(), grupe.end(), pagal_varda);
        break;
    case 2:
        std::sort(grupe.begin(), grupe.end(), pagal_pavarde);
        break;
    case 3:
        std::sort(grupe.begin(), grupe.end(), pagal_vid_did);
        break;
    case 4:
        std::sort(grupe.begin(), grupe.end(), pagal_vid_maz);
        break;
    case 5:
        std::sort(grupe.begin(), grupe.end(), pagal_med_did);
        break;
    case 6:
        std::sort(grupe.begin(), grupe.end(), pagal_med_maz);
        break;
    default:
        cout << "Prašau įveskite vieną iš duotų variantų " << endl; 
    }
}

void meniu(Vector < Studentas > &grupe)
{
    int pasirinkimas = 0;

    while(pasirinkimas != 7)
    {    
        cout << endl;
        cout << "Pasirinkite programos eigą: " << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "1 - Viską įvesti ranka;" << endl;
        cout << "2 - Generuoti pažymius;" << endl;
        cout << "3 - Generuoti studentų vardus, pavardes ir pažymius;" << endl;
        cout << "4 - Nuskaityti duomenis iš failo;" << endl;
        cout << "5 - Testuoti programą;" << endl;
        cout << "6 - Testuoti klasę;" << endl;
        cout << "7 - Baigti darbą;" << endl;
        cout << endl;

        while (true)
        { 
            try
            {
                cin >> pasirinkimas;   
                    if(cin.fail() || cin.peek() != '\n')
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::invalid_argument("Įvedėte ne skaičių.");
                    }
                    if(pasirinkimas < 1 ||  pasirinkimas > 7)
                        throw std::out_of_range("Neteisingas pasirinkimas! Prašau įveskite vieną iš duotų variantų.");
                    break;
                }
                catch(const std::invalid_argument& e)
                {
                    std::cerr << e.what() << " Įveskite dar kartą: " << endl;
                }
                catch(const std::out_of_range& e)
                {
                    std::cerr << e.what() << " Įveskite dar kartą: " << endl;
                }
        }

        switch(pasirinkimas)
        {
            case 1:
                cout << "Pasirinkote viską įvesti ranka " << endl;
                cout << "-----------------------------------------------------------" << endl;
                duomenu_ivedimas(grupe);
                rezultatai (grupe);
                
                break;

            case 2:
            {
                cout << "Pasirinkote generuoti pažymius " << endl;
                cout << "-----------------------------------------------------------" << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while(true)
                {
                    string v, p;
                    cout << "Įveskite studento vardą (jeigu įvedetė visus norimus studentus įrašykite 'x'): ";
                    getline(cin, v);
                    if (v == "x")
                    {
                        break;
                    }
                    cout << "Įveskite studento pavardę: ";
                    getline(cin, p);

                    Studentas A;
                    A.setVardas(v);
                    A.setPavarde(p);

                    skaiciu_generevimas(A);
                    grupe.push_back(std::move(A));
                } 
                rezultatai (grupe);

                break;
            }    
            case 3:
            {
                cout << "Pasirinkote generuoti studentų vardus, pavardes ir pažymius " << endl;
                cout << "-----------------------------------------------------------" << endl;
                int max = 10;
                RandInt rnd{1, max};
                int kiek = rnd();

                    string vardai[10] = {"Emilija", "Alma", "Viktorija", "Egle", "Ieva", "Petras", "Jonas", "Titas", "Matas", "Lukas"};
                    string pavardes_m[10] = {"Pavardaite1", "Pavardaite2", "Pavardaite3", "Pavardaite4", "Pavardaite5", "Pavardaite6", "Pavardaite7", "Pavardaite8", "Pavardaite9", "Pavardaite10"};
                    string pavardes_v[10] = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"};


                for (int i = 0; i < kiek; i++) 
                {
                    Studentas A;
                    RandInt rnd_idx(0, 9);
                    int v_idx = rnd_idx();
                    int p_idx = rnd_idx();

                    string v = vardai[v_idx];
                    string p;

                    char paskutine = v.back();
                    if (paskutine == 'a' || paskutine == 'e' || v == "Emilija") 
                        p = pavardes_m[p_idx];
                    else 
                        p = pavardes_v[p_idx];

                    A.setVardas(v);
                    A.setPavarde(p);
                    skaiciu_generevimas(A);
                    skaiciuoti_viska(A);
                    
                    grupe.push_back(std::move(A));
                }

                rezultatai (grupe);

                break;
            } 
            case 4:
                cout << "Pasirinkote nuskaityti duomenis iš failo " << endl;
                cout << "-----------------------------------------------------------" << endl;
                skaityti_faila(grupe);
                rikiavimas(grupe);
                rezultatu_isvedimas(grupe);

                break;   
            case 5:
            {
                cout << "Pasirinkote testuoti programa " << endl;
                cout << "-----------------------------------------------------------" << endl;
                //failu_generavimas(1000);
                //failu_generavimas(10000);
                //failu_generavimas(100000);
                //failu_generavimas(1000000);
                //failu_generavimas(10000000);
                Vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
                for (auto x : dydziai) {
                    cout << "Testas su " << x << " įrašų: " << endl;
                    cout << "-----------------------------------------------------------" << endl;
                    string failo_pav = "Studentai_" + std::to_string(x) + ".txt";
                    auto start = std::chrono::high_resolution_clock::now();

                    skaityti_faila_automatiskai(failo_pav, grupe);
                    studentu_skirstymas(grupe);

                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = end - start;
                    cout << "Visa programa uztruko: " << diff.count() << " s" << endl;
                    cout << endl;
                    grupe.clear();
                }
                break;
            }    
            case 6:
            {
                cout << "Pasirinkote testuoti klasę " << endl;
                cout << "-----------------------------------------------------------" << endl;
                cout << "1. Default konstruktorius:" << endl;
                Studentas s1;
                if (s1.vardas() == "" && s1.pavarde() == "" && s1.egzaminas() == 0 && s1.vidurkis() == 0.0 && s1.mediana() == 0.0)
                    cout << "Default konstruktorius VEIKIA" << endl;
                else 
                    cout << "Default konstruktorius NEVEIKIA" << endl;
                cout << endl;

                cout << "2. Pilnas konstruktorius: " << endl;
                Studentas s2("Vardas", "Pavarde", {9, 8, 7, 6, 9});
                if (s2 == Studentas("Vardas", "Pavarde", {9, 8, 7, 6, 9}) && s2.egzaminas() == 0 && s2.vidurkis() == 0.0 && s2.mediana() == 0.0)
                     cout << "Konstruktorius su parametrais veikia VEIKIA" << endl;
                else 
                    cout << "Konstruktorius su parametrais NEVEIKIA" << endl;
                cout << endl;

                cout << "3. Kopijavimo konstruktorius: " << endl;
                Studentas s3(s2);
                if(s3 == s2)
                    cout<<"Kopijavimo konstruktorius VEIKIA"<<endl;
                else 
                    cout<<"Kopijavimo konstruktorius NEVEIKIA"<<endl;
                cout << endl;

                cout << "4. Copy assignment operatorius: " << endl;
                Studentas s4;
                s4 = s2;
                if(s4 == s2)
                    cout<<"Copy assignment operatorius VEIKIA"<<endl;
                else 
                    cout<<"Copy assignment operatorius NEVEIKIA"<<endl;
                cout << endl;

                cout << "5. Move konstruktorius: " << endl;
                Studentas s5(std::move(s2));
                if(s5 == Studentas("Vardas", "Pavarde", {9, 8, 7, 6, 9}) && s2.Clear() == true)
                    cout<<"Move konstruktorius VEIKIA"<<endl;
                else 
                    cout<<"Move konstruktorius NEVEIKIA"<<endl;
                cout << endl;

                cout << "6. Move assignment operatorius: " << endl;
                Studentas s("Vardas", "Pavarde", {9, 8, 7, 6, 9});
                Studentas s6;
                s6 = std::move(s);
                if(s6 == Studentas("Vardas", "Pavarde", {9, 8, 7, 6, 9}) && s.Clear() == true)
                    cout<<"Move assignment VEIKIA"<<endl;
                else 
                    cout<<"Move assignment operatorius NEVEIKIA"<<endl;
                cout << endl;

                cout << "7. Destruktorius: " << endl;
                s4.~Studentas();
                if(s4.Clear() == true)
                    cout<<"Destruktorius VEIKIA"<<endl;
                else 
                    cout<<"Destruktorius NEVEIKIA"<<endl;
                cout << endl;

                cout << "8. Ivesties metodas: " << endl;
                std::istringstream in ("Vardas Pavarde 9 8 9 -1 9");
                Studentas s7;
                in >> s7;
                if (s7.vardas() == "Vardas" && s7.pavarde() == "Pavarde" && s7.egzaminas() == 9)
                    cout << "Ivesties metodas VEIKIA" << endl;
                else
                    cout << "Ivesties metodas NEVEIKIA" << endl;
                cout << endl;    

                cout << "9. Isvesties metodas: " << endl;
                std::ostringstream out;
                out << s7;
                if(out.str().find("Vardas") != string::npos && out.str().find("Pavarde") != string::npos)
                    cout << "Isvesties metodas VEIKIA" << endl;
                else 
                    cout << "Isvesties metodas NEVEIKIA" << endl;    
                cout << endl;
                
                /*
                cout << "10. Žmogaus klase: " << endl;
                Zmogus zmog("Vardas", "Pavarde");
                cout << zmog.vardas() << " " << zmog.pavarde() << endl;
                cout << endl;
                */
                    
                break;
            }
            case 7:
                cout << "Pasirinkote baigti darbą " << endl;
                cout << "-----------------------------------------------------------" << endl;

                break;
            default: 
                cout << "Prašau įveskite vieną iš duotų variantų " << endl; 
        }  
    }          
}


    std::istream& operator>>(std::istream& in, Studentas& s) {
    string eilute;
    if (!(getline(in, eilute)) || eilute.empty()) 
        return in;

    std::istringstream iss(eilute);
    string v, p;
    
    if (!(iss >> v >> p)) 
        return in;

    s.setVardas(v);
    s.setPavarde(p);

    Vector<int> temp_paz;
    int balas;
    
    while (iss >> balas) 
    {
        temp_paz.push_back(balas);
    }

    if (!temp_paz.empty()) 
    {
        
        s.setEgzaminas(temp_paz.back()); 
        temp_paz.pop_back();
        s.setPazymiai(temp_paz);
    }

    return in;
}

    std::ostream& operator<<(std::ostream& out, const Studentas &A) {
            out << std::left << std::setw(20) << A.pavarde() << std::setw(20) << A.vardas() << std::setw(20) << std::fixed << std::setprecision(2) << A.vidurkis() << std::setw(20) << std::fixed << std::setprecision(2) << A.mediana() << endl;
            return out;
        }