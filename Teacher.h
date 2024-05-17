#ifndef TEACHER_H
#define TEACHER_H
#include "User.h"
#include <vector>
#include "course.h"  // Include this if Course is defined in course.h
#include "student.h"  // Include this if Student is defined in student.h
class Course;
class Student;
class Teacher : public User {
public:
    Teacher(std::string fn, std::string ln, std::string un, std::string pw, int status = 1);
    void createAssignment(Course& course);
    void createFinalQuiz(Course& course);
    void teacherMenu(const Teacher& teacher, std::vector<Course>& courses, std::vector<Student>& students);
    void studentFinder(const std::string& teacherUsername);
    //void studentFinder(const std::string& teacherUsername, const std::vector<Student>& students);
};
#endif
