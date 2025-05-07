#include <iostream>
#include <array>
#include <string>
using namespace std;

class Persoana 
{

protected:
    string nume;
    int varsta;

public:
    Persoana() : nume(""), varsta(0) {}
    Persoana(string nume, int varsta) : nume(nume), varsta(varsta) {}
    Persoana(Persoana &other) : nume(other.nume), varsta(other.varsta) {}

    Persoana &operator=(Persoana other)
    {
        nume = other.nume;
        varsta = other.varsta;

        return this;
    }

    virtual ~Persoana() {}

    string getNume()
    {
        return nume;
    }
    int getVarsta()
    {
        return varsta;
    }

    virtual void afisare() const = 0;
};

class Jucator : public Persoana
{

private:
    string pozitie;
    int numar;
    
public:
    Jucator() : Persoana(), pozitie("N/A"), numar(0) {}
    Jucator(const string nume, int varsta, string pozitie, int numar) : Persoana(nume, varsta), pozitie(pozitie), numar(numar) {}
    Jucator(Jucator &other) : Persoana(other), pozitie(other.pozitie), numar(other.numar) {}

    ~Jucator() {}

    Jucator &operator=(Jucator other)
    {
        Persoana::operator=(other);
        pozitie = other.pozitie;
        numar = other.numar;

        return this;
    }

    bool operator==(Jucator other)
    {
        return nume == other.nume && numar == other.numar
    }

    string getPozitie()
    {
        return pozitie;
    }
    int getNumar()
    {
        return numar;
    }
    void afisare() override 
    {
        cout<<"Nume: "<<nume<<\n<<"Pozitie: "<<pozitie<<\n<<"Numar: "<<numar<<\n<<"Varsta: "<<varsta<<\n;
    }
    friend ostream &operator<<(ostream &out, Jucator j)
    {
        out << j.nume << " " << j.pozitie << " " << j.numar << " " << j.varsta;
        return out;
    }
};


int main() {
    
    return 0;
}
