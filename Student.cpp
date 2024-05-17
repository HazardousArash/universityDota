// student.cpp
#include "Student.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
Student::Student(std::string fn, std::string ln, std::string un, std::string pw, int status)
    : User(fn, ln, un, pw, status) {}
int getIntegerInput2() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear(); // clear the error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any extra characters in the input buffer
    return choice;
}
void Student::studentMenu() {
    int choice;
    do {
        std::cout << "1)View my info\n2)View my courses\n3)My scores\n4)Log out\n";
        //choice = getIntegerInput2();
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "First Name: " << getFirstname() << "\n";
            std::cout << "Last Name: " << getLastname() << "\n";
            std::cout << "Username: " << getUsername() << "\n";
            std::cout << "Password: " << getPassword() << "\n";
            break;
        case 2:
            this->myCoursesFinder();
            
            break;
        case 3:
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
                    while (std::getline(file, line)) {
                        std::string studentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
                        if (studentUsername == this->getUsername()) {
                            courseNames.push_back(courseName);
                            std::cout << courseNames.size() << ") " << courseName << "\n";  // Print the course name
                            break;
                        }
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
            std::string courseFile = "i."+chosenCourse + ".txt";
            std::fstream file(courseFile, std::ios::in | std::ios::out);
            if (!file) {
                std::cout << "Failed to open the course file.\n";
                break;
            }
            std::string line;
            while (std::getline(file, line)) {
                std::string studentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
                if (studentUsername == this->getUsername()) {
                    std::cout << "Your scores for all assignments in this course are:\n";
                    std::istringstream iss(line);
                    std::string token;
                    for (int i = 0; i < 2; i++) {
                        std::getline(iss, token, ',');  // Skip the first 3 tokens (index, username, and first 2 scores)
                    }
                    for (int i = 0; i < 5; i++) {
                        std::getline(iss, token, ',');
                        std::cout << "Assignment " << i + 1 << ": " << token << "\n";  // Print the score
                    }
                    break;
                }
            }
            file.close();
            break;
        }

        }
    } while (choice != 4);
}
void Student::myCoursesFinder() {
    std::string path = ".";  // The path of the directory where the course files are stored
    std::vector<std::string> courseNames;
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string filename = entry.path().filename().string();
        if (filename.find("i.") == 0) {  // Check if the filename starts with "i."
            std::ifstream file(filename);
            std::string line;
            std::getline(file, line);  // Read the first line
            std::string courseName = line.substr(line.find(": ") + 2);  // Extract the course name
            while (std::getline(file, line)) {
                std::string studentUsername = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);  // Extract the student's username
                if (studentUsername == this->getUsername()) {
                    courseNames.push_back(courseName);
                    std::cout << courseNames.size() << ") " << courseName << "\n";  // Print the course name
                    break;
                }
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
        return;
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
        return;
    }
    std::string assignmentFile = "i." + chosenCourse + ".assignment" + std::to_string(assignmentIndex) + ".txt";
    std::fstream file(assignmentFile, std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "Failed to open the assignment file.\n";
        return;
    }
    std::string line;
    std::streampos prevPos;
    while (std::getline(file, line)) {
        std::string studentUsername = line.substr(0, line.find(" "));  // Extract the student's username
        if (studentUsername == this->getUsername()) {
            std::cout << "Enter your answer (max 500 characters): ";
            std::string answer;
            std::getline(std::cin >> std::ws, answer);  // Read the whole line, ignore leading whitespaces
            answer = answer.substr(0, 500);  // Truncate to 500 characters
            file.clear();  // Clear the EOF flag that was set by std::getline
            file.seekp(prevPos);
            file << studentUsername << " " << answer << "\n";  // Write the student's username and answer to the file
            break;
        }
        prevPos = file.tellg();
    }
    file.close();
}


