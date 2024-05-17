#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "Assignment.h"  // Include this if Assignment is defined in assignment.h
#include "Student.h"
class Course {
private:
    std::string courseName;
    std::string teacherUsername;
    std::vector<std::string> studentUsernames;
    std::vector<Assignment> assignments;
    Assignment finalQuiz;

public:
    Course(std::string courseName, std::string teacherUsername);
    Course();
    std::string getCourseName() const;
    std::string getTeacherUsername() const;
    std::vector<std::string> getStudentUsernames() const;
    std::vector<Assignment> getAssignments() const;
    Assignment getFinalQuiz() const;
    void setCourseName(std::string courseName);
    void setTeacherUsername(std::string teacherUsername);
    void setStudentUsernames(std::vector<std::string> studentUsernames);
    void setAssignments(std::vector<Assignment> assignments);
    void setFinalQuiz(Assignment finalQuiz);
    void addStudent(std::string studentUsername);
    void addCourse(std::vector<Student>& students, const std::string& teacherUsername);
    void removeStudent(std::string studentUsername);
    static void courseFinder(const std::string& teacherUsername);
    void assignmentMenu();
};
#endif // COURSE_H
