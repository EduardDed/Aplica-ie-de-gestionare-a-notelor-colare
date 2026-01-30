#pragma once
#include <vector>
#include <string>
#include <optional>
#include "models.hpp"

struct BazaDate {
    std::vector<Student> elevi;
    std::vector<GradeEntry> note;
};

namespace servicii {

    int urmatorIdElev(const std::vector<Student>& elevi);

    Student adaugaElev(BazaDate& db, const std::string& nume, const std::string& clasa);

    bool existaElev(const BazaDate& db, int idElev);
    std::optional<Student> gasesteElev(const BazaDate& db, int idElev);

    void adaugaNota(BazaDate& db, int idElev, const std::string& materie, int nota, const std::string& data);

    std::vector<GradeEntry> notePentruElev(const BazaDate& db, int idElev);

    double medieElev(const BazaDate& db, int idElev);
    double medieMaterie(const BazaDate& db, const std::string& materie);
}
