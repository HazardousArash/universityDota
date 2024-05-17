// course.cpp
#include "Course.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
Course::Course(std::string courseName, std::string teacherUsername)
    : courseName(courseName), teacherUsername(teacherUsername) {}

Course::Course() {}

std::string Course::getCourseName() const { return courseName; }

std::string Course::getTeacherUsername() const { return teacherUsername; }

std::vector<std::string> Course::getStudentUsernames() const { return studentUsernames; }

std::vector<Assignment> Course::getAssignments() const { return assignments; }

Assignment Course::getFinalQuiz() const { return finalQuiz; }

void Course::setCourseName(std::string courseName) { this->courseName = courseName; }

void Course::setTeacherUsername(std::string teacherUsername) { this->teacherUsername = teacherUsername; }

void Course::setStudentUsernames(std::vector<std::string> studentUsernames) { this->studentUsernames = studentUsernames; }

void Course::setAssignments(std::vector<Assignment> assignments) { this->assignments = assignments; }

void Course::setFinalQuiz(Assignment finalQuiz) { this->finalQuiz = finalQuiz; }

void Course::addStudent(std::string studentUsername) {
    studentUsernames.push_back(studentUsername);
}

void Course::addCourse(std::vector<Student>& students, const std::string& teacherUsername) {
    std::string courseName;
    std::cout << "Enter course name: ";
    std::cin >> courseName;
    this->setCourseName(courseName);
    this->setTeacherUsername(teacherUsername);

    std::string input;
    std::vector<bool> added(students.size(), false);  // Track which students have been added
    do {
        // Check if all students have been added
        if (std::find(added.begin(), added.end(), false) == added.end()) {
            std::cout << "All the students who could participate in your course, have been added.\n";
            break;
        }

        std::cout << "Choose a student to add to the course (enter 'p' to proceed):\n";
        for (int i = 0; i < students.size(); i++) {
            if (!added[i]) {  // Only show students who haven't been added yet
                std::cout << i + 1 << ") " << students[i].getUsername() << "\n";
            }
        }
        std::cout << "Students added to course (remove them by putting 'r' behind their name):\n";
        for (int i = 0; i < students.size(); i++) {
            if (added[i]) {  // Only show students who have been added
                std::cout << i + 1 << ") " << students[i].getUsername() << "\n";
            }
        }
        std::cin >> input;
        if (input != "p") {
            if (input[0] == 'r') {  // Remove a student
                int studentIndex = std::stoi(input.substr(1));
                studentIndex--;  // Adjust for 0-indexing
                added[studentIndex] = false;  // Mark the student as not added
            }
            else {  // Add a student
                int studentIndex = std::stoi(input);
                studentIndex--;  // Adjust for 0-indexing
                this->addStudent(students[studentIndex].getUsername());
                added[studentIndex] = true;  // Mark the student as added
            }
        }
    } while (input != "p");

    std::ofstream file;
    file.open("i." + courseName + ".txt");
    file << "Course Name: " << courseName << "\n";
    file << "Teacher Username: " << this->getTeacherUsername() << "\n";
    std::vector<std::string> studentUsernames = this->getStudentUsernames();
    for (int i = 0; i < studentUsernames.size(); i++) {
        file << i + 1 << "," << studentUsernames[i] << ",0,0,0,0,0\n";
    }
    file.close();
}



void Course::courseFinder(const std::string& teacherUsername) {
    std::string path = ".";  // The path of the directory where the course files are stored
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string filename = entry.path().filename().string();
        if (filename.find("i.") == 0) {  // Check if the filename starts with "i."
            std::ifstream file(filename);
            std::string line;
            std::getline(file, line);  // Read the first line
            std::string courseName = line.substr(line.find(": ") + 2);  // Extract the course name
            std::getline(file, line);  // Read the second line
            std::string fileTeacherUsername = line.substr(line.find(": ") + 2);  // Extract the teacher's username
            if (fileTeacherUsername == teacherUsername) {
                std::cout << courseName << "\n";  // Print the course name
            }
            file.close();
        }
    }
}

void Course::assignmentMenu() {
    std::string path = ".";  // The path of the directory where the course files are stored
    for (int i = 1; i <= 5; i++) {
        std::string filename = "i." + courseName + ".assignment" + std::to_string(i) + ".txt";
        std::ifstream file(path + "/" + filename);
        if (file) {
            std::string assignmentName;
            std::getline(file, assignmentName);  // Read the first line to get the assignment name
            std::cout << "Assignment slot " << i << ") " << assignmentName << "\n";
            file.close();
        }
        else {
            std::cout << "Assignment slot " << i << ") empty\n";
        }
    }
    int assignmentIndex;
    std::cout << "Enter the number of the assignment slot to create an assignment: ";
    std::cin >> assignmentIndex;
    assignmentIndex--;  // Adjust for 0-indexing
    if (assignmentIndex < 0 || assignmentIndex >= 5) {
        std::cout << "Invalid assignment slot number.\n";
        return;
    }
    std::string name;
    int maxScore;
    std::string deadline;
    std::cout << "Enter assignment name: ";
    std::cin >> name;
    std::cout << "Enter maximum score: ";
    std::cin >> maxScore;
    std::cout << "Enter deadline: ";
    std::cin >> deadline;
    Assignment newAssignment(name, maxScore, deadline);
    if (assignmentIndex < assignments.size()) {
        assignments[assignmentIndex] = newAssignment;
    }
    else {
        assignments.push_back(newAssignment);
    }
    std::ofstream outFile("i." + courseName + ".assignment" + std::to_string(assignmentIndex + 1) + ".txt");
    outFile << name << "\n";  // Write the assignment name to the file
    outFile << maxScore << "\n";  // Write the maximum score to the file
    outFile << deadline << "\n";  // Write the deadline to the file
    std::ifstream courseFile("i." + courseName + ".txt");
    std::string line;
    std::getline(courseFile, line);  // Skip the first line (course name)
    std::getline(courseFile, line);  // Skip the second line (teacher's username)
    std::getline(courseFile, line);  // Skip the third line
    int studentIndex = 1;
    while (std::getline(courseFile, line)) {
        std::string studentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
        outFile << studentIndex << ")" << studentUsername << "\n";  // Write the student's username to the file
        studentIndex++;
    }
    courseFile.close();
    outFile.close();
}













