#pragma once

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include "example.h"

using namespace std;

class Persoana 
{

protected:
    std::string nume;
    int varsta;

public:
    Persoana() : nume(""), varsta(0) {}
    Persoana(const std::string &nume, int varsta) : nume(nume), varsta(varsta) {}
    Persoana(const Persoana &other) : nume(other.nume), varsta(other.varsta) {}

    Persoana &operator=(const Persoana &other)
    {
        if(this != &other)
        {
            nume = other.nume;
            varsta = other.varsta;
        }

        return *this;
    }

    virtual ~Persoana() {}

    std::string getNume()
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
    std::string descriere;
public:
    Statistici() : valoare(), descriere("") {}
    Statistici(const T &valoare, const std::string &descriere) : valoare(valoare), descriere(descriere) {}

    T getValoare() 
    {
        return valoare;
    }
    std::string getDescriere()
    {
        return descriere;
    }

    void setValoare(T v)
    {
        valoare = v;
    }
    void setDescriere(const std::string &d)
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
        std::cout << "Descriere: "; in >> ws; std::getline(in, s.descriere);
        std::cout << "Valoare: "; in >> s.valoare;
        return in;
    }
};

class Jucator : public Persoana
{

private:
    std::string pozitie;
    int numar;
    Statistici<int> goluri;
    static int totalJucatori;
    
public:
    Jucator() : Persoana(), pozitie(""), numar(0), goluri(0, "goluri") {}
    Jucator(const std::string &nume, int varsta, const std::string &pozitie, int numar) : Persoana(nume, varsta), pozitie(pozitie), numar(numar), goluri(0, "goluri") {}
    Jucator(Jucator &other) : Persoana(other), pozitie(other.pozitie), numar(other.numar), goluri(other.goluri) {}

    ~Jucator() {}

    static int getTotalJucatori()
    {
        return totalJucatori;
    }

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
        return nume == other.nume && numar == other.numar;
    }

    void adaugaGoluri(int g)
    {
        goluri.setValoare(goluri.getValoare() + g);
    }

    int getGoluri()
    {
        return goluri.getValoare();
    }

    std::string getPozitie()
    {
        return pozitie;
    }
    int getNumar()
    {
        return numar;
    }
    
    void afisare() const override 
    {
        std::cout << "Jucator: " << nume << ", varsta: " << varsta << ", pozitie: " << pozitie << ", numar: " << numar << "\n";
    }
    

    friend ostream &operator<<(ostream &out, Jucator &j)
    {
        out << j.nume << " " << j.pozitie << " " << j.numar << " " << j.varsta;
        return out;
    }
    friend istream &operator>>(istream &in, Jucator &j)
    {
        std::cout << "Nume: "; in >> ws; std::getline(in, j.nume);
        std::cout << "Varsta: "; in >> j.varsta;
        std::cout << "Pozitie: "; in >> ws; std::getline(in, j.pozitie);
        std::cout << "Numar: "; in >> j.numar;
        return in;
    }
};

class Antrenor : public Persoana 
{

private:
    std::string formatie;
    std::string stil;
    int aniExperienta;
public:
    Antrenor() : Persoana(), formatie(""), stil(""), aniExperienta() {}
    Antrenor(const std::string &nume, int varsta, const std::string &formatie, const std::string &stil, int aniExperienta) : Persoana(nume, varsta), formatie(formatie), stil(stil), aniExperienta(aniExperienta) {}
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

    void afisare() const override 
    {
        std::cout << "Antrenor: " << nume << ", varsta: " << varsta << ", formatie: " << formatie << ", stil: " << stil << "\n";
    }
    

    friend ostream &operator<<(ostream &out, const Antrenor &a)
    {
        out << a.nume << " " << a.varsta << " " << a.formatie << " " << a.stil << " " << a.aniExperienta;
        return out;
    }
    friend istream &operator>>(istream &in, Antrenor &a)
    {
        std::cout << "Nume: "; in >> ws; std::getline(in, a.nume);
        std::cout << "Varsta: "; in >> a.varsta;
        std::cout << "Formatie: "; in >> ws; std::getline(in, a.formatie);
        std::cout << "Stil: "; in >> ws; std::getline(in, a.stil);
        std::cout << "Ani experienta: "; in >> a.aniExperienta;
        return in;
    }
};

class Echipa
{
private:
    std::string nume;
    std::vector<std::shared_ptr<Jucator>> jucatori;
    std::shared_ptr<Antrenor> antrenor;

public:
    Echipa() : nume("Nume necunoscut.") {}
    Echipa(std::string nume) : nume(nume) {}

    void adaugaJucator(std::shared_ptr<Jucator> j)
    {
        if(j->getNume().empty())
            throw invalid_argument("Numele jucatorului nu poate fi gol!\n");
        
        for(int i = 0; i < jucatori.size(); i++)
        {
            if(*jucatori[i] == *j)
            {
                std::cout << "Jucatorul " << j->getNume() << "exista deja.\n";
                return;
            }
        }
        jucatori.push_back(j);
    }

    void setAntrenor(std::shared_ptr<Antrenor> a)
    {
        antrenor = a;
    }

    std::string getNume() const
    {
        return nume;
    }

    std::vector<std::shared_ptr<Jucator>> getJucatori() const
    {
        return jucatori;
    }

    std::shared_ptr<Antrenor> getAntrenor() const
    {
        return antrenor;
    }

    void afisare()
    {
        std::cout << "=== Echipa: " << nume << " ===\n\n";

        if(antrenor != nullptr)
        {
            std::cout << "\n";
            antrenor->afisare();
        }
        else
        {
            std::cout << "Fara antrenor\n\n";
        }
        if(jucatori.size() == 0)
        {
            std::cout << "Fara jucatori\n\n";
        }
        else
        {
            std::cout << "\n";
            for(int i = 0; i < jucatori.size(); i++)
            {
                jucatori[i]->afisare();
            }
        }
        std::cout << "====================\n";
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

class Meci
{
private:
    std::shared_ptr<Echipa> echipa1;
    std::shared_ptr<Echipa> echipa2;
    std::map<std::shared_ptr<Jucator>, int> marcatori;
    int goluri1;
    int goluri2;
    bool scorSetat;
public:
    Meci(std::shared_ptr<Echipa> e1, std::shared_ptr<Echipa> e2) : echipa1(e1), echipa2(e2), goluri1(0), goluri2(0), scorSetat(false) {}
    
    void simuleazaRandom()
    {
        goluri1 = std::rand() % 6;
        goluri2 = std::rand() % 6;

        std::vector<std::shared_ptr<Jucator>> j1 = echipa1->getJucatori();
        std::vector<std::shared_ptr<Jucator>> j2 = echipa2->getJucatori();

        for(int i = 0; i < goluri1; i++)
        {
            if(j1.size() > 0)
            {
                int index = std::rand() % j1.size();
                marcatori[j1[index]]++;
            }
        }

        for(int i = 0; i < goluri2; i++)
        {
            if(j2.size() > 0)
            {
                int index = std::rand() % j2.size();
                marcatori[j2[index]]++;
            }
        }

        scorSetat = true;
    }

    void introduManual()
    {
        std::cout << "Goluri " << echipa1->getNume() << ": ";
        std::cin >> goluri1;
        std::cout << "Goluri " << echipa2->getNume() << ": ";
        std::cin >> goluri2;
        cin.ignore();
        std::cout << "Introduceți numele marcatorilor pentru " << echipa1->getNume() << ":\n";
        for (int i = 0; i < goluri1; i++) 
        {
            std::string nume;
            std::cout << "Gol " << i + 1 << ": ";
            std::getline(cin, nume);

            for (int j = 0; j < echipa1->getJucatori().size(); j++) 
            {
                std::shared_ptr<Jucator> juc = echipa1->getJucatori()[j];
                if (juc->getNume() == nume) 
                {
                    marcatori[juc]++;
                    break;
                }
            }
        }

        std::cout << "Introduceți numele marcatorilor pentru " << echipa2->getNume() << ":\n";
        for (int i = 0; i < goluri2; i++) 
        {
            std::string nume;
            std::cout << "Gol " << i + 1 << ": ";
            std::getline(cin, nume);

            for (int j = 0; j < echipa2->getJucatori().size(); j++) 
            {
                std::shared_ptr<Jucator> juc = echipa2->getJucatori()[j];
                if (juc->getNume() == nume) 
                {
                    marcatori[juc]++;
                    break;
                }
            }
        }
        scorSetat = true;
    }

    void afisare()
    {
        std::cout << "=== Meci ===\n";
        std::cout << echipa1->getNume() << " " << goluri1 << " - " << goluri2 << " " << echipa2->getNume() << "\n";
        std::cout << "=== Meci ===\n\n";
    }

    std::map<std::shared_ptr<Jucator>, int> getMarcatori()
    {
        return marcatori;
    }

    int getGoluri1()
    {
        return goluri1;
    }
    
    int getGoluri2()
    {
        return goluri2;
    }

    std::shared_ptr<Echipa> getEchipa1()
    {
        return echipa1;
    }

    std::shared_ptr<Echipa> getEchipa2()
    {
        return echipa2;
    }

    bool Jucat()
    {
        return scorSetat;
    }
};

class Campionat {
private:
    struct StatisticiEchipa 
    {
        int puncte = 0;
        int goluriMarcate = 0;
        int goluriPrimite = 0;

        int golaveraj() const 
        {
            return goluriMarcate - goluriPrimite;
        }
    };
    
    std::vector<std::shared_ptr<Echipa>> echipe;
    std::vector<Meci> meciuri;
    std::map<std::string, StatisticiEchipa> clasament;
    
public:

    Campionat()
    {
        echipe.clear();
        meciuri.clear();
        clasament.clear();
    }

    void adaugaEchipa(std::shared_ptr<Echipa> e) 
    {
        echipe.push_back(e);
        clasament[e->getNume()] = StatisticiEchipa();
    }
    
    std::vector<std::shared_ptr<Echipa>> getEchipe()
    {
        return echipe;
    }

    void genereazaMeciuri() 
    {
        for (int i = 0; i < echipe.size(); i++) 
        {
            for (int j = i + 1; j < echipe.size(); j++) 
            {
                meciuri.push_back(Meci(echipe[i], echipe[j]));
            }
        }
    }
    
    void simuleazaToateMeciurile(bool manual = false) 
    {
        for (int i = 0; i < meciuri.size(); i++) 
        {
            std::cout << "\nMeci " << i + 1 << ":\n";
    
            if (manual)
                meciuri[i].introduManual();
            else
                meciuri[i].simuleazaRandom();

            meciuri[i].afisare();

            std::map<std::shared_ptr<Jucator>, int> goluriMeci = meciuri[i].getMarcatori();
            for(auto it = goluriMeci.begin(); it != goluriMeci.end(); ++it)
            {
                it->first->adaugaGoluri(it->second);
            }
    
            int g1 = meciuri[i].getGoluri1();
            int g2 = meciuri[i].getGoluri2();

            std::string e1 = meciuri[i].getEchipa1()->getNume();
            std::string e2 = meciuri[i].getEchipa2()->getNume();

            clasament[e1].goluriMarcate += g1;
            clasament[e1].goluriPrimite += g2;

            clasament[e2].goluriMarcate += g2;
            clasament[e2].goluriPrimite += g1;
    
            if (g1 > g2)
                clasament[e1].puncte += 3;
            else 
                if (g2 > g1)
                    clasament[e2].puncte += 3;
                else 
                {
                    clasament[e1].puncte += 1;
                    clasament[e2].puncte += 1;
                }
        }
    }
    
    void afiseazaClasament() 
    {
        std::vector<pair<std::string, StatisticiEchipa>> clasamentVector;
        for (const auto &entry : clasament)
        {
            clasamentVector.push_back(entry);
        }
    
        for (int i = 0; i < clasamentVector.size(); i++) 
        {
            for (int j = i + 1; j < clasamentVector.size(); j++) 
            {
                bool swap = false;
    
                if (clasamentVector[j].second.puncte > clasamentVector[i].second.puncte)
                    swap = true;
                else 
                    if (clasamentVector[j].second.puncte == clasamentVector[i].second.puncte) 
                    {
                        if (clasamentVector[j].second.golaveraj() > clasamentVector[i].second.golaveraj())
                            swap = true;
                    }
    
                if (swap) 
                {
                    pair<string, StatisticiEchipa> temp = clasamentVector[i];
                    clasamentVector[i] = clasamentVector[j];
                    clasamentVector[j] = temp;
                }
            }
        }
    
        std::cout << "\n=== CLASAMENT ===\n";
        for (int i = 0; i < clasamentVector.size(); i++) 
        {
            std::string nume = clasamentVector[i].first;
            StatisticiEchipa s = clasamentVector[i].second;
    
            std::cout << i + 1 << ". " << nume << " - " << s.puncte << " pct ("
                << s.goluriMarcate << "-" << s.goluriPrimite
                << ", golaveraj: " << s.golaveraj() << ")\n";
        }
    }
    
    void afiseazaMeciuri() 
    {
        std::cout << "\n=== TOATE MECIURILE ===\n";
        for (int i = 0; i < meciuri.size(); i++) {
            meciuri[i].afisare();
        }
    }

    void afiseazaGolgheteri() 
    {
        std::vector<std::shared_ptr<Jucator>> toti;
    
        for (int i = 0; i < echipe.size(); i++) 
        {
            std::vector<std::shared_ptr<Jucator>> j = echipe[i]->getJucatori();
            for (int k = 0; k < j.size(); k++) 
            {
                toti.push_back(j[k]);
            }
        }
    
        for (int i = 0; i < toti.size(); i++) 
        {
            for (int j = i + 1; j < toti.size(); j++) 
            {
                if (toti[j]->getGoluri() > toti[i]->getGoluri()) 
                {
                    std::shared_ptr<Jucator> aux = toti[i];
                    toti[i] = toti[j];
                    toti[j] = aux;
                }
            }
        }
    
        std::cout << "\n=== CLASAMENT GOLGHETERI ===\n";
        for (int i = 0; i < toti.size(); i++) 
        {
            if (toti[i]->getGoluri() > 0)
                std::cout << toti[i]->getNume() << ": " << toti[i]->getGoluri() << " goluri\n";
        }
    }
    
};