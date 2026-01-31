#include <iostream>
#include <string>
#include <limits>

#include "storage.hpp"
#include "services.hpp"

static const std::string FISIER_ELEVI = "students.csv";
static const std::string FISIER_NOTE  = "grades.csv";

static void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int citesteInt(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        int x;
        if (std::cin >> x) {
            curataInput();
            return x;
        }
        curataInput();
        std::cout << "Valoare invalida. Incearca din nou.\n";
    }
}

static std::string citesteLinie(const std::string& mesaj) {
    std::cout << mesaj;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static void afiseazaElevi(const BazaDate& db) {
    if (db.elevi.empty()) {
        std::cout << "Nu exista elevi.\n";
        return;
    }
    std::cout << "Lista elevi:\n";
    for (const auto& e : db.elevi) {
        std::cout << "ID=" << e.id << " | " << e.name << " | Clasa: " << e.className << "\n";
    }
}

static void afiseazaNoteElev(const BazaDate& db) {
    int id = citesteInt("ID elev: ");
    auto elev = servicii::gasesteElev(db, id);
    if (!elev) {
        std::cout << "Elev inexistent.\n";
        return;
    }

    auto note = servicii::notePentruElev(db, id);
    std::cout << "Note pentru " << elev->name << " (ID " << id << "):\n";
    if (note.empty()) {
        std::cout << "(fara note)\n";
        return;
    }
    for (const auto& n : note) {
        std::cout << n.subject << " | " << n.grade;
        if (!n.date.empty()) std::cout << " | " << n.date;
        std::cout << "\n";
    }
}

int main() {
    BazaDate db;
    db.elevi = storage::incarcaElevi(FISIER_ELEVI);
    db.note  = storage::incarcaNote(FISIER_NOTE);

    while (true) {
        std::cout << "\n=== Gestionare note scolare ===\n";
        std::cout << "1. Adauga elev\n";
        std::cout << "2. Afiseaza elevi\n";
        std::cout << "3. Adauga nota\n";
        std::cout << "4. Afiseaza note elev\n";
        std::cout << "5. Medie elev\n";
        std::cout << "6. Medie materie\n";
        std::cout << "0. Iesire\n";

        int opt = citesteInt("Alege: ");

        try {
            if (opt == 0) {
                storage::salveazaElevi(FISIER_ELEVI, db.elevi);
                storage::salveazaNote(FISIER_NOTE, db.note);
                std::cout << "Date salvate. La revedere!\n";
                break;
            } else if (opt == 1) {
                std::string nume = citesteLinie("Nume elev: ");
                std::string clasa = citesteLinie("Clasa (ex: 10A): ");
                auto e = servicii::adaugaElev(db, nume, clasa);
                storage::salveazaElevi(FISIER_ELEVI, db.elevi);
                std::cout << "Elev adaugat cu ID: " << e.id << "\n";
            } else if (opt == 2) {
                afiseazaElevi(db);
            } else if (opt == 3) {
                int id = citesteInt("ID elev: ");
                std::string materie = citesteLinie("Materie: ");
                int nota = citesteInt("Nota (1-10): ");
                std::string data = citesteLinie("Data (optional, ex: 2026-01-30) sau gol: ");

                servicii::adaugaNota(db, id, materie, nota, data);
                storage::salveazaNote(FISIER_NOTE, db.note);
                std::cout << "Nota adaugata.\n";
            } else if (opt == 4) {
                afiseazaNoteElev(db);
            } else if (opt == 5) {
                int id = citesteInt("ID elev: ");
                auto elev = servicii::gasesteElev(db, id);
                if (!elev) {
                    std::cout << "Elev inexistent.\n";
                    continue;
                }
                double m = servicii::medieElev(db, id);
                std::cout << "Medie pentru " << elev->name << " = " << m << "\n";
            } else if (opt == 6) {
                std::string materie = citesteLinie("Materie: ");
                double m = servicii::medieMaterie(db, materie);
                std::cout << "Medie la " << materie << " = " << m << "\n";
            } else {
                std::cout << "Optiune invalida.\n";
            }
        } catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << "\n";
        }
    }

    return 0;
}
