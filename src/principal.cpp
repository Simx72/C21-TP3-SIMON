#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "./stats.h"

using namespace std;

const char *MESSAGE_ERREUR = "Impossible d'ouvrir le fichier, Fin du programme";

// LA CONSTANTE DU PROGRAMME
// LES STRUCTURES DE DONNÉES IMPOSÉES

// dans stats.h

// L'UNIQUE VARIABLE GLOBALE

size_t nb_repondants; // le nombre réel de répondants: nb_repondants =
                      // lireLesDonnéesDuSondage(...)

// DÉCALRATIONS DES FONCTIONS  -- écrire vos déclarations ici ...

size_t lireLesDonneesDuSondage(bool r1[], Protection *pro, Infection inf[],
                               Repondant rep[]);

// DÉFINITIONS DES FONCTIONS  --  écrire vos définitions ici ...

size_t lireLesDonneesDuSondage(bool r1[], Protection *pro, Infection inf[],
                               Repondant rep[]) {

#ifdef _WIN32
    string name = "../../../src/tests.txt";
#else
    string name = "./src/tests.txt"; // exemple avec un path
#endif

    fstream f(name, ios::in);

    if (f.fail()) // fichier ouvert ?
    {
#ifdef _WIN32
        MessageBoxA(NULL, MESSAGE_ERREUR, "Erreur", MB_OK | MB_ICONSTOP);
#else
        cerr << MESSAGE_ERREUR << endl;
#endif
        exit(EXIT_FAILURE); // fin abrupte
    }

    char c;
    size_t r;
    // clang-format off
    for (r = 0; r < REPONDANTS_MAX; ++r) // lire les réponses de chaque répondant
    {
        f >> c;	if (c == 'O') r1[r] = true; else r1[r] = false;						// r1
		f >> pro->r2[r] >> pro->r3[r] >> pro->r4[r] >> pro->r5[r] >> pro->r6[r];	// r2 à r6
		f >> c; if (c == 'O') inf[r].r7 = true; else inf[r].r7 = false;				// r7
		f >> inf[r].r8 >> inf[r].r9 >> inf[r].r10;									// r8 à r10
		f >> rep[r].ville >> rep[r].age >> rep[r].scolarite;						// ville, age, scolarité
		if (f.fail()) { f.clear(); break; }
    }
    // clang-format on
    f.close();
    return r; // r = le nombre de répondants lus
}

int main() {

#ifdef _WIN32
    // Activer UTF-8 pour l'entrée/sortie console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Pour recevoir les données du sondage
    bool *r1 = new bool[REPONDANTS_MAX]{}; // pour la  réponse  1
    Protection *pro = new Protection{};    // pour les réponses 2-3-4-5-6
    Infection *inf =
        new Infection[REPONDANTS_MAX]{}; // pour les réponses 7-8-9-10
    Repondant *rep = new Repondant[REPONDANTS_MAX]{}; // pour les réponses
                                                      // ville, age, scolarité

    // A - charger les données du sondage
    nb_repondants = lireLesDonneesDuSondage(r1, pro, inf, rep);

    // B - appeler vos fonctions statistiques et afficher ici leurs résultats
    // ...

    int res01 = stat_01(r1, nb_repondants);
    int res02 = stat_02(pro->r3, nb_repondants);
    double res03 = stat_03(pro->r2, rep, nb_repondants);
    double res04 = stat_04(rep, pro->r5, pro->r6, nb_repondants);
    double res05 = stat_05(rep, pro->r2, nb_repondants);
    double res06 = stat_06(inf, nb_repondants);
    string res07 = stat_07(inf, nb_repondants);
    size_t res08 = stat_08(inf, pro->r4, nb_repondants);
    double res09 = stat_09(rep, inf, pro->r4, nb_repondants);
    string res10 = stat_10(rep, inf, nb_repondants);

    // Output

    cout << "Réponses: \n\n";
    cout << "Stat 01: " << res01 << endl;
    cout << "Stat 02: " << res02 << endl;
    cout << "Stat 03: " << res03 << endl;
    cout << "Stat 04: " << res04 << endl;
    cout << "Stat 05: " << res05 << endl;
    cout << "Stat 06: " << res06 << endl;
    cout << "Stat 07: " << res07 << endl;
    cout << "Stat 08: " << res08 << endl;
    cout << "Stat 09: " << res09 << endl;
    cout << "Stat 10: " << res10 << endl;

    // cin.get();

    // C - Recycler les allocations dynamiques
    delete[] r1;
    delete pro;
    delete[] inf;
    delete[] rep;
}
