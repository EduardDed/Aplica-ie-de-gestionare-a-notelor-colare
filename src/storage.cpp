#include "storage.hpp"
#include <fstream>
#include <sstream>

static std::vector<std::string> split(const std::string& linie) {
    std::vector<std::string> rezultat;
    std::stringstream ss(linie);
    std::string camp;
    while (getline(ss, camp, ',')) {
        rezultat.push_back(camp);
    }
    return rezultat;
}

namespace storage {

std::vector<Student> incarcaElevi(const std::string& numeFisier) {
    std::vector<Student> elevi;
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) return elevi;

    std::string linie;
    while (getline(fisier, linie)) {
        auto campuri = split(linie);
        if (campuri.size() < 3) continue;

        Student s;
        s.id = std::stoi(campuri[0]);
        s.name = campuri[1];
        s.className = campuri[2];
        elevi.push_back(s);
    }
    return elevi;
}

void salveazaElevi(const std::string& numeFisier, const std::vector<Student>& elevi) {
    std::ofstream fisier(numeFisier);
    for (const auto& s : elevi) {
        fisier << s.id << "," << s.name << "," << s.className << "\n";
    }
}

std::vector<GradeEntry> incarcaNote(const std::string& numeFisier) {
    std::vector<GradeEntry> note;
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) return note;

    std::string linie;
    while (getline(fisier, linie)) {
        auto campuri = split(linie);
        if (campuri.size() < 4) continue;

        GradeEntry g;
        g.studentId = std::stoi(campuri[0]);
        g.subject = campuri[1];
        g.grade = std::stoi(campuri[2]);
        g.date = campuri[3];
        note.push_back(g);
    }
    return note;
}

void salveazaNote(const std::string& numeFisier, const std::vector<GradeEntry>& note) {
    std::ofstream fisier(numeFisier);
    for (const auto& g : note) {
        fisier << g.studentId << "," << g.subject << "," << g.grade << "," << g.date << "\n";
    }
}

}
