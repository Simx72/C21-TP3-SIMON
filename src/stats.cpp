#include "stats.h"
#include "liste.h"
#include <cstddef>

// 1. Combien de personnes toussent souvent ?
std::size_t stat_01(bool *r1, std::size_t nb_repondants) {
    std::size_t count = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (r1[i])
            count++;
    return count;
}

// 2. Combien de personnes veulent un masque dans leur auto ?
std::size_t stat_02(char *r3, std::size_t nb_repondants) {
    std::size_t count = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (r3[i] == 'O')
            count++;
    return count;
}

// 3. Combien de masques, en moyenne, ont les gens qui sont dans la trentaine ?
double stat_03(int *r2, Repondant *rep, std::size_t nb_repondants) {
    std::size_t nb_de_personnes = 0;
    std::size_t nb_de_masques = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (rep[i].age >= 30 && rep[i].age < 40) {
            nb_de_masques += r2[i];
            nb_de_personnes++;
        }
    if (nb_de_personnes == 0)
        return 0;
    else
        return (double)nb_de_masques / (double)nb_de_personnes;
}

// 4. Quel est l'âge moyen des gens qui se serviraient d’un masque pour décorer
// ou pour dormir ?
double stat_04(Repondant *rep, char *r5, char *r6, std::size_t nb_repondants) {
    std::size_t nb_de_personnes = 0;
    std::size_t somme_des_ages = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (r5[i] || r6[i]) {
            somme_des_ages += rep[i].age;
            nb_de_personnes++;
        }
    if (nb_de_personnes == 0)
        return 0;
    else
        return (double)somme_des_ages / (double)nb_de_personnes;
}

// 5. Quel pourcentage des gens de Vaudreuil possèdent plus d'un masque ?
double stat_05(Repondant *rep, int *r2, std::size_t nb_repondants) {
    std::size_t total = 0, fraction = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (rep[i].ville == "Vaudreuil") {
            total++;
            if (r2[i] > 1)
                fraction++;
        }
    if (total == 0)
        return 0;
    else
        return (double)fraction / (double)total;
}

// 6. Quel pourcentage de la population utilise du désinfectant ?
double stat_06(Infection *inf, std::size_t nb_repondants) {
    std::size_t fraction = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (inf[i].r8 != 1)
            fraction++;
    if (nb_repondants == 0)
        return 0;
    else
        return (double)fraction / (double)nb_repondants;
}

// 7. Quel est le type de désinfectant le plus répandu ?
std::string stat_07(Infection *inf, std::size_t nb_repondants) {
    // Get quantity for each one
    int type_quantity[4]{};
    for (size_t i = 0; i < nb_repondants; i++)
        if (inf[i].r8 >= 2 && inf[i].r8 <= 5)
            type_quantity[inf[i].r8 - 2]++;
    // Get the type with the max
    std::size_t max = 0;
    for (std::size_t i = 0; i < 4; i++)
        if (type_quantity[i] > type_quantity[max])
            max = i;
    // Return
    switch (max) {
        // clang-format off
        case 0: return "Savon à vaisselle";
        case 1: return "Purell";
        case 2: return "Eau de javel";
        case 3: return "Alcool à friction";
        // clang-format on
    };
    return "None";
}

// 8. Combien de gens non testés et n’utilisant pas de désinfectant ont déjà
// emprunté un masque ?
//    _Ne pas considérer réponse de la question 7_
std::size_t stat_08(Infection *inf, char *r4, std::size_t nb_repondants) {
    std::size_t quantity = 0;
    for (size_t i = 0; i < nb_repondants; i++)
        if (inf[i].r10 == 0)
            if (inf[i].r8 == 1)
                if (r4[i] == 'O')
                    quantity++;
    return quantity;
}

// 9. Combien d'années de scolarité, en moyenne, ont les gens infectés de
// Montréal sans masque ou sans désinfectant ?
//    _Ceux qui sont certains d’être infectés (Oui à question 9) et ne pas
//    considérer la réponse à la question 7._
double stat_09(Repondant *rep, Infection *inf, int *r2,
               std::size_t nb_repondants) {
    std::size_t total = 0, somme = 0;
    for (std::size_t i = 0; i < nb_repondants; i++) {
        const bool infecte = inf[i].r9 == 1, ville = rep[i].ville == "Montreal",
                   pas_masque = r2[i] == 0, pas_desinf = inf[i].r8 == 1;

        if ((infecte && ville) && (pas_masque || pas_desinf)) {
            total++;
            somme += rep[i].scolarite;
        }
    }
    if (total == 0)
        return 0;
    else
        return (double)somme / (double)total;
}

// 10. Quelle est la ville ayant fait subir le plus grand nombre de tests ?
//     (Obligatoire : pour cette question, vous devez utiliser une liste chainée
//     des villes du sondage)
std::string stat_10(Repondant *rep, Infection *inf, std::size_t nb_repondants) {
    // Get villes
    auto ll = linked_list::new_linked_list();
    for (std::size_t i = 0; i < nb_repondants; i++) {
        auto node = linked_list::get_node_by_ville(ll, rep[i].ville);
        if (node == nullptr)
            linked_list::push_front(ll, {rep[i].ville, inf[i].r10});
        else
            node->value.quantity += inf[i].r10;
    }
    // Get max
    linked_list::Node *max_node = ll->head;
    linked_list::Node *current_node = ll->head;
    if (max_node == nullptr) {
        linked_list::destroy(ll);
        return "Error";
    }
    while (current_node != nullptr) {
        if (current_node->value.quantity > max_node->value.quantity)
            max_node = current_node;
        current_node = current_node->next;
    }
    auto result = max_node->value.ville;
    linked_list::destroy(ll);
    return result;
}
