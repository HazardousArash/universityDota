#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include <vector>
#include "student.h"  // Include this if Student is defined in student.h
#include "teacher.h"  // Include this if Teacher is defined in teacher.h
class Course;
class Student;
class Admin : public User {
public:
    Admin(std::string fn, std::string ln, std::string un, std::string pw, int status = 1);
    void createStudent(std::vector<Student>& students);
    void createTeacher(std::vector<Teacher>& teachers);
    void removeUser(std::vector<Student>& students, std::vector<Teacher>& teachers);
    void restoreUser(std::vector<Student>& students, std::vector<Teacher>& teachers);
    void updateUser(std::vector<Student>& students, std::vector<Teacher>& teachers);
    void adminMenu(std::vector<Student>& students, std::vector<Teacher>& teachers);
    bool isUniqueUsernameteacher(const std::vector<Teacher>& teachers, const std::string& username);
    bool isUniqueUsernamestudent(const std::vector<Student>& students, const std::string& username);
};
#endif
