#pragma once
#include <vector>
#include <string>
#include "models.hpp"

namespace storage {
    std::vector<Student> incarcaElevi(const std::string& numeFisier);
    void salveazaElevi(const std::string& numeFisier, const std::vector<Student>& elevi);

    std::vector<GradeEntry> incarcaNote(const std::string& numeFisier);
    void salveazaNote(const std::string& numeFisier, const std::vector<GradeEntry>& note);
}
