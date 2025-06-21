#include "student.h"
#include <iostream>
#include <cstdio>   

using namespace std;

int main() {
    const int MAX = 100;
    Student students[MAX];
    int count = 0;

    int choice;

    cin.ignore();

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Add student\n";
        cout << "2. Show all students\n";
        cout << "3. Delete student by index\n";
        cout << "4. Update student info\n";
        cout << "5. Save all students to file (C-style)\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            if (count < MAX) {
                students[count++] = createNewStudentFromUserInput();
            }
            else {
                cout << "Student list full!\n";
            }
            break;

        case 2:
            if (count == 0) {
                cout << "No students yet.\n";
            }
            else {
                for (int i = 0; i < count; i++) {
                    cout << "\nIndex " << i << ":\n";
                    printNewStudent(students[i]);
                }
            }
            break;

        case 3: {
            int index;
            cout << "Enter index to delete: ";
            cin >> index;
            cin.ignore();
            deleteStudentByIndex(students, count, index);
            break;
        }

        case 4: {
            if (count == 0) {
                cout << "No students to update.\n";
                break;
            }
            int idx;
            cout << "Enter index of student to update: ";
            cin >> idx;
            cin.ignore();

            if (idx < 0 || idx >= count) {
                cout << "Invalid index!\n";
                break;
            }

            int updateChoice;
            do {
                cout << "\n--- Update Student Menu ---\n";
                cout << "1. Change Name\n";
                cout << "2. Change Surname\n";
                cout << "3. Change Group\n";
                cout << "4. Update Marks\n";
                cout << "0. Back to main menu\n";
                cout << "Your choice: ";
                cin >> updateChoice;
                cin.ignore();

                switch (updateChoice) {
                case 1:
                    updateStudentName(students[idx]);
                    break;
                case 2:
                    updateStudentSurname(students[idx]);
                    break;
                case 3:
                    updateStudentGroup(students[idx]);
                    break;
                case 4:
                    updateStudentMarks(students[idx]);
                    break;
                case 0:
                    cout << "Returning to main menu.\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (updateChoice != 0);
            break;
        }

        case 5: {
            FILE* fileDescriptor = nullptr;
            const char* filePath = "students.txt";

            if (fopen_s(&fileDescriptor, filePath, "w") != 0 || fileDescriptor == nullptr) {
                cout << "Failed to open file for writing!\n";
            }
            else {
                bool result = printStudentsToFile(fileDescriptor, students, count);
                if (result) {
                    cout << "File write status: \033[42mOK\033[0m\n";
                }
                else {
                    cout << "File write status: \033[41mERROR\033[0m\n";
                }
                fclose(fileDescriptor);
            }
            break;
        }

        case 0:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    
    for (int i = 0; i < count; i++) {
        deleteStudent(students[i]);
    }

    return 0;
}
