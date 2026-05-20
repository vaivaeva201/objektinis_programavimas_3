# objektinis_programavimas_3
# v3.0

šioje laboratorinio versijoje sukurta Vector klasė ir palyginamas jos veikimas su std::vector naudotu senesniose versijose (v1.5).

**std::vector vs Vector class**

* Lyginama kiek vidutiniškai užtrunka tuščius vektorius užpildyti int elementų naudojant push_back() funkciją:

| Vektoriaus elementų kiekis | std::vector | Vector klasei | 
| --- | --- | --- |
| 10000 | 0.000558111 | 0.000293931 |
| 100000 | 0.00342118 | 0.00172783 |
| 1000000 | 0.0215837 | 0.0100205 |
| 10000000 | 0.201045 | 0.115422 |
| 100000000 | 2.04973 | 1.10308 |

* Lyginama kiek kartų įvyksta atminties perskirstymai:

| Vektoriaus elementų kiekis | std::vector | Vector klasei | 
| --- | --- | --- |
| 10000 | 14 | 14 |
| 100000 | 17 | 17 |
| 1000000 | 20 | 20 |
| 10000000 | 24 | 24 |
| 100000000 | 27 | 27 |

* Atlikta spartos analiė. Lyginama su 3 strategijos rezultatai v1.5.

| Studentų kiekis faile | Konteinerio tipas | Programos veikimo laikas |
| --- | --- | --- |
| 100 000 | std::vector | 0.904644 s |
| 100 000 | Vector klasė | 0.939137 s |
| 1 000 000 | std::vector | 9.17372 s |
| 1 000 000 | Vector klasė | 9.53246 s |
| 10 000 000 | std::vector | 99.0563 s |
| 10 000 000 | Vector klasė | 102.984 s |


**Funkcijų aprašymas**
* push_back()
Prideda naują elementą į vektoriaus galą.
Jei vektoriuje nėra laisvos vietos, funkcija naują taplą padidina 2 kartus.

````cpp
void push_back(const T& value)
        {
            if(size_ < capacity_)
            {
                data_[size_] = value;
                size_++;
            }
            else
            {
                capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                T *newdata_ = new T[capacity_];
                for (size_t i = 0; i < size_; i++)
                {
                    newdata_[i] = data_[i];
                }
                newdata_[size_] = value;
                size_++;
                delete[] data_;
                data_ = newdata_;
            }

        }
`````
* reverse()
Rankinis atminties rezervavimas.
Jei new_cap didesnis už esamą talpą, išskiriamas naujas, didesnis atminties blokas, į kurį perkeliami esami elementai, o senoji atmintis atlaisvinama.

````cpp
void reserve(size_type new_cap) 
        {
            if (new_cap > capacity_) 
            {
                T* newdata = new T[new_cap];
                for (size_t i = 0; i < size_; i++) 
                    newdata[i] = std::move(data_[i]);
                delete[] data_;
                data_ = newdata;
                capacity_ = new_cap;
            }
        }
`````

* shrink_to_fit()
Atlaisvina nenaudojamą rezervuotą atmintį, suvienodindama talpą su esamu elementų kiekiu.

````cpp
void shrink_to_fit()
        {
            if (capacity_ > size_) 
            {
                T* newdata_ = new T[size_];
                for (size_type i = 0; i < size_; ++i) {
                    newdata_[i] = std::move(data_[i]);
                }
                delete[] data_;
                data_ = newdata_;
                capacity_ = size_;
            }
        }
`````

* operator[]
Grąžina nuorodą į elementą vektoriuje.

````cpp
T& operator[](size_t index)
        {
            return data_[index];
        }
`````

* insert()
Įterpia naują elementą į nurodytą poziciją. Visi elementai nuo nurodytos pozicijos iki galo pastumiami viena vieta į dešinę, o laisvoje vietoje įrašoma nauja reikšmė.

````cpp
void insert(size_t index, const T& value) 
        {
            if (index > size_) 
                throw std::out_of_range("Insert index out of range");
            if (size_ == capacity_) 
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            
            for (size_t i = size_; i > index; --i) 
            {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[index] = value;
            size_++;
        }
`````

**Pagrindinės programos funkcijos**
* 1. Įvesti visus studento duomenis ranka;
* 2. Sugeneruoti atsitiktinius pažymius, bet studento vardą ir pavardę įvesti ranka;
* 3. Sudenetuoti studento vardą, pavardę ir pažymius;
* 4. Nuskaityti duomenis iš failo;
* 5. Testuoti programą;
* 6. Testuoti tris strategijas;
