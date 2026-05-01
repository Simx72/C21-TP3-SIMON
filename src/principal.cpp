#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

#include "./stats.h"

using namespace std;

const char* MESSAGE_ERREUR = "Impossible d'ouvrir le fichier tests.txt. Fin du programme";

// L'UNIQUE VARIABLE GLOBALE

size_t nb_repondants; // le nombre réel de répondants: nb_repondants =
                      // lireLesDonnéesDuSondage(...)

// DÉCALRATIONS DES FONCTIONS  -- écrire vos déclarations ici ...

size_t lireLesDonneesDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[]);

// DÉFINITIONS DES FONCTIONS  --  écrire vos définitions ici ...

size_t lireLesDonneesDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[]) {

#ifdef PROJECT_TEST_FILE
    string name = PROJECT_TEST_FILE;
#else
    string name = "src/tests.txt";
#endif

    fstream f(name, ios::in);

    if (f.fail()) // fichier ouvert ?
    {
#ifdef _WIN32
        string erreur = MESSAGE_ERREUR;
        erreur += " Route essayée : ";
        erreur += name;
        MessageBoxA(NULL, erreur.c_str(), "Route incorrecte", MB_OK | MB_ICONSTOP);
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
    bool* r1 = new bool[REPONDANTS_MAX]{};            // pour la  réponse  1
    Protection* pro = new Protection{};               // pour les réponses 2-3-4-5-6
    Infection* inf = new Infection[REPONDANTS_MAX]{}; // pour les réponses 7-8-9-10
    Repondant* rep = new Repondant[REPONDANTS_MAX]{}; // pour les réponses
                                                      // ville, age, scolarité

    // A - charger les données du sondage
    nb_repondants = lireLesDonneesDuSondage(r1, pro, inf, rep);

    // B - appeler vos fonctions statistiques et afficher ici leurs résultats
    // ...

    int res01 = stat_01(r1);
    int res02 = stat_02(pro->r3);
    double res03 = stat_03(pro->r2, rep);
    double res04 = stat_04(rep, pro->r5, pro->r6);
    double res05 = stat_05(rep, pro->r2);
    double res06 = stat_06(inf);
    string res07 = stat_07(inf);
    size_t res08 = stat_08(inf, pro->r4);
    double res09 = stat_09(rep, inf, pro->r2);
    string res10 = stat_10(rep, inf);

    // Output

    cout << "TP3 - SIMON - 2026\n\n";
    cout << "Réponses: \n\n";

    cout << "1. Combien de personnes toussent souvent ?\n";
    cout << "\tR: " << res01 << "\n\n";

    cout << "2. Combien de personnes veulent un masque dans leur auto ?\n";
    cout << "\tR: " << res02 << "\n\n";

    cout << "3. Combien de masques, en moyenne, ont les gens qui sont dans la\n"
            "   trentaine ?\n";
    cout << "\tR: " << fixed << setprecision(1) << res03 << "\n\n";

    cout << "4. Quel est l'âge moyen des gens qui se serviraient d’un masque\n"
            "   pour décorer ou pour dormir ?\n";
    cout << "\tR: " << fixed << setprecision(1) << res04 << "\n\n";

    cout << "5. Quel pourcentage des gens de Vaudreuil possèdent plus d'un\n"
            "   masque ?\n";
    cout << "\tR: " << fixed << setprecision(1) << (res05 * 100) << " %"
         << "\n\n";

    cout << "6. Quel pourcentage de la population utilise du désinfectant ?\n";
    cout << "\tR: " << fixed << setprecision(1) << (res06 * 100) << " %"
         << "\n\n";

    cout << "7. Quel est le type de désinfectant le plus répandu ?\n";
    cout << "\tR: " << res07 << "\n\n";

    cout << "8. Combien de gens non testés et n’utilisant pas de désinfectant\n"
            "   ont déjà emprunté un masque ?\n";
    cout << "\tR: " << res08 << "\n\n";

    cout << "9. Combien d'années de scolarité, en moyenne, ont les gens\n"
            "   infectés de Montréal sans masque ou sans désinfectant ?\n";
    cout << "\tR: " << fixed << setprecision(1) << res09 << "\n\n";

    cout << "10. Quelle est la ville ayant fait subir le plus grand nombre de\n"
            "   tests ?\n";
    cout << "\tR: " << res10 << "\n\n";

#ifdef _WIN32
    _getch();
#endif

    // C - Recycler les allocations dynamiques
    delete[] r1;
    delete pro;
    delete[] inf;
    delete[] rep;
}
