#include "student.h"
#include <iostream>


using namespace std;

Student createNewStudentFromUserInput() {
    Student newStudent{};
    char buffer[100];

    cout << "Enter name: ";
    cin.getline(buffer, 100);
    int len = strlen(buffer) + 1;
    newStudent.name = new char[len];
    strcpy_s(newStudent.name, len, buffer);

    cout << "Enter surname: ";
    cin.getline(buffer, 100);
    len = strlen(buffer) + 1;
    newStudent.surname = new char[len];
    strcpy_s(newStudent.surname, len, buffer);

    cout << "Enter group: ";
    cin.getline(buffer, 100);
    len = strlen(buffer) + 1;
    newStudent.group = new char[len];
    strcpy_s(newStudent.group, len, buffer);

    cout << "Enter number of marks: ";
    cin >> newStudent.marksCount;

    newStudent.marks = new int[newStudent.marksCount];
    cout << "Enter marks (separated by space): ";
    for (int i = 0; i < newStudent.marksCount; i++) {
        cin >> newStudent.marks[i];
    }

    cin.ignore();

    return newStudent;
}

void printNewStudent(const Student& student) {
    cout << "Name: " << student.name << "\n";
    cout << "Surname: " << student.surname << "\n";
    cout << "Group: " << student.group << "\n";
    cout << "Marks: ";
    for (int i = 0; i < student.marksCount; i++) {
        cout << student.marks[i] << " ";
    }
    cout << "\n";
}

void deleteStudent(Student& student) {
    delete[] student.name;
    delete[] student.surname;
    delete[] student.group;
    delete[] student.marks;

    student.name = nullptr;
    student.surname = nullptr;
    student.group = nullptr;
    student.marks = nullptr;
    student.marksCount = 0;
}
void updateStudentName(Student& student) {
    char buffer[100];
    cout << "Enter new name: ";
    cin.getline(buffer, 100);


    delete[] student.name;

    int len = strlen(buffer) + 1;
    student.name = new char[len];
    strcpy_s(student.name, len, buffer);

    cout << "Name updated successfully!\n";
}
void updateStudentSurname(Student& student) {
    char buffer[150];
    cout << "Enter new surname: ";
    cin.getline(buffer, 150);

    delete[] student.surname;

    int len = strlen(buffer) + 1;
    student.surname = new char[len];
    strcpy_s(student.surname, len, buffer);

    cout << "Surname updted succesfully!\n";
}
void updateStudentGroup(Student& student) {
    char buffer[100];
    cout << "Enter new group : ";
    cin.getline(buffer, 100);

    delete[] student.group;

    int len = strlen(buffer) + 1;
    student.group = new char[len];
    strcpy_s(student.group, len, buffer);

    cout << "Group updated succesfully\n";
}
void updateStudentMarks(Student& student) {
    int choice;

    do {
        cout << "\n--- Update Marks Menu ---\n";
        cout << "1. Add new mark\n";
        cout << "2. Delete mark by index\n";
        cout << "3. Change mark by index\n";
        cout << "0. Exit marks update\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int newMark;
            cout << "Enter new mark to add: ";
            cin >> newMark;
            cin.ignore();


            int* newMarks = new int[student.marksCount + 1];


            for (int i = 0; i < student.marksCount; i++) {
                newMarks[i] = student.marks[i];
            }


            newMarks[student.marksCount] = newMark;


            delete[] student.marks;


            student.marks = newMarks;
            student.marksCount++;

            cout << "Mark added.\n";
            break;
        }
        case 2: {
            if (student.marksCount == 0) {
                cout << "No marks to delete.\n";
                break;
            }
            int delIndex;
            cout << "Enter index of mark to delete (0 to " << student.marksCount - 1 << "): ";
            cin >> delIndex;
            cin.ignore();

            if (delIndex < 0 || delIndex >= student.marksCount) {
                cout << "Invalid index!\n";
                break;
            }

            if (student.marksCount == 1) {

                delete[] student.marks;
                student.marks = nullptr;
                student.marksCount = 0;
            }
            else {

                int* newMarks = new int[student.marksCount - 1];


                for (int i = 0, j = 0; i < student.marksCount; i++) {
                    if (i != delIndex) {
                        newMarks[j++] = student.marks[i];
                    }
                }


                delete[] student.marks;

                student.marks = newMarks;
                student.marksCount--;
            }

            cout << "Mark deleted.\n";
            break;
        }
        case 3: {
            if (student.marksCount == 0) {
                cout << "No marks to change.\n";
                break;
            }
            int chIndex;
            cout << "Enter index of mark to change (0 to " << student.marksCount - 1 << "): ";
            cin >> chIndex;
            cin.ignore();

            if (chIndex < 0 || chIndex >= student.marksCount) {
                cout << "Invalid index!\n";
                break;
            }

            int newMark;
            cout << "Enter new mark: ";
            cin >> newMark;
            cin.ignore();

            student.marks[chIndex] = newMark;

            cout << "Mark updated.\n";
            break;
        }
        case 0:
            cout << "Exiting marks update.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
bool printStudentsToFile(FILE* descriptor, Student students[], int count) {
    if (descriptor == nullptr) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        fprintf(descriptor, "------ STUDENT %d ------\n", i + 1);
        fprintf(descriptor, "Name: %s\n", students[i].name);
        fprintf(descriptor, "Surname: %s\n", students[i].surname);
        fprintf(descriptor, "Group: %s\n", students[i].group);
        fprintf(descriptor, "Marks: ");
        for (int j = 0; j < students[i].marksCount; j++) {
            fprintf(descriptor, "%d ", students[i].marks[j]);
        }
        fprintf(descriptor, "\n------------------------\n\n");
    }

    return true;
}

void deleteStudentByIndex(Student students[], int& count, int index) {
    if (index < 0 || index >= count) {
        cout << "Invalid index!\n";
        return;
    }

    deleteStudent(students[index]);

    for (int i = index; i < count - 1;i++) {
        students[i] = students[i + 1];
    }

    count--;

    cout << "Student deleted!\n";
}
