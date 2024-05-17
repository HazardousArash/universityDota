//#include "Teacher.h
//#include "Student.h"
//#include "Admin.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
class Student;
class Assignment {
public:
    std::string name;
    int maxScore;
    std::map<std::string, int> studentScores;  // Maps a student's username to their score

    // Constructor
    Assignment(std::string name, int maxScore) : name(name), maxScore(maxScore) {}
    Assignment() {}
    // Getters
    std::string getName() const { return name; }
    int getMaxScore() const { return maxScore; }
    std::map<std::string, int> getStudentScores() const { return studentScores; }

    // Setters
    void setName(std::string name) { this->name = name; }
    void setMaxScore(int maxScore) { this->maxScore = maxScore; }
    void setStudentScores(std::map<std::string, int> studentScores) { this->studentScores = studentScores; }

    // Other methods
    void addScore(std::string studentUsername, int score) {
        studentScores[studentUsername] = score;
    }
};

class Course {
private:
    std::string courseName;
    std::string teacherUsername;
    std::vector<std::string> studentUsernames;
    std::vector<Assignment> assignments;
    Assignment finalQuiz;

public:
    Course(std::string courseName, std::string teacherUsername)
        : courseName(courseName), teacherUsername(teacherUsername) {}
    Course() {}

    // Getters
    std::string getCourseName() const { return courseName; }
    std::string getTeacherUsername() const { return teacherUsername; }
    std::vector<std::string> getStudentUsernames() const { return studentUsernames; }
    std::vector<Assignment> getAssignments() const { return assignments; }
    Assignment getFinalQuiz() const { return finalQuiz; }

    // Setters
    void setCourseName(std::string courseName) { this->courseName = courseName; }
    void setTeacherUsername(std::string teacherUsername) { this->teacherUsername = teacherUsername; }
    void setStudentUsernames(std::vector<std::string> studentUsernames) { this->studentUsernames = studentUsernames; }
    void setAssignments(std::vector<Assignment> assignments) { this->assignments = assignments; }
    void setFinalQuiz(Assignment finalQuiz) { this->finalQuiz = finalQuiz; }

    // Other methods
    void addStudent(std::string studentUsername) {
        studentUsernames.push_back(studentUsername);
    }
    void addCourse(std::vector<Student*>& students) {
        std::string courseName;
        std::cout << "Enter course name: ";
        std::cin >> courseName;
        this->setCourseName(courseName);

        std::string input;
        do {
            std::cout << "Choose a student to add to the course (enter 'p' to proceed): \n";
            for (int i = 0; i < students.size(); i++) {
                std::cout << i + 1 << ") " << students[i]->getUsername() << "\n";
            }
            std::cin >> input;
            if (input != "p") {
                int studentIndex = std::stoi(input);
                studentIndex--;  // Adjust for 0-indexing
                this->addStudent(students[studentIndex]->getUsername());
            }
        } while (input != "p");

        std::ofstream file;
        file.open(courseName + ".txt");
        file << "Course Name: " << courseName << "\n";
        file << "Teacher Username: " << this->getTeacherUsername() << "\n";
        std::vector<std::string> studentUsernames = this->getStudentUsernames();
        for (int i = 0; i < studentUsernames.size(); i++) {
            file << i + 1 << "," << studentUsernames[i] << ",0,0,0,0,0\n";
        }
        file.close();
    }


    void removeStudent(std::string studentUsername) {
//        studentUsernames.erase(std::remove(studentUsernames.begin(), studentUsernames.end(), studentUsername), studentUsernames.end());
    }
};

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
    void studentMenu() {
        int choice;
        do {
            std::cout << "1)View my info\n2)View my courses\n3)Log out\n";
            std::cin >> choice;
            switch (choice) {
            case 1:
                // Your existing code here
                break;
            case 2:
                // Your existing code here
                break;
                // Add other cases here
            }
        } while (choice != 5);
    }
};

class Teacher : public User {
public:
    Teacher(std::string fn, std::string ln, std::string un, std::string pw, int status = 1)
        : User(fn, ln, un, pw, status) {}
    void createAssignment(Course& course) {
        if (course.getAssignments().size() >= 5) {
            std::cout << "Maximum number of assignments reached for this course.\n";
            return;
        }
        std::string name;
        int maxScore;
        std::cout << "Enter assignment name: ";
        std::cin >> name;
        std::cout << "Enter maximum score: ";
        std::cin >> maxScore;
        Assignment newAssignment(name, maxScore);
        std::vector<Assignment> assignments = course.getAssignments();
        assignments.push_back(newAssignment);
        course.setAssignments(assignments);

        std::cout << "Assignment created successfully.\n";
    }
    void createFinalQuiz(Course& course) {
        std::string name;
        int maxScore;
        std::cout << "Enter final quiz name: ";
        std::cin >> name;
        std::cout << "Enter maximum score: ";
        std::cin >> maxScore;

        Assignment finalQuiz(name, maxScore);
        course.setFinalQuiz(finalQuiz);

        std::cout << "Final quiz created successfully.\n";
    }
    void teacherMenu(const Teacher& teacher, std::vector<Course>& courses, std::vector<Student>& students) {
        int choice;
        int courseIndex;
        do {
            std::cout << "1)View my info\n2)View my courses\n3)View my students\n4)Empty for now\n5)Log out\n";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore leftover newline
            switch (choice) {
            case 1:
                std::cout << "First Name: " << teacher.getFirstname() << "\n";
                std::cout << "Last Name: " << teacher.getLastname() << "\n";
                std::cout << "Username: " << teacher.getUsername() << "\n";
                std::cout << "Password: " << teacher.getPassword() << "\n";
                break;
            case 2:
                if (courses.empty()) {
                    std::cout << "No courses available. Press 'a' to add a course.\n";
                    char option;
                    std::cin >> option;
                    if (option == 'a') {
                        Course newCourse;
                        newCourse.setTeacherUsername(teacher.getUsername());
                        std::vector<Student*> studentPointers;
                        for (Student& student : students) {
                            studentPointers.push_back(&student);
                        }
                        newCourse.addCourse(studentPointers);
                        courses.push_back(newCourse);
                    }
                }
                else {
                    for (int i = 0; i < courses.size(); i++) {
                        if (courses[i].getTeacherUsername() == getUsername()) {
                            std::cout << i + 1 << ") " << courses[i].getCourseName() << "\n";
                        }
                    }
                    std::cout << "Enter the number of the course to view, 'a' to add a course, or 'r' to remove a course: ";
                    std::string input;
                    std::cin >> input;
                    if (input == "a") {
                        // Call addCourse function here
                    }
                    else if (input == "r") {
                        // Call removeCourse function here
                    }
                    else {
                        int courseIndex = std::stoi(input);
                        if (courseIndex > 0 && courseIndex <= courses.size()) {
                            courseIndex--;  // Adjust for 0-indexing
                            // Display course details here
                        }
                    }
                }
                break;

            case 3:
                for (int i = 0; i < courses.size(); i++) {
                    if (courses[i].getTeacherUsername() == getUsername()) {
                        std::cout << i + 1 << ") " << courses[i].getCourseName() << "\n";
                    }
                }
                std::cout << "Enter the number of the course to view students, or 0 to go back: ";

                std::cin >> courseIndex;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore leftover newline
                if (courseIndex > 0 && courseIndex <= courses.size()) {
                    courseIndex--;  // Adjust for 0-indexing
                    std::vector<std::string> studentUsernames = courses[courseIndex].getStudentUsernames();
                    for (int i = 0; i < studentUsernames.size(); i++) {
                        std::cout << i + 1 << ") " << studentUsernames[i] << "\n";
                    }
                }
                break;
            case 4:
                // Empty for now
                break;
            }
        } while (choice != 5);
    }



};
class Admin : public User {
public:
    Admin(std::string fn, std::string ln, std::string un, std::string pw, int status = 1)
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
        file << newStudent.getFirstname() << " " << newStudent.getLastname() << " " << newStudent.getUsername() << " " << newStudent.getPassword() << " " << newStudent.getStatus() << "\n";
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
        file << newTeacher.getFirstname() << " " << newTeacher.getLastname() << " " << newTeacher.getUsername() << " " << newTeacher.getPassword() << " " << newTeacher.getStatus() << "\n";
        file.close();
    }

    void removeUser(std::vector<Student>& students, std::vector<Teacher>& teachers) {
        int userType;
        std::cout << "Enter 1 for student, 2 for teacher: ";
        std::cin >> userType;
        if (userType == 1) {
            for (int i = 0; i < students.size(); i++) {
                if (students[i].getStatus() == 1) {
                    std::cout << i + 1 << " " << students[i].getFirstname() << " " << students[i].getLastname() << "\n";
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

    void adminMenu(std::vector<Student>& students, std::vector<Teacher>& teachers) {
        int choice;
        Admin admin("admin", "admin", "admin", "admin");
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
    std::vector<Course> courses;  // Declare 'courses' here

    loadData(students, teachers);

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (username == "admin" && password == "admin") {
        Admin admin("admin", "admin", "admin", "admin", 1);
        admin.adminMenu(students, teachers);
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
        }
    }

    return 0;
}

