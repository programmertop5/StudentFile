#pragma once
#include <cstdio>  
struct Student {
    char* name;
    char* surname;
    char* group;
    int* marks;
    int marksCount;
};

Student createNewStudentFromUserInput();
void printNewStudent(const Student& student);
void deleteStudent(Student& student);
void deleteStudentByIndex(Student students[], int& count, int index);

void updateStudentName(Student& student);
void updateStudentSurname(Student& student);
void updateStudentGroup(Student& student);
void updateStudentMarks(Student& student);
bool printStudentsToFile(FILE* descriptor, Student students[], int count);

