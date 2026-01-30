#include "services.hpp"
#include <algorithm>
#include <stdexcept>

namespace servicii {

int urmatorIdElev(const std::vector<Student>& elevi) {
    int maxId = 0;
    for (const auto& e : elevi) {
        maxId = std::max(maxId, e.id);
    }
    return maxId + 1;
}

Student adaugaElev(BazaDate& db, const std::string& nume, const std::string& clasa) {
    if (nume.empty()) throw std::runtime_error("Numele nu poate fi gol.");
    if (clasa.empty()) throw std::runtime_error("Clasa nu poate fi goala.");

    Student e;
    e.id = urmatorIdElev(db.elevi);
    e.name = nume;
    e.className = clasa;
    db.elevi.push_back(e);
    return e;
}

bool existaElev(const BazaDate& db, int idElev) {
    for (const auto& e : db.elevi) {
        if (e.id == idElev) return true;
    }
    return false;
}

std::optional<Student> gasesteElev(const BazaDate& db, int idElev) {
    for (const auto& e : db.elevi) {
        if (e.id == idElev) return e;
    }
    return std::nullopt;
}

void adaugaNota(BazaDate& db, int idElev, const std::string& materie, int nota, const std::string& data) {
    if (!existaElev(db, idElev)) throw std::runtime_error("Elev inexistent (ID).");
    if (materie.empty()) throw std::runtime_error("Materia nu poate fi goala.");
    if (nota < 1 || nota > 10) throw std::runtime_error("Nota trebuie sa fie intre 1 si 10.");

    GradeEntry n;
    n.studentId = idElev;
    n.subject = materie;
    n.grade = nota;
    n.date = data;
    db.note.push_back(n);
}

std::vector<GradeEntry> notePentruElev(const BazaDate& db, int idElev) {
    std::vector<GradeEntry> rezultat;
    for (const auto& n : db.note) {
        if (n.studentId == idElev) rezultat.push_back(n);
    }
    return rezultat;
}

double medieElev(const BazaDate& db, int idElev) {
    int suma = 0, cnt = 0;
    for (const auto& n : db.note) {
        if (n.studentId == idElev) {
            suma += n.grade;
            cnt++;
        }
    }
    if (cnt == 0) return 0.0;
    return (double)suma / cnt;
}

double medieMaterie(const BazaDate& db, const std::string& materie) {
    int suma = 0, cnt = 0;
    for (const auto& n : db.note) {
        if (n.subject == materie) {
            suma += n.grade;
            cnt++;
        }
    }
    if (cnt == 0) return 0.0;
    return (double)suma / cnt;
}

} 
