# Tema 9 - Aplicatie de gestionare a notelor scolare (C++)

Aplicatie in consola pentru:
- adaugare elev (ID auto)
- adaugare nota
- afisare elevi / note elev
- medie elev / medie materie

Datele se salveaza in:
- students.csv
- grades.csv

## Rulare cu Docker 

```bash
docker build -t tema9-note-scolare .
docker run -it --rm tema9-note-scolare
