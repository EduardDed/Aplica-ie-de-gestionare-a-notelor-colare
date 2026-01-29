#pragma once
#include <string>

struct Student {
    int id;
    std::string name;
    std::string className;
};

struct GradeEntry {
    int studentId;
    std::string subject;
    int grade;
    std::string date;
};
