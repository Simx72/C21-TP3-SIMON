#ifndef STATS_H
#define STATS_H
#include <cstddef>
#include <string>

const size_t REPONDANTS_MAX = 500; // nombre maximun de répondants du sondage

struct Protection {
    int r2[REPONDANTS_MAX];
    char r3[REPONDANTS_MAX];
    char r4[REPONDANTS_MAX];
    char r5[REPONDANTS_MAX];
    char r6[REPONDANTS_MAX];
};

struct Infection {
    bool r7;
    int r8, r9, r10;
};

struct Repondant {
    std::string ville;
    int age;
    int scolarite;
};

std::size_t stat_01(bool* r1, std::size_t nb_repondants);
std::size_t stat_02(char* r3, std::size_t nb_repondants);
double stat_03(int* r2, Repondant* rep, std::size_t nb_repondants);
double stat_04(Repondant* rep, char* r5, char* r6, std::size_t nb_repondants);
double stat_05(Repondant* rep, int* r2, std::size_t nb_repondants);
double stat_06(Infection* inf, std::size_t nb_repondants);
std::string stat_07(Infection* inf, std::size_t nb_repondants);
std::size_t stat_08(Infection* inf, char* r4, std::size_t nb_repondants);
double stat_09(Repondant* rep, Infection* inf, int* r2, std::size_t nb_repondants);
std::string stat_10(Repondant* rep, Infection* inf, std::size_t nb_repondants);

#endif
