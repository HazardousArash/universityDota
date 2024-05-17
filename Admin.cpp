#include "Student.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <limits>
Admin::Admin(std::string fn, std::string ln, std::string un, std::string pw, int status)
    : User(fn, ln, un, pw, status) {}

bool Admin::isUniqueUsernamestudent(const std::vector<Student>& students,const std::string& username) {
    for (const auto& user : students) {
        if (user.getUsername() == username) {
            return false;
        }
    }
    return true;
}
bool Admin::isUniqueUsernameteacher(const std::vector<Teacher>& teachers, const std::string& username) {
    for (const auto& user : teachers) {
        if (user.getUsername() == username) {
            return false;
        }
    }
    return true;
    }
  
    
   

void Admin::createStudent(std::vector<Student>& students) {
    std::string fn, ln, un, pw;
    std::cout << "Enter new student first name: ";
    std::cin >> fn;
    std::cout << "Enter new student last name: ";
    std::cin >> ln;

    do {
        std::cout << "Enter new student username (at least 6 characters and unique): ";
        std::cin >> un;
    } while (un.length() < 6 || !isUniqueUsernamestudent(students, un));

    do {
        std::cout << "Enter new student password (at least 8 characters): ";
        std::cin >> pw;
    } while (pw.length() < 8);

    Student newStudent(fn, ln, un, pw);
    students.push_back(newStudent);
    std::ofstream file;
    file.open("studentsinfo.txt", std::ios_base::app);
    file << newStudent.getFirstname() << " " << newStudent.getLastname() << " " << newStudent.getUsername() << " " << newStudent.getPassword() << " " << newStudent.getStatus() << "\n";
    file.close();
}

void Admin::createTeacher(std::vector<Teacher>& teachers) {
    std::string fn, ln, un, pw;
    std::cout << "Enter new teacher first name: ";
    std::cin >> fn;
    std::cout << "Enter new teacher last name: ";
    std::cin >> ln;

    do {
        std::cout << "Enter new teacher username (at least 6 characters and unique): ";
        std::cin >> un;
    } while (un.length() < 6 || !isUniqueUsernameteacher(teachers, un));

    do {
        std::cout << "Enter new teacher password (at least 8 characters): ";
        std::cin >> pw;
    } while (pw.length() < 8);

    Teacher newTeacher(fn, ln, un, pw);
    teachers.push_back(newTeacher);
    std::ofstream file;
    file.open("teachersinfo.txt", std::ios_base::app);
    file << newTeacher.getFirstname() << " " << newTeacher.getLastname() << " " << newTeacher.getUsername() << " " << newTeacher.getPassword() << " " << newTeacher.getStatus() << "\n";
    file.close();
}
void Admin::removeUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
    int userType;

    std::cout << "Enter 1 for student, 2 for teacher: ";
    std::cin >> userType;
    if (!std::cin.good() || (userType != 1 && userType != 2)) {
        std::cout << "Invalid input. Please enter an integer (1 or 2).\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (userType == 1) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getStatus() == 1) {
                std::cout << i + 1 << " " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
            }
        }
        int userIndex;
        std::cout << "Enter the number of the student to remove: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > students.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        students[userIndex].setStatus(0);
        // Rewrite studentsinfo.txt here
        std::ofstream file;
        file.open("studentsinfo.txt", std::ios_base::trunc);
        for (const auto& student : students) {
            file << student.getFirstname() << " " << student.getLastname() << " " << student.getUsername() << " " << student.getPassword() << " " << student.getStatus() << "\n";
        }
        file.close();
    }
    else if (userType == 2) {
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].getStatus() == 1) {
                std::cout << i + 1 << ") " << teachers[i].getFirstname() << " " << teachers[i].getLastname() << "\n";
            }
        }
        int userIndex;
        std::cout << "Enter the number of the teacher to remove: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > teachers.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        teachers[userIndex].setStatus(0);
        // Rewrite teachersinfo.txt here
        std::ofstream file;
        file.open("teachersinfo.txt", std::ios_base::trunc);
        for (const auto& teacher : teachers) {
            file << teacher.getFirstname() << " " << teacher.getLastname() << " " << teacher.getUsername() << " " << teacher.getPassword() << " " << teacher.getStatus() << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Invalid option\n";
    }
}

void Admin::restoreUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
    int userType;

    std::cout << "Enter 1 for student, 2 for teacher: ";
    std::cin >> userType;
    if (!std::cin.good() || (userType != 1 && userType != 2)) {
        std::cout << "Invalid input. Please enter an integer (1 or 2).\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (userType == 1) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getStatus() == 0) {
                std::cout << i + 1 << ") " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
            }
        }
        int userIndex;
        std::cout << "Enter the number of the student to restore: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > students.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        students[userIndex].setStatus(1);
        // Rewrite studentsinfo.txt here
        std::ofstream file;
        file.open("studentsinfo.txt", std::ios_base::trunc);
        for (const auto& student : students) {
            file << student.getFirstname() << " " << student.getLastname() << " " << student.getUsername() << " " << student.getPassword() << " " << student.getStatus() << "\n";
        }
        file.close();
    }
    else if (userType == 2) {
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].getStatus() == 0) {
                std::cout << i + 1 << " " << teachers[i].getFirstname() << " " << teachers[i].getLastname() << "\n";
            }
        }
        int userIndex;
        std::cout << "Enter the number of the teacher to restore: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > teachers.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        teachers[userIndex].setStatus(1);
        // Rewrite teachersinfo.txt here
        std::ofstream file;
        file.open("teachersinfo.txt", std::ios_base::trunc);
        for (const auto& teacher : teachers) {
            file << teacher.getFirstname() << " " << teacher.getLastname() << " " << teacher.getUsername() << " " << teacher.getPassword() << " " << teacher.getStatus() << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Invalid option\n";
    }
}

void Admin::updateUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
    int userType;
    std::cout << "Enter 1 for student, 2 for teacher: ";
    std::cin >> userType;
    if (!std::cin.good() || (userType != 1 && userType != 2)) {
        std::cout << "Invalid input. Please enter an integer (1 or 2).\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (userType == 1) {
        for (int i = 0; i < students.size(); i++) {
            std::cout << i + 1 << ") " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
        }
        int userIndex;
        std::cout << "Enter the number of the student to update: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > students.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        std::string un, pw;
        std::cout << "Enter new username: ";
        std::cin >> un;
        std::cout << "Enter new password: ";
        std::cin >> pw;
        students[userIndex].setUsername(un);
        students[userIndex].setPassword(pw);
        // Update studentsinfo.txt here
        std::ofstream file;
        file.open("studentsinfo.txt", std::ios_base::trunc);
        for (const auto& student : students) {
            file << student.getFirstname() << " " << student.getLastname() << " " << student.getUsername() << " " << student.getPassword() << " " << student.getStatus() << "\n";
        }
        file.close();
    }
    else if (userType == 2) {
        for (int i = 0; i < teachers.size(); i++) {
            std::cout << i + 1 << ") " << teachers[i].getFirstname() << " " << teachers[i].getLastname() << "\n";
        }
        int userIndex;
        std::cout << "Enter the number of the teacher to update: ";
        std::cin >> userIndex;
        if (!std::cin.good() || userIndex <= 0 || userIndex > teachers.size()) {
            std::cout << "Invalid input. Please enter an integer within the correct range.\n";
            std::cout << "\033[2J\033[H";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        userIndex--;  // Adjust for 0-indexing
        std::string un, pw;
        std::cout << "Enter new username: ";
        std::cin >> un;
        std::cout << "Enter new password: ";
        std::cin >> pw;
        teachers[userIndex].setUsername(un);
        teachers[userIndex].setPassword(pw);
        // Update teachersinfo.txt here
        std::ofstream file;
        file.open("teachersinfo.txt", std::ios_base::trunc);
        for (const auto& teacher : teachers) {
            file << teacher.getFirstname() << " " << teacher.getLastname() << " " << teacher.getUsername() << " " << teacher.getPassword() << " " << teacher.getStatus() << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Invalid option\n";
    }
}



int getIntegerInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear(); // clear the error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any extra characters in the input buffer
    return choice;
}

void Admin::adminMenu(std::vector<Student>& students, std::vector<Teacher>& teachers) {
    int choice;
    Admin admin("admin", "admin", "admin", "admin");
    do {
        std::cout << "1)Add new user\n2)remove user\n3)update user\n4)restore user\n5)log out\n";
        choice = getIntegerInput();
        switch (choice) {
        case 1:
            int userType;
            std::cout << "Enter 1 for student, 2 for teacher: ";
            userType = getIntegerInput();
            if (userType == 1) {
                admin.createStudent(students);
            }
            else if (userType == 2) {
                admin.createTeacher(teachers);
            }
            else {
                std::cout << "Invalid option\n";
            }
            std::cout << "\033[2J\033[H";
            break;
        case 2:
            admin.removeUser(students, teachers);
            std::cout << "\033[2J\033[H";
            break;
        case 3:
            admin.updateUser(students, teachers);
            std::cout << "\033[2J\033[H";
            break;
        case 4:
            admin.restoreUser(students, teachers);
            std::cout << "\033[2J\033[H";
            break;
        }
    } while (choice != 5);
}
