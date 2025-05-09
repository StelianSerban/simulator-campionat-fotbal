#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Persoana 
{

protected:
    string nume;
    int varsta;

public:
    Persoana() : nume(""), varsta(0) {}
    Persoana(const string &nume, int varsta) : nume(nume), varsta(varsta) {}
    Persoana(Persoana &other) : nume(other.nume), varsta(other.varsta) {}

    Persoana &operator=(Persoana &other)
    {
        if(this != &other)
        {
            nume = other.nume;
            varsta = other.varsta;
        }

        return *this;
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

template <typename T>
class Statistici
{
private:
    T valoare;
    string descriere;
public:
    Statistici() : valoare(), descriere("") {}
    Statistici(const T &valoare, const string &descriere) : valoare(valoare), descriere(descriere) {}

    T getValoare() 
    {
        return valoare;
    }
    string getDescriere()
    {
        return descriere;
    }

    void setValoare(T v)
    {
        valoare = v;
    }
    void setDescriere(const string &d)
    {
        descriere = d;
    }

    friend ostream &operator<<(ostream &out, const Statistici<T> &s)
    {
        out << "[ " << s.descriere << ": " << s.valoare << " ]";
        return out;
    }
    friend istream &operator>>(istream &in, Statistici<T> &s)
    {
        cout << "Descriere: "; in >> ws; getline(in, s.descriere);
        cout << "Valoare: "; in >> s.valoare;
        return in;
    }
};

class Jucator : public Persoana
{

private:
    string pozitie;
    int numar;
    
public:
    Jucator() : Persoana(), pozitie(""), numar(0) {}
    Jucator(const string &nume, int varsta, const string &pozitie, int numar) : Persoana(nume, varsta), pozitie(pozitie), numar(numar) {}
    Jucator(Jucator &other) : Persoana(other), pozitie(other.pozitie), numar(other.numar) {}

    ~Jucator() {}

    Jucator &operator=(Jucator &other)
    {
        if(this != &other)
        {
            Persoana::operator=(other);
            pozitie = other.pozitie;
            numar = other.numar;
        }

        return *this;
    }

    bool operator==(Jucator &other)
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
    friend ostream &operator<<(ostream &out, Jucator &j)
    {
        out << j.nume << " " << j.pozitie << " " << j.numar << " " << j.varsta;
        return out;
    }
    friend istream &operator>>(istream &in, Jucator &j)
    {
        cout << "Nume: "; in >> ws; getline(in, j.nume);
        cout << "Varsta: "; in >> j.varsta;
        cout << "Pozitie: "; in >> ws; getline(in, j.pozitie);
        cout << "Numar: "; in >> j.numar;
    }
};

class Antrenor : public Persoana 
{

private:
    string formatie;
    string stil;
    int aniExperienta;
public:
    Antrenor() : Persoana(), formatie(""), stil(""), aniExperienta() {}
    Antrenor(const string &nume, int varsta, const string &formatie, const string &stil, int aniExperienta) : Persoana(nume, varsta), formatie(formatie), stil(stil), aniExperienta(aniExperienta) {}
    Antrenor(const Antrenor &other) : Persoana(other), formatie(other.formatie), stil(other.stil), aniExperienta(other.aniExperienta) {}

    Antrenor &operator=(const Antrenor &other)
    {
        if(this != &other)
        {
            Persoana::operator=(other);
            formatie = other.formatie;
            stil = other.stil;
            aniExperienta = other.aniExperienta;
        }
        return *this;
    }

    ~Antrenor() {}

    void afisare() override 
    {
        cout<<"Nume: "<<nume<<\n<<"Varsta: "<<varsta<<\n<<"Formatie: "<<formatie<<\n<<"Stil: "<<stil<<\n<<"Ani experienta: "<<aniExperienta<<\n;
    }
    friend ostream &operator<<(ostream &out, const Antrenor &a)
    {
        out << a.nume << " " << a.varsta << " " << a.formatie << " " << a.stil << " " << a.aniExperienta;
    }
    friend istream &operator>>(istream &in, Antrenor &a)
    {
        cout << "Nume: "; in >> ws; getline(in, a.nume);
        cout << "Varsta: "; in >> a.varsta;
        cout << "Formatie: "; in >> ws; getline(in, a.formatie);
        cout << "Stil: "; in >> ws; getline(in, a.stil);
        cout << "Ani experienta: "; in >> a.aniExperienta;
        return in;
    }
};

class Echipa
{
private:
    string nume;
    vector<shared_ptr<Jucator>> jucatori;
    shared_ptr<Antrenor> antrenor;

public:
    Echipa() : nume("Nume necunoscut.") {}
    Echipa(string nume) : nume(nume) {}

    void adaugaJucator(shared_ptr<Jucator> j)
    {
        for(int i = 0; i < jucatori.size(); i++)
        {
            if(*jucatori[i] == *j)
            {
                cout << "Jucatorul " << j->getNume() << "exista deja.\n";
                return;
            }
        }
        jucatori.push_back(j);
    }

    void setAntrenor(shared_ptr<Antrenor> a)
    {
        antrenor = a;
    }

    string getNume() const
    {
        return nume;
    }

    vector<shared_ptr<Jucator>> getJucatori() const
    {
        return jucatori;
    }

    shared_ptr<Antrenor> getAntrenor() const
    {
        return antrenor;
    }

    void afisare()
    {
        cout << "=== Echipa: " << nume << " ===\n\n";

        cout << "Antrenor:";
        if(antrenor != nullptr)
        {
            cout << "\n";
            antrenor->afisare(cout);
        }
        else
        {
            cout << "Fara antrenor\n\n";
        }
        cout << "Jucatori:";
        if(jucatori.size() == 0)
        {
            cout << "Fara jucatori\n\n";
        }
        else
        {
            cout << "\n";
            for(int i = 0; i < jucatori.size(); i++)
            {
                jucatori[i]->afisare(cout);
            }
        }
        cout << "====================\n";
    }

    friend ostream &operator<<(ostream &out, const Echipa &e)
    {
        out << "Echipa: " << e.nume << "\n";
        out << "Antrenor: ";
        if (e.antrenor != nullptr)
            out << *(e.antrenor) << "\n";
        else
            out << "Fara antrenor\n";
        out << "Jucatori:\n\n";
        for(int i = 0; i < e.jucatori.size(); i++)
        {
            out << *(e.jucatori[i]) << "\n";
        }
        return out;
    }
};



int main() {
    
    return 0;
}
