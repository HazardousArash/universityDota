#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include <cstdlib>
#include<Windows.h>
std::system("cls");
class User {
protected:
    std::string firstname;
    std::string lastname;
    std::string username;
    std::string password;
    int status;  // 1 for active, 0 for removed
public:
    User(std::string fn, std::string ln, std::string un, std::string pw, int status = 1)
        : firstname(fn), lastname(ln), username(un), password(pw), status(status) {}

    std::string getFirstname() const { return firstname; }
    std::string getLastname() const { return lastname; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    int getStatus() const { return status; }

    void setUsername(std::string un) { username = un; }
    void setPassword(std::string pw) { password = pw; }
    void setStatus(int status) { this->status = status; }
};

class Student : public User {
public:
    Student(std::string fn, std::string ln, std::string un, std::string pw, int status = 1)
        : User(fn, ln, un, pw, status) {}
};

class Teacher : public User {
public:
    Teacher(std::string fn, std::string ln, std::string un, std::string pw, int status = 1)
        : User(fn, ln, un, pw, status) {}
};
class Admin : public User {
public:
    Admin(std::string fn, std::string ln, std::string un, std::string pw)
        : User(fn, ln, un, pw) {}

    void createStudent(std::vector<Student>& students) {
        std::string fn, ln, un, pw;
        std::cout << "Enter new student first name: ";
        std::cin >> fn;
        std::cout << "Enter new student last name: ";
        std::cin >> ln;
        std::cout << "Enter new student username: ";
        std::cin >> un;
        std::cout << "Enter new student password: ";
        std::cin >> pw;
        Student newStudent(fn, ln, un, pw);
        students.push_back(newStudent);
        std::ofstream file;
        file.open("studentsinfo.txt", std::ios_base::app);
        file << newStudent.getFirstname() << "," << newStudent.getLastname() << "," << newStudent.getUsername() << "," << newStudent.getPassword() << "," << newStudent.getStatus() << "\n";
        file.close();
    }

    void createTeacher(std::vector<Teacher>& teachers) {
        std::string fn, ln, un, pw;
        std::cout << "Enter new teacher first name: ";
        std::cin >> fn;
        std::cout << "Enter new teacher last name: ";
        std::cin >> ln;
        std::cout << "Enter new teacher username: ";
        std::cin >> un;
        std::cout << "Enter new teacher password: ";
        std::cin >> pw;
        Teacher newTeacher(fn, ln, un, pw);
        teachers.push_back(newTeacher);
        std::ofstream file;
        file.open("teachersinfo.txt", std::ios_base::app);
        file << newTeacher.getFirstname() << "," << newTeacher.getLastname() << "," << newTeacher.getUsername() << "," << newTeacher.getPassword() << "," << newTeacher.getStatus() << "\n";
        file.close();
    }

    void removeUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
        int userType;
        std::cout << "Enter 1 for student, 2 for teacher: ";
        std::cin >> userType;
        if (userType == 1) {
            for (int i = 0; i < students.size(); i++) {
                if (students[i].getStatus() == 1) {
                    std::cout << i + 1 << ") " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
                }
            }
            int userIndex;
            std::cout << "Enter the number of the student to remove: ";
            std::cin >> userIndex;
            userIndex--;  // Adjust for 0-indexing
            students[userIndex].setStatus(0);
            // Rewrite studentsinfo.txt here
            std::ofstream file;
            file.open("studentsinfo.txt", std::ios_base::trunc);
            for (const auto& student : students) {
                file << student.getFirstname() << "," << student.getLastname() << "," << student.getUsername() << "," << student.getPassword() << "," << student.getStatus() << "\n";
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
            userIndex--;  // Adjust for 0-indexing
            teachers[userIndex].setStatus(0);
            // Rewrite teachersinfo.txt here
            std::ofstream file;
            file.open("teachersinfo.txt", std::ios_base::trunc);
            for (const auto& teacher : teachers) {
                file << teacher.getFirstname() << "," << teacher.getLastname() << "," << teacher.getUsername() << "," << teacher.getPassword() << "," << teacher.getStatus() << "\n";
            }
            file.close();
        }
        else {
            std::cout << "Invalid option\n";
        }
    }

    void restoreUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
        int userType;
        std::cout << "Enter 1 for student, 2 for teacher: ";
        std::cin >> userType;
        if (userType == 1) {
            for (int i = 0; i < students.size(); i++) {
                if (students[i].getStatus() == 0) {
                    std::cout << i + 1 << ") " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
                }
            }
            int userIndex;
            std::cout << "Enter the number of the student to restore: ";
            std::cin >> userIndex;
            userIndex--;  // Adjust for 0-indexing
            students[userIndex].setStatus(1);
            // Rewrite studentsinfo.txt here
            std::ofstream file;
            file.open("studentsinfo.txt", std::ios_base::trunc);
            for (const auto& student : students) {
                file << student.getFirstname() << "," << student.getLastname() << "," << student.getUsername() << "," << student.getPassword() << "," << student.getStatus() << "\n";
            }
            file.close();
        }
        else if (userType == 2) {
            for (int i = 0; i < teachers.size(); i++) {
                if (teachers[i].getStatus() == 0) {
                    std::cout << i + 1 << ") " << teachers[i].getFirstname() << " " << teachers[i].getLastname() << "\n";
                }
            }
            int userIndex;
            std::cout << "Enter the number of the teacher to restore: ";
            std::cin >> userIndex;
            userIndex--;  // Adjust for 0-indexing
            teachers[userIndex].setStatus(1);
            // Rewrite teachersinfo.txt here
            std::ofstream file;
            file.open("teachersinfo.txt", std::ios_base::trunc);
            for (const auto& teacher : teachers) {
                file << teacher.getFirstname() << "," << teacher.getLastname() << "," << teacher.getUsername() << "," << teacher.getPassword() << "," << teacher.getStatus() << "\n";
            }
            file.close();
        }
        else {
            std::cout << "Invalid option\n";
        }
    }

    void updateUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
        int userType;
        std::cout << "Enter 1 for student, 2 for teacher: ";
        std::cin >> userType;
        if (userType == 1) {
            for (int i = 0; i < students.size(); i++) {
                std::cout << i + 1 << ") " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
            }
            int userIndex;
            std::cout << "Enter the number of the student to update: ";
            std::cin >> userIndex;
            userIndex--;  // Adjust for 0-indexing
            std::string un, pw;
            std::cout << "Enter new username: ";
            std::cin >> un;
            std::cout << "Enter new password: ";
            std::cin >> pw;
            students[userIndex].setUsername(un);
            students[userIndex].setPassword(pw);
            // Update studentsinfo.txt here
        }
        else if (userType == 2) {
            for (int i = 0; i < teachers.size(); i++) {
                std::cout << i + 1 << ") " << teachers[i].getFirstname() << " " << teachers[i].getLastname() << "\n";
            }
            int userIndex;
            std::cout << "Enter the number of the teacher to update: ";
            std::cin >> userIndex;
            userIndex--;  // Adjust for 0-indexing
            std::string un, pw;
            std::cout << "Enter new username: ";
            std::cin >> un;
            std::cout << "Enter new password: ";
            std::cin >> pw;
            teachers[userIndex].setUsername(un);
            teachers[userIndex].setPassword(pw);
            // Update teachersinfo.txt here
        }
        else {
            std::cout << "Invalid option\n";
        }
    }
};
void loadData(std::vector<Student>& students, std::vector<Teacher>& teachers) {
    std::ifstream file;
    std::string fn, ln, un, pw;
    int status;

    file.open("studentsinfo.txt");
    while (file >> fn >> ln >> un >> pw >> status) {
        students.push_back(Student(fn, ln, un, pw, status));
    }
    file.close();

    file.open("teachersinfo.txt");
    while (file >> fn >> ln >> un >> pw >> status) {
        teachers.push_back(Teacher(fn, ln, un, pw, status));
    }
    file.close();
}

int main() {
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    loadData(students, teachers);
    Admin admin("admin", "admin", "admin", "admin");
    int choice;
    do {
        std::cout << "1)Add new user\n2)remove user\n3)update user\n4)restore user\n5)log out\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            int userType;
            std::cout << "Enter 1 for student, 2 for teacher: ";
            std::cin >> userType;
            if (userType == 1) {
                admin.createStudent(students);
            }
            else if (userType == 2) {
                admin.createTeacher(teachers);
            }
            else {
                std::cout << "Invalid option\n";
            }

            break;
        case 2:
            admin.removeUser(students, teachers);
            break;
        case 3:
            admin.updateUser(students, teachers);
            break;
        case 4:
            admin.restoreUser(students, teachers);
            break;
            // Add other cases here
        }
    } while (choice != 5);
    return 0;
}
