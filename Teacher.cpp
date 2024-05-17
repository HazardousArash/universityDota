// teacher.cpp
#include <sstream>
#include "Teacher.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
class user;
Teacher::Teacher(std::string fn, std::string ln, std::string un, std::string pw, int status)
    : User(fn, ln, un, pw, status) {}

int getIntegerInput3() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear(); // clear the error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any extra characters in the input buffer
    return choice;
}

void Teacher::teacherMenu(const Teacher& teacher, std::vector<Course>& courses, std::vector<Student>& students) {
    int choice;
    int courseIndex;
    do {
        std::cout << "1)View my info\n2)assignment manager\n3)list of my students\n4)Add a new course\n5)Score students\n6)Log out\n";
        //choice = getIntegerInput3();
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
        {
            std::cout << "Your courses:\n";
            std::string path = ".";  // The path of the directory where the course files are stored
            int courseIndex = 1;
            for (const auto& entry : fs::directory_iterator(path)) {
                std::string filename = entry.path().filename().string();
                if (filename.find("i.") == 0) {  // Check if the filename starts with "i."
                    std::ifstream file(filename);
                    std::string line;
                    std::getline(file, line);  // Read the first line
                    std::string courseName = line.substr(line.find(": ") + 2);  // Extract the course name
                    std::getline(file, line);  // Read the second line
                    std::string fileTeacherUsername = line.substr(line.find(": ") + 2);  // Extract the teacher's username
                    if (fileTeacherUsername == teacher.getUsername()) {
                        std::cout << courseIndex << ") " << courseName << "\n";  // Print the course name
                        Course newCourse(courseName, fileTeacherUsername);
                        courses.push_back(newCourse);
                        courseIndex++;
                    }
                    file.close();
                }
            }
            std::cout << "Enter the number of the course to view the assignment menu: ";
            std::cin >> courseIndex;
            courseIndex--;  // Adjust for 0-indexing
            if (courseIndex < 0 || courseIndex >= courses.size()) {
                std::cout << "Invalid course number.\n";
                break;
            }
            courses[courseIndex].assignmentMenu();
            int assignmentIndex;
            std::cout << "Enter the number of the assignment slot to create an assignment: ";
            std::cin >> assignmentIndex;
            assignmentIndex--;  // Adjust for 0-indexing
            if (assignmentIndex < 0 || assignmentIndex >= 5) {
                std::cout << "Invalid assignment slot number.\n";
                break;
            }
            std::string name;
            int maxScore;
            std::string exp;
            std::cout << "Enter assignment name: ";
            std::cin >> name;
            std::cout << "Enter maximum score: ";
            std::cin >> maxScore;
            std::cout << "Enter exp: ";
            std::cin >> exp;
            Assignment newAssignment(name, maxScore, exp);
            if (assignmentIndex < courses[courseIndex].getAssignments().size()) {
                courses[courseIndex].getAssignments()[assignmentIndex] = newAssignment;
            }
            else {
                courses[courseIndex].getAssignments().push_back(newAssignment);
            }
            std::ofstream file("i." + courses[courseIndex].getCourseName() + ".assignment" + std::to_string(assignmentIndex + 1) + ".txt");
            for (const auto& studentUsername : courses[courseIndex].getStudentUsernames()) {
                file << studentUsername << " 0\n";
            }
            file.close();
            std::cout << "Assignment created successfully.\n";
            break;
        }
        case 3:
            Teacher::studentFinder(teacher.getUsername());
            break;
        case 4:{
            Course newCourse;
            newCourse.addCourse(students, teacher.getUsername());
            courses.push_back(newCourse);
            break;
            }
        case 5:
        {
            std::string path = ".";  // The path of the directory where the course files are stored
            std::vector<std::string> courseNames;
            for (const auto& entry : fs::directory_iterator(path)) {
                std::string filename = entry.path().filename().string();
                if (filename.find("i.") == 0) {  // Check if the filename starts with "i."
                    std::ifstream file(filename);
                    std::string line;
                    std::getline(file, line);  // Read the first line
                    std::string courseName = line.substr(line.find(": ") + 2);  // Extract the course name
                    std::getline(file, line);  // Read the second line
                    std::string fileTeacherUsername = line.substr(line.find(": ") + 2);  // Extract the teacher's username
                    if (fileTeacherUsername == teacher.getUsername()) {
                        courseNames.push_back(courseName);
                        std::cout << courseNames.size() << ") " << courseName << "\n";  // Print the course name
                    }
                    file.close();
                }
            }
            int courseIndex;
            std::cout << "Enter the number of the course to choose: ";
            std::cin >> courseIndex;
            courseIndex--;  // Adjust for 0-indexing
            if (courseIndex < 0 || courseIndex >= courseNames.size()) {
                std::cout << "Invalid course number.\n";
                break;
            }
            std::string chosenCourse = courseNames[courseIndex];
            for (int i = 1; i <= 5; i++) {
                std::string assignmentFile = "i." + chosenCourse + ".assignment" + std::to_string(i) + ".txt";
                std::ifstream file(assignmentFile);
                if (file) {
                    std::string assignmentName;
                    std::getline(file, assignmentName);  // Read the first line to get the assignment name
                    std::cout << i << ") " << assignmentName << "\n";
                    file.close();
                }
            }
            int assignmentIndex;
            std::cout << "Enter the number of the assignment to choose: ";
            std::cin >> assignmentIndex;
            if (assignmentIndex < 1 || assignmentIndex > 5) {
                std::cout << "Invalid assignment number.\n";
                break;
            }
            std::string assignmentFile = "i." + chosenCourse + ".assignment" + std::to_string(assignmentIndex) + ".txt";
            std::ifstream file(assignmentFile);
            if (!file) {
                std::cout << "Failed to open the assignment file.\n";
                break;
            }
            std::string line;
            std::getline(file, line);  // Skip the first line (assignment name)
            int maxScore;
            file >> maxScore;  // Read the maximum score from the second line
            std::getline(file, line);
            std::getline(file, line);// Skip the third line (deadline)
            std::vector<std::string> studentUsernames;
            std::vector<std::string> studentAnswers;
            int studentIndex = 1;
            while (std::getline(file, line)) {
                std::string studentUsername = line.substr(0, line.find(" "));  // Extract the student's username
                std::string studentAnswer = line.substr(line.find(" ") + 1);  // Extract the student's answer
                studentUsernames.push_back(studentUsername);
                studentAnswers.push_back(studentAnswer.empty() ? "No answer" : studentAnswer);
                std::cout << "Student " << studentIndex << ": " << studentUsername << ", Answer: " << studentAnswer << "\n";  // Print the student's username and answer
                studentIndex++;
            }
            file.close();

            std::cout << "Enter the number of the student to score: ";
            std::cin >> studentIndex;
            studentIndex--;  // Adjust for 0-indexing
            if (studentIndex < 0 || studentIndex >= studentUsernames.size()) {
                std::cout << "Invalid student number.\n";
                break;
            }
            int score;
            std::cout << "Enter the score for the student: ";
            std::cin >> score;
            // Ensure the score is not less than 0 or more than the max score
            score = std::max(0, std::min(score, maxScore));

            // Now update the score in the course file
            std::fstream courseFile("i."+chosenCourse + ".txt", std::ios::in | std::ios::out);
            if (!courseFile) {
                std::cout << "Failed to open the course file.\n";
                break;
            }
            std::streampos prevPos;
            while (std::getline(courseFile, line)) {
                std::string fileStudentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
                if (fileStudentUsername == studentUsernames[studentIndex]) {
                    std::string newLine;
                    int commaCount = 0;
                    for (char& c : line) {
                        if (c == ',') {
                            commaCount++;
                        }
                        if (commaCount == assignmentIndex + 2) {
                            newLine += std::to_string(score);
                        }
                        else {
                            newLine += c;
                        }
                    }
                    courseFile.seekp(prevPos);
                    courseFile << newLine << "\n";  // Write the new line with the updated score
                    break;
                }
                prevPos = courseFile.tellg();
            }
            courseFile.close();

            std::cout << "Score updated successfully.\n";
            break;
        }







        }
    } while (choice != 6);
}
void Teacher::studentFinder(const std::string& teacherUsername) {
    std::string path = ".";  // The path of the directory where the course files are stored
    int courseIndex = 1;
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
                std::cout << courseIndex << ")" << courseName << "\n";  // Print the course name
                courseIndex++;
                int studentIndex = 1;
                while (std::getline(file, line)) {
                    std::string studentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
                    std::cout << "  " << studentIndex << "." << studentUsername << "\n";  // Print the student's username
                    studentIndex++;
                }
            }
            file.close();
        }
    }
}
    



