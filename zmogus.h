#include <iostream>
#include <utility>
using std::string;

class Zmogus {
    protected:
        string Vardas_;
        string Pavarde_;
    public:
        Zmogus() : Vardas_(""), Pavarde_("") {}
        Zmogus(string v, string p) : Vardas_(v), Pavarde_(p) {}

        Zmogus(const Zmogus& z): 
           Vardas_(z.Vardas_),
           Pavarde_(z.Pavarde_)  {}

         Zmogus(Zmogus&& z) noexcept 
         : Vardas_(std::move(z.Vardas_)),
          Pavarde_(std::move(z.Pavarde_)) {}


        inline string vardas() const { return Vardas_; }
        inline string pavarde() const { return Pavarde_; }

        inline void setVardas(string var) { Vardas_ = var; }
        inline void setPavarde(string pav) { Pavarde_ = pav; }

        Zmogus& operator=(const Zmogus& z) 
        {
        if (this != &z) {
            Vardas_ = z.Vardas_;
            Pavarde_ = z.Pavarde_;
        }
        return *this;
        }

        Zmogus& operator=(Zmogus&& z) noexcept 
        {
            if (this != &z) {
                Vardas_ = std::move(z.Vardas_);
                Pavarde_ = std::move(z.Pavarde_);
            }
            return *this;
        }

        virtual ~Zmogus() {
            Vardas_.clear();
            Pavarde_.clear();
        }

         virtual void printInfo() const = 0;
};