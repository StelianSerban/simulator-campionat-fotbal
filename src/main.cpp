#include "example.h"
using namespace std;

int main() {
    
    Campionat c;
    int optiune;
    bool meciuriGenerate = false;
    srand(time(NULL));

    do
    {
        cout << "\n=== MENIU ===\n";
        cout << "1. Adauga echipa\n";
        cout << "2. Adauga jucator\n";
        cout << "3. Seteaza antrenor\n";
        cout << "4. Afiseaza echipe\n";
        cout << "5. Genereaza meciuri\n";
        cout << "6. Simuleaza toate meciurile\n";
        cout << "7. Afiseaza clasamentul\n";
        cout << "8. Afiseaza meciurile\n";
        cout << "9: Afiseaza golgheteri\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin >> optiune;
        cin.ignore();

        if(optiune == 1)
        {
            string numeEchipa;
            cout << "Nume echipa: ";
            getline(cin, numeEchipa);
            c.adaugaEchipa(make_shared<Echipa>(numeEchipa));
        }

        if(optiune == 2)
        {
            string numeEchipa, numeJucator;
            int varsta, numar;
            cout << "Nume echipa: ";
            getline(cin, numeEchipa);
            cout << "Nume jucator: ";
            getline(cin, numeJucator);
            cout << "Varsta: ";
            cin >> varsta;
            cout << "Numar: ";
            cin >> numar;
            cin.ignore();
            shared_ptr<Jucator> j = make_shared<Jucator>(numeJucator, varsta,"mijlocas", numar);
            try
            {
                for (auto echipa : c.getEchipe())
                {
                    if(echipa->getNume() == numeEchipa)
                    {
                        echipa->adaugaJucator(j);
                        break;
                    }
                }
            } catch(const exception &e)
            {
                cout << "Eroare: " << e.what() << "\n";
            }
        }

        if(optiune == 3)
        {
            // persoana formatie stil aniExperienta

            string numeEchipa, numeAntrenor, formatie, stil;
            int varsta, aniExperienta;
            cout << "Nume echipa: ";
            getline(cin, numeEchipa);
            cout << "Nume antrenor: ";
            getline(cin, numeAntrenor);
            cout << "Varsta: ";
            cin >> varsta;
            cin.ignore();
            cout << "Formatie: ";
            getline(cin, formatie);
            cout << "Stil: ";
            getline(cin, stil);
            cout << "Ani experienta: ";
            cin >> aniExperienta;
            cin.ignore();

            shared_ptr<Antrenor> a = make_shared<Antrenor>(numeAntrenor, varsta, formatie, stil, aniExperienta);

            for(auto echipa : c.getEchipe())
            {
                if(echipa->getNume() == numeEchipa)
                {
                    echipa->setAntrenor(a);
                    break;
                }
            }
        }

        if(optiune == 4)
        {
            for(auto echipa : c.getEchipe())
            {
                echipa->afisare();
            }
        }

        if(optiune == 5)
        {
            c.genereazaMeciuri();
            meciuriGenerate = true;
            cout << "Meciurile au fost generate!\n";
        }

        if(optiune == 6)
        {
            if(meciuriGenerate == false)
            {
                cout << "Mai intai trebuie sa generati meciurile!\n";
                continue;
            }
            int tipSimulare;
            cout << "1 = scoruri random, 2 = introducere manuala: ";
            cin >> tipSimulare;
            if(tipSimulare == 1)
                c.simuleazaToateMeciurile(false);
            else
                c.simuleazaToateMeciurile(true);
        }

        if(optiune == 7)
            c.afiseazaClasament();

        if(optiune == 8)
            c.afiseazaMeciuri();

        if(optiune == 9)
            c.afiseazaGolgheteri();


    }while(optiune != 0);

    return 0;
}