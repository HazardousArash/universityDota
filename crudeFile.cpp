#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Teacher.h"
#include "Assignment.h"
#include "Course.h"

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
    std::vector<Course> courses;  // Declare 'courses' here

    loadData(students, teachers);

    std::string username, password;
    int attempts = 0;
    while (attempts < 3) {
        std::cout << "Enter username: ";
        std::cin >> username;
        if (username.length() < 6) {
            std::cout << "Username must be at least 6 characters long.\n";
            attempts++;
            continue;
        }
        std::cout << "Enter password: ";
        std::cin >> password;
        if (password.length() < 8) {
            std::cout << "Password must be at least 8 characters long.\n";
            attempts++;
            continue;
        }

        if (username == "admin1" && password == "admin123") {
            Admin admin("admin", "admin", "admin", "admin", 1);
            admin.adminMenu(students, teachers);
            break;
        }
        else {
            bool loggedIn = false;
            for (const auto& student : students) {
                if (student.getUsername() == username && student.getPassword() == password && student.getStatus() == 1) {
                    Student loggedInStudent = student;
                    loggedInStudent.studentMenu();
                    loggedIn = true;
                    break;
                }
            }
            if (!loggedIn) {
                for (const auto& teacher : teachers) {
                    if (teacher.getUsername() == username && teacher.getPassword() == password && teacher.getStatus() == 1) {
                        Teacher loggedInTeacher = teacher;
                        loggedInTeacher.teacherMenu(teacher, courses, students);
                        loggedIn = true;
                        break;
                    }
                }
            }
            if (!loggedIn) {
                std::cout << "Invalid username or password, or the user is removed\n";
                attempts++;
            }
            else {
                break;
            }
        }
    }

    if (attempts == 3) {
        std::cout << "Failed to login after 3 attempts. Exiting the program.\n";
        return 0;
    }

    return 0;
}


