#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    Student(std::string fn, std::string ln, std::string un, std::string pw, int status = 1);
    void studentMenu();
    void myCoursesFinder();
};
#endif